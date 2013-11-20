/*
 * KIARA transport library
 *
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#include "k_transport.h"
#include "k_transport.hpp"

kt_msg_t* kt_msg_new ()
{
  kt_msg_t* msg = new kt_msg_t();
  return msg;
}

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
