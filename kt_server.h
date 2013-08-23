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
typedef struct {
	struct kt_network_stack_t network_config;
	char *base_url;
} kt_srvconf_t;

typedef struct {
	kt_srvconf_t config;
        void *frontend;
        void *backend;
	void *dispatcher;
        enum threading_model th_model;
	int thread_nbr;
	kctx_t *ctx;
} kt_srvctx_t;

//public
kt_srvctx_t *kt_init_server(kt_srvconf_t config);
int kt_run_server(kt_srvctx_t *context, void (*f)(kt_messageraw_t* msgData));
int kt_stop_server(kt_srvctx_t *context);
static void server_worker(void *args, zctx_t *ctx, void *pipe);
void connect_to_backend(kt_srvctx_t *ctx);
void disconnect_from_backend(kt_srvctx_t *ctx);
kt_messageraw_t* recv_message(kt_srvctx_t *ctx);
int send_message(kt_srvctx_t *ctx, kt_messageraw_t *msg);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
