/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "k_transport.h"
#include "k_transport.hpp"

//#include "kt_zeromq.hpp"
#include <zmq.h>

/* Create new empty kt_msg_t
 */
kt_msg_t* kt_msg_new ()
{
  kt_msg_t* msg = new kt_msg_t();
  return msg;
}

/* Destroy passed kt_msg_t*
 */
void kt_msg_destroy ( kt_msg_t* msg )
{
  // Empty the metadata
  msg->metadata.clear();
  assert ( msg->metadata.empty() );

  // Delete the payload from the heap
  (*msg->free_payload) ( msg->payload );
  msg->payload = NULL;
  msg->payload_size = 0;

  // Cleanup the kt_msg_t construct
  delete msg;
  msg = NULL;
}

kt_handle_t* kt_create_handle ( void* (*callback_func)(kt_conn_session_t*, kt_msg_t*) )
{
  kt_handle_t* handle = new kt_handle_t();
  handle->callback = callback_func;
  return handle;
}

kt_application_layer _return_transport_from_endpoint (const char* rem)
{
  assert (rem != NULL);
  std::string remote(rem);

  if ( remote.compare (0, 3, "tcp") == 0 )
    return KT_TCP;

  return 0;
}

kt_conn_session_t* kt_connect ( const char* rem )
{
  //if ( _return_transport_from_endpoint (rem) == KT_TCP )
  if ( true )
  {
    std::cout << "We have tcp, let's use 0mq" << std::endl;

    kt_conn_session_info* info = new kt_conn_session_info ();
    kt_conn_session* sess = new kt_conn_session ();

    info->context = zmq_ctx_new ();
    info->socket = zmq_socket (info->context, ZMQ_REQ);
    zmq_connect (info->socket, rem);

    sess->_info = info;
    return sess;
  }  
  else
  {
    std::cout << "No tcp, no workee, failed hard!" << std::endl;
    return NULL;
  }
}
