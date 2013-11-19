/*
 * KIARA transport library
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 * Reference: doc/Library API contract.md
 */

#ifndef KT_TRANSPORT
#define KT_TRANSPORT

// Includes
#include <stdint.h>

#define KT_TRANSPORT_MAJOR 0
#define KT_TRANSPORT_MINOR 1
#define KT_TRANSPORT_PATCH 0

// #ifdef unixoid
#include <pthread.h>
#define THREAD_HANDLE pthread_t
// #endif

#ifdef __cplusplus
extern "C" {
#endif

// network layer
typedef uint8_t kt_network_layer;
#define KT_IPLEGACY 4
#define KT_IPV6     6

// transport layer
// see RFC 790 for numbers
// size defined RFC 790, 8 bit field
typedef uint8_t kt_transport_layer;
#define KT_TCP    6
#define KT_UDP   21
#define KT_DCCP  33
#define KT_SCTP 132

/* TODO: This needs some more fine tuning like setting the protocol level,
 * desired algorithms, key exchanges etc.
 * <habl> 21.08.2013
 */

// crypto layer
typedef uint8_t kt_crypto_layer;
#define KT_NONE   0
#define KT_SSL    1
#define KT_TLS    2

// application layer
typedef uint8_t kt_application_layer;
#define KT_ZEROMQ  0
#define KT_HTTP    1
#define KT_RTSP    2
#define KT_NTP     3
#define KT_FTP     4
#define KT_NFS     5

struct kt_network_stack {
  kt_network_layer network_layer;
  kt_transport_layer transport_layer;
  kt_crypto_layer crypto_layer;
  kt_application_layer application_layer;
  // as defined by RFC 793 this field is 16 bit long
  uint16_t port;
};

/* The application type directly decides the communication pattern of the
 * socket and network and transport layers. Also it makes certain assumptions
 * that for e.g. a webserver implies HTTP with TCP on Port 80 and a streaming
 * service uses RTSP and UDP on port 554.
 */

// 8 bit allows 256 different application types, should be enough
typedef uint8_t kt_application_type;
#define KT_WEBSERVER      0
#define KT_PUBLISHER      1
#define KT_STREAM         2
#define KT_ROUNDROBIN     3
#define KT_REQUESTREPLY   4

typedef struct {
  struct kt_network_stack network_config;
  kt_application_type application_type;
  char *base_url;
} kt_connconf_t;

typedef struct kt_conn_session kt_conn_session_t;

typedef struct kt_msg kt_msg_t;

// client functions
kt_conn_session_t* kt_connect ( const char* );
int kt_send ( kt_conn_session_t*, kt_msg_t*, int );
kt_msg_t* kt_recv ( kt_conn_session_t*, int );
void* kt_disconnect ( kt_conn_session_t* );

// server functions
kt_conn_session_t* kt_init_server ( kt_connconf_t );
void kt_register_handle ( kt_conn_session_t*, THREAD_HANDLE* );
int kt_run_server ( kt_conn_session_t* );
void* kt_stop_server ( kt_conn_session_t*, int );

#ifdef __cplusplus
}
#endif

#endif // K_TRANSPORT
