#include <czmq.h>
#include <zmq.h>

#ifndef KTRANSPORT_H
#define	KTRANSPORT_H
#ifdef	__cplusplus
extern "C" {
#endif

typedef zctx_t kctx_t;

typedef enum kt_network_layer {
    IPLEGACY,
    IPV6
} kt_network_layer;

typedef enum kt_transport_layer {
    TCP,
    UDP,
    DCCP,
    SCTP
} kt_transport_layer;

/* TODO: This needs some more fine tuning like setting the protocol level,
 * desired algorithms, key exchanges etc.
 * <habl> 21.08.2013
 */
typedef enum kt_crypto_layer {
    NONE,
    TLS,
    SSL
} kt_crypto_layer;

typedef enum kt_application_layer {
    HTTP,
    RTSP,
    NTP,
    FTP,
    NFS
} kt_application_layer;

typedef struct kt_network_stack {
    enum kt_network_layer network;
    enum kt_transport_layer transport;
    enum kt_crypto_layer crypto;
    enum kt_application_layer application;
} kt_network_stack;

/* The application type directly decides the communication pattern of the
 * socket and network and transport layers. Also it makes certain assumptions
 * that for e.g. a webserver implies HTTP with TCP on Port 80 and a streaming
 * service uses RTSP and UDP on port 554.
 */
typedef enum kt_application_type {
    WEBSERVER,
    PUBLISHER,
    STREAM,
    ROUNDROBIN
};

typedef struct kt_messageraw {
    char *body;
    char *msgData;
    int type;
} kt_messageraw;

#ifdef	__cplusplus
}
#endif

#endif	/* KTRANSPORT_H */

