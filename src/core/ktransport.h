#include <czmq.h>
#include <zmq.h>

#ifndef KTRANSPORT_H
#define	KTRANSPORT_H
//#ifdef	__cplusplus
//extern "C" {
//#endif

typedef zctx_t kctx_t;

enum kt_network_layer {
	IPLEGACY,
	IPV6
};

enum kt_transport_layer {
	TCP,
	UDP,
	DCCP,
	SCTP
};

/* TODO: This needs some more fine tuning like setting the protocol level,
 * desired algorithms, key exchanges etc.
 * <habl> 21.08.2013
 */
enum kt_crypto_layer {
	NONE,
	TLS,
	SSL
};

enum kt_application_layer {
	ZEROMQ,
	HTTP,
	RTSP,
	NTP,
	FTP,
	NFS
};

struct kt_network_stack_t {
	enum kt_network_layer network;
	enum kt_transport_layer transport;
	enum kt_crypto_layer crypto;
	enum kt_application_layer application;
	uint16_t port;
};

/* The application type directly decides the communication pattern of the
 * socket and network and transport layers. Also it makes certain assumptions
 * that for e.g. a webserver implies HTTP with TCP on Port 80 and a streaming
 * service uses RTSP and UDP on port 554.
 */
typedef enum kt_application_type {
	WEBSERVER,
	PUBLISHER,
	STREAM,
	ROUNDROBIN,
	REQUESTREPLY
} kt_application_type;

typedef struct kt_messageraw_t {
	// identity given to the message by zeromq router zsocket, don't
	// fiddle with it or expect nothing to work anymore
	zframe_t *_identity;
	// actual payload, that's what you look for
	char *msgData;
	// reserved for later use
	int type;
} kt_messageraw_t;

typedef struct {
	struct kt_network_stack_t network_config;
	enum kt_application_type type;
	char *base_url;
} kt_connconf_t;

char* compile_endpoint_string(kt_connconf_t config);

//#ifdef	__cplusplus
//}
//#endif

#endif	/* KTRANSPORT_H */

