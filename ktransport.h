/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 7. August 2013, 17:04
 */

#include <czmq.h>
#include <zmq.h>

#ifndef KTRANSPORT_H
#define	KTRANSPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef zctx_t kctx_t;

enum message_type {
	HTTP,

#ifdef WITH_SSL
	HTTP_TLS
#endif
};

typedef struct kt_messageraw
{
        char *body;
        char *msgData;
	int type;
} kt_messageraw;

#ifdef	__cplusplus
}
#endif

#endif	/* KTRANSPORT_H */

