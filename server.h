/* 
 * File:   server.h
 * Author: aepp
 *
 * Created on 24. Juli 2013, 14:24
 */
//TODO: Replace czmq by ktransport.h
#include <czmq.h>
#include "kiara.h"
#include "kmessage.h"
#include "ktransport.h"

#ifndef SERVER_H
#define	SERVER_H

#ifdef	__cplusplus
extern "C" {
#endif
	
typedef struct KIARA_ServerConfig KIARA_ServerConfig;
typedef struct KIARA_ServerContext KIARA_ServerContext;

enum threading_model {
	BOSS_WORKER,			// 0
	BOSS_WORKER_CLUSTER		// 1
};

enum communication_pattern {
	REQ_REP,				// 0
	PUBLISH_SUBSCRIBE		// 1
};

//public
struct KIARA_ServerConfig {
	int type;
	char *base_url;
};

//private
struct KIARA_ServerContext {
	struct KIARA_ServerConfig config;
	int th_model;
	int thread_nbr;
	zctx_t *ctx;
};

//public
KIARA_ServerContext *initServer(KIARA_ServerConfig config);
KIARA_Result runServer(KIARA_ServerContext *context, void (*f)(char*, char*, char*));
KIARA_Result stopServer(KIARA_ServerContext *context);

//private
static void server_worker(void *args, zctx_t *ctx, void *pipe);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */

