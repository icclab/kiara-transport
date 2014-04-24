/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "KT_Zeromq.hpp"
#include <iostream>

namespace KIARA
{
namespace Transport
{

KT_Zeromq::KT_Zeromq() {
	_context = zmq_ctx_new ();
}

KT_Zeromq::~KT_Zeromq() {
	zmq_ctx_destroy ( _context );
}

void
KT_Zeromq::poller ( void* socket, std::string endpoint ) {
	KT_Session* sess = _sessions->find ( endpoint )->second;
	while (!interupted)
	{
		KT_Msg* msg = new KT_Msg;
		if (0 == recv (*sess, *msg, 0))
		    _std_callback ( *msg, sess, this );
	}
}

void* KT_Zeromq::create_socket (unsigned int socket_type, bool listener)
{
    void* socket = nullptr;
    int errcode = 0;
    switch (socket_type)
    {
    case KT_STREAM:
    case KT_WEBSERVER:
        socket = zmq_socket ( _context, ZMQ_STREAM );
        errcode = errno;
        break;
    case KT_REQUESTREPLY:
        if (listener)
        {
            socket = zmq_socket ( _context, ZMQ_REP);
        } else {
            socket = zmq_socket ( _context, ZMQ_REQ);
        }
        errcode = errno;
        break;
    case KT_PUBLISHSUBSCRIBE:
        // Even though a client is listening to messages we have to invert this
        // model since clients connect to the server that binds. Since connect
        // implicitly means !listener this would be the wrong way around.
        //
        // Basically the client acts as a server and the server as a client.
        if (!listener)
        {
            socket = zmq_socket ( _context, ZMQ_PUB);
        } else {
            socket = zmq_socket ( _context, ZMQ_SUB);
        }
        errcode = errno;
        break;
    default:
        break;
    }
    errno = errcode;
    return socket;
}

int
KT_Zeromq::connect ( KT_Session** ret ) {
	void* socket = nullptr;
	int errcode = 0;

	socket = create_socket(_configuration.get_application_type(), false);

	if (nullptr == socket)
	{
		errno = errcode;
		return -1;
	}

	KT_Configuration config = get_configuration();
	// memory leak
	std::string* binding_name = new std::string;
	if (KT_TCP == config.get_transport_layer())
	{
		binding_name->append("tcp://");
	} else {
		return -1;
	}

	binding_name->append(config.get_hostname());
	binding_name->append(":");
	binding_name->append(std::to_string(config.get_port_number()));

	// TODO: fix dangerous pointer to underlying data structure
	const char* host = binding_name->c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
	{
		errno = errcode;
		return -1;
	}

	if (KT_PUBLISHSUBSCRIBE == config.get_application_type())
	{
	    // Just subscribe to everything
	    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);
	}

	uint8_t id [256];
	size_t id_size = 256;
	zmq_getsockopt(socket, ZMQ_IDENTITY, id, &id_size);

	KT_Session* session = new KT_Session ();
	session->set_socket ( socket );
	session->set_endpoint ( *binding_name );
	std::vector<char> identifier (id, id + id_size);
	session->set_identifier( std::move(identifier));
	_sessions->insert ( std::make_pair ( *binding_name, session ) );

	*ret = session;

	return 0;
}

// Zeromq has no synchronous send. Thus linger is correctly throwing a -Wunused warning
int
KT_Zeromq::send ( KT_Msg& message, KT_Session& session, int linger) {
    switch (_configuration.get_application_type ())
    {
    case (KT_STREAM):
    case (KT_WEBSERVER):
		int rc = zmq_send ( session.get_socket(), session.get_identifier().data(), session.get_identifier().size(), ZMQ_SNDMORE );
		int errcode = errno;
		if (session.get_identifier().size() != static_cast<std::vector<char>::size_type>(rc) )
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
KT_Zeromq::recv ( KT_Session& session, KT_Msg& ret, int linger ) {
	KT_Msg message;
	std::vector< char > buffer;
	std::vector< char > identifier;
	int size;

	switch (_configuration.get_application_type ())
    {
    case (KT_STREAM):
    case (KT_WEBSERVER):
        std::cerr << "KT_STREAM, stripping zmq_identity" << std::endl;
        zmq_msg_t id;
        zmq_msg_init (&id);
        size = zmq_msg_recv (&id, session.get_socket (), 0);
        identifier.resize (size_t (size));
        char* id_ptr = (char*) zmq_msg_data (&id);
        identifier = std::vector<char> (id_ptr, id_ptr + size);
        session.set_identifier (std::move (identifier));
        zmq_msg_close (&id);
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
KT_Zeromq::disconnect ( KT_Session& session ) {
	zmq_close ( session.get_socket() );
	_sessions->erase( session.get_endpoint() );
	return 0;
}

int
KT_Zeromq::register_callback ( std::function<void(KT_Msg&, KT_Session*, KT_Connection*)> callback ) {
	_std_callback = callback;
	return 0;
}

/**
 * bind requires a valid callback handler which is called when a message is
 * received, it binds according to the set configuration
 */
int
KT_Zeromq::bind ( ) {
	void* socket = nullptr;
	int errcode = 0;

	socket = create_socket(_configuration.get_application_type(), true);

	if (nullptr == socket)
	{
		errno = errcode;
		return -1;
	}

	KT_Configuration config = get_configuration();
	// memory leak
	std::string* binding_name = new std::string;
	if (KT_TCP == config.get_transport_layer())
	{
		binding_name->append("tcp://");
	} else {
		return -1;
	}

	binding_name->append(config.get_hostname());
	binding_name->append(":");
	binding_name->append(std::to_string(config.get_port_number()));

	int rc = zmq_bind ( socket, binding_name->c_str() );
	errcode = errno;
	if ( 0 != rc )
	{
		errno = errcode;
		return -1;
	}

	KT_Session* session = new KT_Session();
	session->set_socket ( socket );
	session->set_endpoint ( binding_name->c_str() );
	_sessions->insert ( std::make_pair ( binding_name->c_str(), session ) );

	if (KT_PUBLISHSUBSCRIBE != _configuration.get_application_type())
	{
	    interupted = false;
	    poller_thread = new std::thread ( &KT_Zeromq::poller, this, socket, binding_name->c_str() );
	}
	return 0;
}

/**
 * stops listening to incomming messages
 */
int
KT_Zeromq::unbind ( ) {
	interupted = true;
	poller_thread->join();
	return 0;
}

} /* namespace Transport */
} /* namespace KIARA */
