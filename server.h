/* 
 * File:   server.h
 * Author: aepp
 *
 * Created on 24. Juli 2013, 14:24
 */
#include <czmq.h>

#ifndef SERVER_H
#define	SERVER_H

#ifdef	__cplusplus
extern "C" {
#endif
	
typedef struct KIARAServerConfig KIARAServerConfig;
typedef struct KIARAServerContext KIARAServerContext;
	
enum server_type {
	TCP,							// 0
	TCP_HTTP						// 1

#ifdef WITH_SSL
	,
	TCP_HTTPS,				// 3
#endif
};

enum threading_model {
	BOSS_WORKER,			// 0
	BOSS_WORKER_CLUSTER		// 1
};

enum communication_pattern {
	REQ_REP,				// 0
	PUBLISH_SUBSCRIBE		// 1
};

//public
struct KIARAServerConfig {
	int type;
	char *base_url;
};

//private
struct KIARAServerContext {
	struct KIARAServerConfig config;
	int th_model;
	int thread_nbr;
	zctx_t *ctx;
};

//public
KIARAServerContext *initServer(KIARAServerConfig config);
void *runServer(KIARAServerContext *context, void (*f)(char*, char*, char*));

//private
static void server_worker(void *args, zctx_t *ctx, void *pipe);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */

