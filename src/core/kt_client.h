/* 
 * File:   kt_client.h
 * Author: habl
 *
 * Created on August 26, 2013, 11:09 AM
 */

#ifndef KT_CLIENT_H
#define	KT_CLIENT_H

#include <czmq.h>
#include "kiara.h"
#include "ktransport.h"

//#ifdef	__cplusplus
//extern "C" {
//#endif

typedef struct {
	kt_connconf_t config;
	void *socket;
	kctx_t *ctx;
} kt_clientctx_t;

kt_clientctx_t *kt_client_init(kt_connconf_t config);
int kt_client_connect(kt_clientctx_t *kt_ctx);
int kt_client_disconnect(kt_clientctx_t *kt_ctx);
kt_messageraw_t* recv_message(kt_clientctx_t *kt_ctx);
int send_message(kt_clientctx_t *kt_ctx, kt_messageraw_t *msg);

//#ifdef	__cplusplus
//}
//#endif

#endif	/* KT_CLIENT_H */

