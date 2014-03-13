/*
 * KT_Configuration_glob.h
 *
 *  Created on: Mar 13, 2014
 *      Author: habl
 */

#ifndef KT_CONFIGURATION_GLOB_H_
#define KT_CONFIGURATION_GLOB_H_

#ifdef __cplusplus
extern "C" {
#endif

// network layer
typedef unsigned int kt_network_layer;
#define KT_IPLEGACY 4
#define KT_IPV6     6

// transport layer
// see RFC 790 for numbers
typedef unsigned int kt_transport_layer;
#define KT_TCP    6
#define KT_UDP   21
#define KT_DCCP  33
#define KT_SCTP 132

/* TODO: This needs some more fine tuning like setting the protocol level,
 * desired algorithms, key exchanges etc.
 * <habl> 21.08.2013
 */

// crypto layer
typedef unsigned int kt_crypto_layer;
#define KT_NONE   0
#define KT_SSL    1
#define KT_TLS    2

// application layer
typedef unsigned int kt_application_layer;
#define KT_ZEROMQ  0
#define KT_HTTP    1
#define KT_RTSP    2
#define KT_NTP     3
#define KT_FTP     4
#define KT_NFS     5

/* The application type directly decides the communication pattern of the
 * socket and network and transport layers. Also it makes certain assumptions
 * that for e.g. a webserver implies HTTP with TCP on Port 80 and a streaming
 * service uses RTSP and UDP on port 554.
 */

typedef unsigned int kt_application_type;
#define KT_WEBSERVER      0
#define KT_PUBLISHER      1
#define KT_STREAM         2
#define KT_ROUNDROBIN     3
#define KT_REQUESTREPLY   4

#ifdef __cplusplus
}
#endif

#endif /* KT_CONFIGURATION_GLOB_H_ */
