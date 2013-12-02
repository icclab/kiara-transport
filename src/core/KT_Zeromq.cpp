/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "../../include/KT_Zeromq.hpp"

#include <algorithm>
#include <cstdlib> // for malloc
#include <zmq.h>

KIARA::Transport::KT_Zeromq::KT_Zeromq() {
	_context = zmq_ctx_new ();
}

KIARA::Transport::KT_Zeromq::~KT_Zeromq() {
	zmq_ctx_destroy ( _context );
}

KIARA::Transport::KT_Session*
KIARA::Transport::KT_Zeromq::connect ( KIARA::Transport::KT_Client &endpoint ) {
	void* socket = zmq_socket ( _context, ZMQ_REQ );
	const char* host = endpoint.get_endpoint().c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
		return NULL;

	KIARA::Transport::KT_Session *session = new KIARA::Transport::KT_Session ();
	session->set_socket ( socket );
	session->set_endpoint ( endpoint.get_endpoint() );

	std::string *identifier = new std::string (endpoint.get_endpoint());
	_sessions.insert ( std::pair<std::string*, KIARA::Transport::KT_Session*>(identifier, session) );

	return session;
}

void
KIARA::Transport::KT_Zeromq::send ( KIARA::Transport::KT_Msg &message, KIARA::Transport::KT_Session &session, int linger) {
	void* payload = malloc ( message.get_payload()->size() + 1 );
	memcpy ( payload, message.get_payload()->data(), message.get_payload()->size() );
	zmq_send ( session.get_socket(), payload, message.get_payload()->size() + 1, linger );
	delete (&message);
}

KIARA::Transport::KT_Msg*
KIARA::Transport::KT_Zeromq::recv ( KIARA::Transport::KT_Session& session, int linger ) {
	// TODO: Remove magic number
	std::vector< unsigned char > *buffer = new std::vector< unsigned char >(1024);
	int rc = zmq_recv ( session.get_socket(), &buffer[0], 1024, linger);
	if ( -1 == rc )
		return NULL;

	KIARA::Transport::KT_Msg* message = new KIARA::Transport::KT_Msg();
	message->set_payload(buffer);

	return message;
}

void
KIARA::Transport::KT_Zeromq::disconnect ( KIARA::Transport::KT_Session& session ) {
	zmq_close ( session.get_socket() );
	std::string *key = new std::string ( session.get_endpoint() );

	// something bugs me … does it then compare the address of the key or the value?
	// since this is a pointer it might not get dereferenced and the address used instead
	// the actual value rendering the erase useless or even dangerous.
	_sessions.erase( key );
}

void
KIARA::Transport::KT_Zeromq::register_callback ( void (*callback)(KIARA::Transport::KT_Msg& message, KIARA::Transport::KT_Session& session) ) {

}

/**
 * bind requires a valid callback handler which is called when a message is
 * received, it binds according to the set configuration
 */
void
KIARA::Transport::KT_Zeromq::bind ( ) {

}

/**
 * stops listening to incomming messages
 */
void
KIARA::Transport::KT_Zeromq::unbind ( ) {

}
