/*
 * KIARA transport library
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#ifndef
#define K_TRANSPORT

#define K_TRANSPORT_MAJOR 0
#define K_TRANSPORT_MINOR 1
#define K_TRANSPORT_PATCH 0

/* k_user_data is a pointer to an opaque data structure which is needed by the
 * upper layers of KIARA and will not be modified by the transport library.
 */

typedef struct kt_conn_session {
  kt_conn_session_info* _info;
  void* k_user_data;
} kt_conn_session_t;

/* Since payload is handled as a pointer to a binary memory allocation
 * *free_payload() is responsible to destroy/deallocate the beforementioned
 * memory.
 *
 * According to settings in kt_conn_session_t defined it will generate valid
 * header and body structures from the metadata and payload when sent. The
 * same applies the other way around when receiving messages.
 */

typedef struct kt_msg {
  std::map <std::string, std::string> metadata;
  void* payload;
  std::size_t payload_size;
  void (*free_payload) (void*);
} kt_msg_t;

#endif // K_TRANSPORT
