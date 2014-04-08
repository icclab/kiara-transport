/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "KT_Zeromq.hpp"
#include "KT_HTTP_Parser.hpp"
#include "KT_HTTP_Responder.hpp"
#include "KT_HTTP_Requester.hpp"
#include "reco_engine.h"
#include "registry.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace KIARA::Transport;

void callback_handler(KT_Msg&, KT_Session*, KT_Connection*);

RecoServer::RecoServer(char* endpoint, neg_ctx_t* neg_ctx) {
	host = endpoint;
	ctx = neg_ctx;
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
	
	connection->get_session().find(ctx->host)->second->set_k_user_data(ctx);
	
	sleep(600);

	connection->unbind();

	return 0;
}

void callback_handler(KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	KT_HTTP_Parser parser(msg);
	neg_ctx_t *neg_ctx = (neg_ctx_t*) sess->get_k_user_data();
	std::cout << neg_ctx->host << std::endl;
	std::string payload("");
	if(parser.get_url().compare(0, 12, "/negotiation") != 0){
		payload.append ( "Not a negotiation endpoint!" );
		payload = KT_HTTP_Responder::generate_400_BAD_REQUEST( std::vector<char>(payload.begin(), payload.end()) );
	}
	else {
		switch (parser.method) {
			//GET Request
			case 1:
				payload.append (reg_get_local_capability_json(neg_ctx));
				payload = KT_HTTP_Responder::generate_200_OK( std::vector<char>(payload.begin(), payload.end()) );
				break;
			//POST Request
			case 3:
				std::cout << parser.get_payload() << std::endl;
				reg_set_remote_capability(neg_ctx, parser.get_identifier().c_str(), parser.get_payload().c_str());
				
				payload.append ( neg_negotiate(neg_ctx, parser.get_identifier().c_str()) );
				payload = KT_HTTP_Responder::generate_200_OK( std::vector<char>(payload.begin(), payload.end()) );
				break;
			//Anything else
			default:
				payload.append ( "Request type is not supported" );
				payload = KT_HTTP_Responder::generate_400_BAD_REQUEST( std::vector<char>(payload.begin(), payload.end()) );
		}
	}
	//DEBUG Only
	std::cout << parser.get_payload() << std::endl;
	std::cout << parser.get_identifier() << std::endl;

	KT_Msg message;
	message.set_payload(payload);

	obj->send(message, (*sess), 0);
}

RecoClient::RecoClient(char* serverhost, neg_ctx_t* neg_ctx) {
	host = serverhost;
	KT_Configuration config;
	config.set_application_type ( KT_STREAM );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	KT_Session* session = nullptr;
	KT_Client endpoint;
	endpoint.set_endpoint(host);
	if (0 != connection->connect(endpoint, &session))
	{
		std::cerr << "Failed to connect" << std::endl;
	}

	if (nullptr == session)
	{
		std::cerr << "Session object was not set" << std::endl;
	}

	KT_Msg request;
	std::string payload(reg_get_local_capability_json(neg_ctx));
	std::cout << payload << std::endl;
	payload = KT_HTTP_Requester::generate_request("POST", "localhost:5555", "/negotiation",  std::vector<char>(payload.begin(), payload.end()));
	
	request.set_payload(payload);

	if (0 != connection->send(request, *session, 0))
	{
		std::cerr << "Failed to send payload" << std::endl;
	}

	KT_Msg reply;
	if (0 != connection->recv(*session, reply, 0))
		std::cerr << "Receive failed" << std::endl;

	KT_HTTP_Parser parser (reply);
	std::cout << "Parser found in body:" << std::endl;
	response = parser.get_payload();
}

char *RecoClient::GetPayload() {
	return (char *) response.c_str();
}

#ifdef	__cplusplus
extern "C" {
#endif

void* init_reco_server(char *endpoint, neg_ctx_t *neg_ctx) {
	RecoServer *out = new RecoServer(endpoint, neg_ctx);
	return ((void*)out);
}

void reco_run_server(void *reco_server){
	RecoServer *tmp_reco_server = ((RecoServer*)reco_server);
	tmp_reco_server->RunServer();
}

char* reco_send_offer (char *endpoint, neg_ctx_t* neg_ctx) {
	RecoClient *out = new RecoClient(endpoint, neg_ctx);
	return out->GetPayload();
}

#ifdef	__cplusplus
}
#endif