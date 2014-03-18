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
	std::string payload("");
	switch (parser.method) {
		//GET Request
		case 1:
			payload.append ( "POST request are currently not enabled" );
			payload = KT_HTTP_Responder::generate_400_BAD_REQUEST( std::vector<char>(payload.begin(), payload.end()) );
			break;
		//POST Request
		case 3:
			payload.append ( "POST request are currently not enabled" );
			payload = KT_HTTP_Responder::generate_400_BAD_REQUEST( std::vector<char>(payload.begin(), payload.end()) );
			break;
		//Anything else
		default:
			payload.append ( "Request type is not supported" );
			payload = KT_HTTP_Responder::generate_400_BAD_REQUEST( std::vector<char>(payload.begin(), payload.end()) );
	}
	//DEBUG Only
	std::cout << parser.get_payload() << std::endl;
	std::cout << parser.get_url() << std::endl;	

	KT_Msg message;
	message.set_payload(payload);

	obj->send(message, (*sess), 0);
}

RecoClient::RecoClient(char* endpoint) {
	host = endpoint;
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
	std::string payload ( "PUT / HTTP/1.1\r\nUser-Agent: KIARA\r\nHost: localhost:5555\r\nContent-Length: 41\r\n\r\nHello World, welcome to KIARA::Transport" );

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
	std::cout << parser << std::endl;

	return 0;
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

int reco_send_offer (char *endpoint) {
	RecoClient *out = new RecoClient(endpoint);
	return ((void*)out);
}

#ifdef	__cplusplus
}
#endif