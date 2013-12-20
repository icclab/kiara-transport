/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "../../include/KT_Zeromq.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <zmq.h>

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
		KT_Msg msg = recv (*sess, 0);
		_callback ( msg, sess, this );
	}
}

KIARA::Transport::KT_Session*
KIARA::Transport::KT_Zeromq::connect ( KIARA::Transport::KT_Client& endpoint ) {
	void* socket = zmq_socket ( _context, ZMQ_REQ );
	// TODO: fix dangerous pointer to underlying data structure
	const char* host = endpoint.get_endpoint().c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
		return NULL;

	KIARA::Transport::KT_Session* session = new KIARA::Transport::KT_Session ();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint.get_endpoint() );
	_sessions.insert ( std::make_pair ( endpoint.get_endpoint(), session ) );

	return session;
}
// Zeromq has no synchronous send. Thus linger is correctly throwing a -Wunused warning
void
KIARA::Transport::KT_Zeromq::send ( KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session& session, int linger) {
	if ( KT_STREAM == _configuration.get_application_type() )
	{
		zmq_send ( session.get_socket(), session.get_zeromq_identifier().data(), session.get_zeromq_identifier().size(), ZMQ_SNDMORE );
	}
	zmq_send ( session.get_socket(), message.get_payload().data(), message.get_payload().size() + 1, 0 );
}

// Zeromq has no asynchronous recv. Thus linger is correctly throwing a -Wunused warning
// zmq_recv will block until a message arrived
KIARA::Transport::KT_Msg
KIARA::Transport::KT_Zeromq::recv ( KIARA::Transport::KT_Session& session, int linger ) {
	KIARA::Transport::KT_Msg message;
	std::vector< char > buffer;
	std::vector< char > identifier;

	// TODO: Remove magic number
	if ( KT_STREAM == _configuration.get_application_type() )
	{
		identifier.resize ( 1024 );
		int size = zmq_recv ( session.get_socket(), identifier.data(), identifier.size(), 0);
		identifier.resize ( (size_t)size );
		session.set_zeromq_identifier ( std::move(identifier) );
	}

	// TODO Remove magic number
	buffer.resize ( 1024 );
	int rc = zmq_recv ( session.get_socket(), buffer.data(), buffer.size(), 0);
	if ( -1 == rc )
		return std::move ( message );

	buffer.resize ( (size_t)rc );

	message.set_payload ( std::move(buffer) );
	return std::move ( message );
}

void
KIARA::Transport::KT_Zeromq::disconnect ( KIARA::Transport::KT_Session& session ) {
	zmq_close ( session.get_socket() );
	_sessions.erase( session.get_endpoint() );
}

void
KIARA::Transport::KT_Zeromq::register_callback ( void (*callback)(KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session* session, KIARA::Transport::KT_Connection* obj) ) {
	_callback = callback;
}

/**
 * bind requires a valid callback handler which is called when a message is
 * received, it binds according to the set configuration
 */
void
KIARA::Transport::KT_Zeromq::bind ( std::string endpoint ) {
	void* socket = NULL;

	if ( KT_STREAM == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_STREAM );
	}
	else if ( KT_REQUESTREPLY == _configuration.get_application_type() )
	{
		socket = zmq_socket ( _context, ZMQ_REP);
	}

	assert ( socket );
	int rc = zmq_bind ( socket, endpoint.c_str() );

	if ( 0 != rc )
		return;

	KIARA::Transport::KT_Session* session = new KIARA::Transport::KT_Session();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint );
	_sessions.insert ( std::make_pair ( endpoint, session ) );

	interupted = false;
	poller_thread = new std::thread ( &KT_Zeromq::poller, this, socket, endpoint );
}

/**
 * stops listening to incomming messages
 */
void
KIARA::Transport::KT_Zeromq::unbind ( ) {
	interupted = true;
	poller_thread->join();
}
