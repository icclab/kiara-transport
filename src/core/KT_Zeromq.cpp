/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "KT_Zeromq.hpp"
#include <iostream>

KIARA::Transport::KT_Zeromq::KT_Zeromq() {
	_context = zmq_ctx_new ();
}

KIARA::Transport::KT_Zeromq::~KT_Zeromq() {
	zmq_ctx_destroy ( _context );
}

void
KIARA::Transport::KT_Zeromq::poller ( void* socket, std::string endpoint ) {
	KIARA::Transport::KT_Session* sess = _sessions.find ( endpoint )->second;
	while (!interupted)
	{
		KT_Msg msg;
		int error = recv (*sess, msg, 0);
		_callback ( msg, sess, this );
	}
}

int
KIARA::Transport::KT_Zeromq::connect ( KIARA::Transport::KT_Client& endpoint, KIARA::Transport::KT_Session** ret ) {
	void* socket = NULL;
	int errcode;
	if ( KT_STREAM == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_STREAM );
		errcode = errno;
	}
	else if ( KT_REQUESTREPLY == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_REQ);
		errcode = errno;
	}

	if (NULL == socket)
	{
		errno = errcode;
		return -1;
	}
	// TODO: fix dangerous pointer to underlying data structure
	const char* host = endpoint.get_endpoint().c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
	{
		errno = errcode;
		return -1;
	}

	uint8_t id [256];
	size_t id_size = 256;
	zmq_getsockopt(socket, ZMQ_IDENTITY, id, &id_size);

	KIARA::Transport::KT_Session* session = new KIARA::Transport::KT_Session ();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint.get_endpoint() );
	std::vector<char> identifier (id, id + id_size);
	session->set_zeromq_identifier( std::move(identifier));
	_sessions.insert ( std::make_pair ( endpoint.get_endpoint(), session ) );

	*ret = session;

	return 0;
}

// Zeromq has no synchronous send. Thus linger is correctly throwing a -Wunused warning
int
KIARA::Transport::KT_Zeromq::send ( KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session& session, int linger) {
	if ( KT_STREAM == _configuration.get_application_type() )
	{
		int rc = zmq_send ( session.get_socket(), session.get_zeromq_identifier().data(), session.get_zeromq_identifier().size(), ZMQ_SNDMORE );
		int errcode = errno;
		if (session.get_zeromq_identifier().size() != static_cast<std::vector<char>::size_type>(rc) )
		{
			std::cerr << "Failed to send identity to 0mq socket: " << std::strerror(errcode) << std::endl;
			errno = errcode;
			return -1;
		}
	}

	int rc = zmq_send ( session.get_socket(), message.get_payload().data(), message.get_payload().size(), 0 );
	int errcode = errno;
	if (message.get_payload().size() != static_cast<std::vector<char>::size_type>(rc))
	{
		errno = errcode;
		return -1;
	}

	return 0;
}

// Zeromq has no asynchronous recv. Thus linger is correctly throwing a -Wunused warning
// zmq_recv will block until a message arrived
int
KIARA::Transport::KT_Zeromq::recv ( KIARA::Transport::KT_Session& session, KIARA::Transport::KT_Msg& ret, int linger ) {
	KIARA::Transport::KT_Msg message;
	std::vector< char > buffer;
	std::vector< char > identifier;
	int size;

	if ( KT_STREAM == _configuration.get_application_type() )
	{
		zmq_msg_t id;
		zmq_msg_init (&id);
		size = zmq_msg_recv (&id, session.get_socket(), 0);
		identifier.resize(size_t(size));
		char* id_ptr = (char*)zmq_msg_data(&id);
		identifier = std::vector<char>(id_ptr, id_ptr + size);
		session.set_zeromq_identifier ( std::move(identifier) );
		zmq_msg_close(&id);
	}

	zmq_msg_t msg;
	zmq_msg_init (&msg);
	size = zmq_msg_recv (&msg, session.get_socket(), 0);
	if ( -1 == size )
	{
		ret = std::move (message);
		return -1;
	}

	char* msg_ptr = (char*)zmq_msg_data(&msg);
	buffer = std::vector<char>(msg_ptr, msg_ptr + size);

	ret.set_payload ( buffer );
	zmq_msg_close(&msg);

	return 0;
}

int
KIARA::Transport::KT_Zeromq::disconnect ( KIARA::Transport::KT_Session& session ) {
	zmq_close ( session.get_socket() );
	_sessions.erase( session.get_endpoint() );
	return 0;
}

int
KIARA::Transport::KT_Zeromq::register_callback ( void (*callback)(KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session* session, KIARA::Transport::KT_Connection* obj) ) {
	_callback = callback;
	return 0;
}

/**
 * bind requires a valid callback handler which is called when a message is
 * received, it binds according to the set configuration
 */
int
KIARA::Transport::KT_Zeromq::bind ( std::string endpoint ) {
	void* socket = NULL;
	int errcode;

	if ( KT_STREAM == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_STREAM );
		errcode = errno;
	}
	else if ( KT_REQUESTREPLY == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_REP);
		errcode = errno;
	}

	if (NULL == socket)
	{
		errno = errcode;
		return -1;
	}

	int rc = zmq_bind ( socket, endpoint.c_str() );
	errcode = errno;
	if ( 0 != rc )
	{
		errno = errcode;
		return -1;
	}

	KIARA::Transport::KT_Session* session = new KIARA::Transport::KT_Session();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint );
	_sessions.insert ( std::make_pair ( endpoint, session ) );

	interupted = false;
	poller_thread = new std::thread ( &KT_Zeromq::poller, this, socket, endpoint );
	return 0;
}

/**
 * stops listening to incomming messages
 */
int
KIARA::Transport::KT_Zeromq::unbind ( ) {
	interupted = true;
	poller_thread->join();
	return 0;
}
