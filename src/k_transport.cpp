/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "../include/k_transport.hpp"

//#include "kt_zeromq.hpp"
#include <cstdlib> // for malloc
#include <zmq.h>

typedef void kt_msg;

// KT_Msg implementation
namespace KIARA {
  namespace Transport {

  /* KT_Msg class */

  // Empty constructor
  KT_Msg::KT_Msg () {}

  // Constructor with payload
  KT_Msg::KT_Msg (std::vector<unsigned char>& payload)
  {
    this->_payload = payload;
  }

  // Destructor
  KT_Msg::~KT_Msg ()
  {
    // Destroy payload
    this->_payload.clear ();

    // Destroy metadata
    this->_metadata.clear ();
  }

  // Metadata methods
  void KT_Msg::add_metadata (std::string key, std::string value)
  {
    this->_metadata.insert (std::pair<std::string, std::string> (key, value));
  }

  std::map <std::string, std::string>&&
    KT_Msg::get_metadata ()
  {
    return std::move (_metadata);
  }

  // Payload methods
  void KT_Msg::set_payload (const std::vector<unsigned char> payload)
  {
    this->_payload = payload;
  }

  std::vector<unsigned char>&& KT_Msg::get_payload ()
  {
    return std::move (_payload);
  }
  } // end of namespace Transport
} // end of namespace KIARA

/* Create new empty kt_msg_t
 */

kt_msg* kt_msg_new ()
{
  return reinterpret_cast<kt_msg*>(new KIARA::Transport::KT_Msg());
}

/* Destroy passed kt_msg_t*
 */

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

kt_conn_session_t* kt_connect ( const char* rem )
{
  if ( _return_transport_from_endpoint (rem) == KT_TCP )
  {
    kt_conn_session_info *info = new kt_conn_session_info ();
    kt_conn_session_t *sess = new kt_conn_session ();

    info->context = zmq_ctx_new ();
    info->socket = zmq_socket (info->context, ZMQ_REQ);
    zmq_connect (info->socket, rem);

    sess->_info = info;
    return sess;
  }  
  else
  {
    std::cout << "No tcp, no workee, failing hard!" << std::endl;
    return NULL;
  }
}

void* kt_disconnect ( kt_conn_session_t* sess )
{
  zmq_close ( sess->_info->socket );
  zmq_ctx_destroy ( sess->_info->context );
  return sess->k_user_data;
}

int kt_send ( kt_conn_session_t* sess, kt_msg* msg, int linger )
{
  zmq_send ( sess->_info->socket, (char*) msg->payload, msg->payload_size, 0 );
  kt_msg_destroy (msg);
  return 0;
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
