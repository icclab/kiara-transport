/* 
 * File:   server.h
 * Author: aepp, habl
 *
 * Created on 24. Juli 2013, 14:24
 */
//TODO: Replace czmq by ktransport.h
#include <czmq.h>
#include <stdlib.h>
#include "kiara.h"
#include "ktransport.h"

#ifndef KT_SERVER_H
#define	KT_SERVER_H

#ifdef	__cplusplus
extern "C" {
#endif

enum threading_model {
	BOSS_WORKER,
	BOSS_WORKER_CLUSTER
};

enum communication_pattern {
	REQ_REP,
	PUBLISH_SUBSCRIBE,
    ROUTER
};

typedef struct {
	kt_connconf_t config;
        void *frontend;
        void *backend;
	void *dispatcher;
        enum threading_model th_model;
	int thread_nbr;
	kctx_t *ctx;
} kt_srvctx_t;

struct forking_params_hack {
	kt_messageraw_t* (*f)(kt_messageraw_t * msg);
	kt_srvctx_t* kt_ctx;
};
//public
kt_srvctx_t *kt_init_server(kt_connconf_t config);
int kt_run_server(kt_srvctx_t *context, kt_messageraw_t * (*f)(kt_messageraw_t* msgData));
int kt_stop_server(kt_srvctx_t *context);
static void _server_worker(void *args, zctx_t *ctx, void *pipe);
void* _connect_to_backend(zctx_t *ctx);
void _disconnect_from_backend(zctx_t *ctx, void* socket);
kt_messageraw_t* _recv_message(kt_srvctx_t *kt_ctx, void *sock);
int _send_message(kt_srvctx_t *kt_ctx, void *sock, kt_messageraw_t *msg);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
