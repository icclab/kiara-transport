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

enum message_type {
	HTTP,						// 0

#ifdef WITH_SSL
	,
	HTTP_TLS					// 1
#endif
};

typedef struct KIARA_MessageRaw KIARA_MessageRaw;

struct KIARA_MessageRaw
{
    char *body;
	char *msgData;
	int type;	
};

typedef zctx_t kctx_t;

/*kctx_t* kctx_new() {
	return (kctx_t*) zctx_new();
}*/

#ifdef	__cplusplus
}
#endif

#endif	/* KTRANSPORT_H */

