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

KIARA::Transport::KT_Session*
KIARA::Transport::KT_Zeromq::connect ( KIARA::Transport::KT_Client &endpoint ) {
	_context = zmq_ctx_new ();
	void* socket = zmq_socket ( _context, ZMQ_REQ );

	const char* host = endpoint.get_endpoint().c_str();
	int rc = zmq_connect ( socket, host );

	if ( 0 != rc )
		return NULL;

	KIARA::Transport::KT_Session *session = new KIARA::Transport::KT_Session ();
	session->set_socket ( socket );

	std::string *identifier = new std::string (endpoint.get_endpoint());
	_sessions.insert ( std::pair<std::string*, KIARA::Transport::KT_Session*>(identifier, session) );

	return session;
}

void
send ( KIARA::Transport::KT_Msg &message, KIARA::Transport::KT_Session &session, int linger = 0 ) {
	void* payload = malloc ( message.get_payload()->size() + 1 );
	memcpy ( payload, message.get_payload()->data(), message.get_payload()->size() );
	zmq_send ( session.get_socket(), payload, message.get_payload()->size() + 1, linger );
	delete (&message);
}

KIARA::Transport::KT_Msg*
recv ( KIARA::Transport::KT_Session& session, int linger = 0 ) {
	// TODO: Remove magic number
	std::vector< unsigned char > *buffer = new std::vector< unsigned char >(1024);
	int rc = zmq_recv ( session.get_socket(), &buffer[0], 1024, linger);
	if ( -1 == rc )
		return NULL;

	KIARA::Transport::KT_Msg* message = new KIARA::Transport::KT_Msg();
	message->set_payload(buffer);

	return message;
}

/*

kt_msg* kt_msg_new ()
{
  return reinterpret_cast<kt_msg*>(new KIARA::Transport::KT_Msg());
}

void kt_msg_destroy ( kt_msg* msg )
{
  // Prevent working on NULL
  assert (msg);
  delete (msg);
}

void kt_msg_set_payload ( kt_msg* c_msg, void* payload, size_t payload_size)
{
  KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
}

void* kt_msg_get_payload ( kt_msg* c_msg )
{
  KIARA::Transport::KT_Msg *msg = reinterpret_cast<KIARA::Transport::KT_Msg *> (c_msg);
  return msg->get_payload().data ();
}

kt_application_layer _return_transport_from_endpoint (const char* rem)
{
  assert (rem != NULL);
  std::string remote(rem);

  if ( remote.compare (0, 3, "tcp") == 0 )
    return KT_TCP;

  return 0;
}

void* kt_disconnect ( kt_conn_session_t* sess )
{
  zmq_close ( sess->_info->socket );
  zmq_ctx_destroy ( sess->_info->context );
  return sess->k_user_data;
}

kt_msg_t* kt_recv ( kt_conn_session_t* sess, int linger )
{
  void* buffer = malloc(100);
  kt_msg* msg = kt_msg_new ();
  int rc = zmq_recv ( sess->_info->socket, buffer, 100, 0 );
  assert ( rc != -1 );

  msg->payload = buffer;
  msg->payload_size = rc;

  return msg;
}

 */
