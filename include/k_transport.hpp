/*
 * KIARA transport library
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

//#include <features.h>

#include <map>
#include <string>
#include <cassert>

#if defined (__UNIX__) || defined (__APPLE__)
#include <pthread.h>
#define THREAD_HANDLE pthread_t
#endif

/* Since payload is handled as a pointer to a binary memory allocation
 * *free_payload() is responsible to destroy/deallocate the beforementioned
 * memory.
 *
 * According to settings in kt_conn_session_t defined it will generate valid
 * header and body structures from the metadata and payload when sent. The
 * same applies the other way around when receiving messages.
 */

struct kt_msg {
  std::map <std::string, std::string> metadata;
  void* payload;
  std::size_t payload_size;
  void (*free_payload) (void*);
};

/* k_user_data is a pointer to an opaque data structure which is needed by the
 * upper layers of KIARA and will not be modified by the transport library.
 */

// TODO: What shoudl kt_conn_session_info actually hold?
#define kt_conn_session_info void

struct kt_conn_session {
  kt_conn_session_info* _info;
  void* k_user_data;
};

struct kt_thread_handle {
 THREAD_HANDLE * callback;
};