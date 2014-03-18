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

class RecoClient {
public:
	RecoClient(char *serverhost);
	~RecoClient();
private:
	std::string host;
};
#endif

#ifdef	__cplusplus
extern "C" {
#endif
	
void* init_reco_server(char* endpoint);
void reco_run_server(void *reco_server);
void* reco_send_offer (char* endpoint);

#ifdef	__cplusplus
}
#endif

#endif	/* RECO_ENGINE_H */

