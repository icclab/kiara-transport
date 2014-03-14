/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "KT_Zeromq.hpp"
#include "KT_HTTP_Parser.hpp"
#include "KT_HTTP_Responder.hpp"
#include "reco_engine.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace KIARA::Transport;

void callback_handler(KT_Msg&, KT_Session*, KT_Connection*);

RecoServer::RecoServer(char* endpoint) {
	host = endpoint;
	//url = std::string(endpoint);
}

RecoServer::~RecoServer() {
	//delete[];
}

int RecoServer::RunServer() {
	KT_Configuration config;
	config.set_application_type(KT_STREAM);

	KT_Connection* connection = new KT_Zeromq();
	connection->set_configuration(config);

	connection->register_callback(&callback_handler);
	connection->bind(host);

	sleep(300);

	connection->unbind();

	return 0;
}

void callback_handler(KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	KT_HTTP_Parser parser(msg);
	std::cout << parser << std::endl;

	//std::string payload ( "Hello World, welcome to KIARA::Transport" );
	//payload = KT_HTTP_Responder::generate_200_OK( std::vector<char>(payload.begin(), payload.end()) );
	std::string payload = KT_HTTP_Responder::generate_418_IM_A_TEAPOT();

	KT_Msg message;
	message.set_payload(payload);

	obj->send(message, (*sess), 0);
}

#ifdef	__cplusplus
extern "C" {
#endif

void* init_reco_server(char *endpoint) {
	RecoServer *out = new RecoServer(endpoint);
	return ((void*)out);
}

void reco_run_server(void *reco_server){
	RecoServer *tmp_reco_server = ((RecoServer*)reco_server);
	tmp_reco_server->RunServer();
}

int reco_send_offer (neg_ctx_t *neg_ctx) {
	return 1;
}

#ifdef	__cplusplus
}
#endif