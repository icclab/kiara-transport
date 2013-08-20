/* 
 * File:   server.h
 * Author: aepp, habl
 *
 * Created on 24. Juli 2013, 14:24
 */
//TODO: Replace czmq by ktransport.h
#include <czmq.h>
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

//public
typedef struct kt_srvconf {
	int type;
	char *base_url;
} kt_srvconf;

typedef struct kt_srvctx {
	struct kt_srvconf config;
        void *frontend;
        void *backend;
        enum threading_model th_model;
	int thread_nbr;
	kctx_t *ctx;
} kt_srvctx;

//public
kt_srvctx *kt_init_server(kt_srvconf config);
int kt_run_server(kt_srvctx *context, void (*f)(kt_messageraw* msgData));
int kt_stop_server(kt_srvctx *context);
static void server_worker(void *args, zctx_t *ctx, void *pipe);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
