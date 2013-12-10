/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "../../include/KT_Zeromq.hpp"

#include <algorithm>
#include <zmq.h>

KIARA::Transport::KT_Zeromq::KT_Zeromq() {
	_context = zmq_ctx_new ();
}

KIARA::Transport::KT_Zeromq::~KT_Zeromq() {
	zmq_ctx_destroy ( _context );
}

KIARA::Transport::KT_Session*
KIARA::Transport::KT_Zeromq::connect ( KIARA::Transport::KT_Client& endpoint ) {
	void* socket = zmq_socket ( _context, ZMQ_REQ );
	const char* host = endpoint.get_endpoint().c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
		return NULL;

	KIARA::Transport::KT_Session *session = new KIARA::Transport::KT_Session ();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint.get_endpoint() );
	_sessions.insert ( std::pair<std::string, KIARA::Transport::KT_Session*>(endpoint.get_endpoint(), session) );

	return session;
}

void
KIARA::Transport::KT_Zeromq::send ( KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session& session, int linger) {
	zmq_send ( session.get_socket(), message.get_payload().data(), message.get_payload().size() + 1, linger );
}

KIARA::Transport::KT_Msg*
KIARA::Transport::KT_Zeromq::recv ( KIARA::Transport::KT_Session& session, int linger ) {
	// TODO: Remove magic number
	std::vector< char > buffer;
	buffer.resize ( 1024 );
	int rc = zmq_recv ( session.get_socket(), buffer.data(), buffer.size(), linger);
	if ( -1 == rc )
		return NULL;

	KIARA::Transport::KT_Msg* message = new KIARA::Transport::KT_Msg();
	message->set_payload(buffer);
	return message;
}

void
KIARA::Transport::KT_Zeromq::disconnect ( KIARA::Transport::KT_Session& session ) {
	zmq_close ( session.get_socket() );
	_sessions.erase( session.get_endpoint() );
}

void
KIARA::Transport::KT_Zeromq::register_callback ( void (*callback)(KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session& session) ) {

}

/**
 * bind requires a valid callback handler which is called when a message is
 * received, it binds according to the set configuration
 */
void
KIARA::Transport::KT_Zeromq::bind ( std::string endpoint ) {
	void* socket = zmq_socket ( _context, ZMQ_REP );
	zmq_bind ( socket, endpoint.c_str() );

	while (1)
	{
		char buffer[10];
		zmq_recv (socket, buffer, 10, 0);
		printf ("Received: %s\n", buffer);
		zmq_send (socket, "Reply", 5, 0);
	}
}

/**
 * stops listening to incomming messages
 */
void
KIARA::Transport::KT_Zeromq::unbind ( ) {

}
