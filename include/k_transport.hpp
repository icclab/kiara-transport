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
#include <iostream>
#include <vector>
#include <utility>

//#include "k_transport.h"

#include "dirty_nasty_preprocessor_hacks.h"

#if defined (__UNIX__)
#include <pthread.h>
#define THREAD_HANDLE pthread_t
#endif

namespace KIARA {
  namespace Transport {
/* Since payload is handled as a pointer to a binary memory allocation
 * *free_payload() is responsible to destroy/deallocate the beforementioned
 * memory.
 *
 * According to settings in kt_conn_session_t defined it will generate valid
 * header and body structures from the metadata and payload when sent. The
 * same applies the other way around when receiving messages.
 */

class KT_Msg {
 private:
    // Members
    std::map <std::string, std::string> _metadata;
    std::vector <unsigned char> _payload;

 public:
    // Constructor, Destructor
    KT_Msg ();
    KT_Msg (std::vector<unsigned char>& payload);
    ~KT_Msg ();

    // **** Methods ****
   
    // **** Accessors ****

    // Metadata methods
    void add_metadata (std::string key, std::string value);
    std::map <std::string, std::string>&&
      get_metadata ();
    std::string&& get_serialized_metadata (std::string delimiter);

    // Payload methods
    void set_payload (const std::vector<unsigned char> payload);
    std::vector<unsigned char>&& get_payload();

};
    
    

/* k_user_data is a pointer to an opaque data structure which is needed by the
 * upper layers of KIARA and will not be modified by the transport library.
 */

// TODO: What should kt_conn_session_info actually hold?
struct kt_conn_session_info {
  void* context;
  void* socket;
};

struct kt_conn_session {
  kt_conn_session_info* _info;
  void* k_user_data;
};

kt_application_layer _return_transport_from_endpoint (char*);

  } // end of namespace Transport
} // end of namespace KIARA
