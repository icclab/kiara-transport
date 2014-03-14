/* 
 * File:   reco_engine.h
 * Author: aepp
 *
 * Created on 25. November 2013, 16:45
 */
#include "negotiation.h"
#ifdef	__cplusplus
	#include <iostream>
#endif
#include <czmq.h>

#ifndef RECO_ENGINE_H
#define	RECO_ENGINE_H

#ifdef	__cplusplus
class RecoServer {
public:
	RecoServer(char *endpoint);
	~RecoServer();
	int RunServer();
private:
	std::string host;
};
#endif

#ifdef	__cplusplus
extern "C" {
#endif
	
void* init_reco_server(char* endpoint);
void reco_run_server(void *reco_server);
int reco_send_offer (neg_ctx_t *neg_ctx);

#ifdef	__cplusplus
}
#endif

#endif	/* RECO_ENGINE_H */

