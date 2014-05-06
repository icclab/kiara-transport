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
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

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
	config.set_transport_layer(KT_TCP);
	config.set_hostname("*");
	config.set_port_number(ctx->port);

	KT_Connection* connection = new KT_Zeromq();
	connection->set_configuration(config);

	connection->register_callback(&callback_handler);
	connection->bind();

	connection->get_session()->begin()->second->set_k_user_data(ctx);

	sleep(600);

	connection->unbind();

	return 0;
}

void callback_handler(KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	KT_HTTP_Parser parser(msg);
	neg_ctx_t *neg_ctx = (neg_ctx_t*) sess->get_k_user_data();
	std::cout << neg_ctx->host << std::endl;
	std::string payload("");
	if (parser.get_url().compare(0, 12, "/negotiation") != 0) {
		payload.append("Not a negotiation endpoint!");
		payload = KT_HTTP_Responder::generate_400_BAD_REQUEST(std::vector<char>(payload.begin(), payload.end()));
	} else {
		switch (parser.method) {
				//GET Request
			case 1:
				payload.append(reg_get_local_capability_json(neg_ctx));
				payload = KT_HTTP_Responder::generate_200_OK(std::vector<char>(payload.begin(), payload.end()));
				break;
				//POST Request
			case 3:
				std::cout << parser.get_payload() << std::endl;
				reg_set_remote_capability(neg_ctx, parser.get_identifier().c_str(), parser.get_payload().c_str());
				payload.append(neg_negotiate(neg_ctx, parser.get_identifier().c_str()));
				payload = KT_HTTP_Responder::generate_200_OK(std::vector<char>(payload.begin(), payload.end()));
				break;
				//Anything else
			default:
				payload.append("Request type is not supported");
				payload = KT_HTTP_Responder::generate_400_BAD_REQUEST(std::vector<char>(payload.begin(), payload.end()));
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

	KT_Configuration config;
	config.set_application_type(KT_STREAM);

	config.set_host(KT_TCP, "localhost", 5555);

	KT_Connection* connection = new KT_Zeromq();
	connection->set_configuration(config);

	KT_Session* session = nullptr;

	if (0 != connection->connect(&session)) {
		remote_endpoint = 25;
	} else {

		if (nullptr == session) {
			remote_endpoint = 30;
		}

		KT_Msg request;
		std::string payload(reg_get_local_capability_json(neg_ctx));
		payload = KT_HTTP_Requester::generate_request("POST", "localhost:5555", "/negotiation", std::vector<char>(payload.begin(), payload.end()));

		request.set_payload(payload);

		if (0 != connection->send(request, *session, 0)) {
			remote_endpoint = 35;
		}

		KT_Msg reply;
		if (0 != connection->recv(*session, reply, 0))
			remote_endpoint = 40;

		KT_HTTP_Parser parser(reply);
		response = parser.get_payload();
	}
}

char *RecoClient::GetPayload() {
	return (char *) response.c_str();
}

#ifdef	__cplusplus
extern "C" {
#endif

	void* init_reco_server(char *endpoint, neg_ctx_t *neg_ctx) {
		RecoServer *out = new RecoServer(endpoint, neg_ctx);
		return ((void*) out);
	}

	void reco_run_server(void *reco_server) {
		RecoServer *tmp_reco_server = ((RecoServer*) reco_server);
		tmp_reco_server->RunServer();
	}

	char* reco_send_offer(char *endpoint, neg_ctx_t* neg_ctx) {
		RecoClient *out = new RecoClient(endpoint, neg_ctx);

		switch (out->remote_endpoint) {

			case 25:
				return "";
				break;

			case 0:
				return out->GetPayload();
				break;

			default:
				break;
		}
		return "";
	}

	int _check_remote_endpoint(char* hostname, int port) {
		struct hostent *host;
		int err, i, sock, ret;
		struct sockaddr_in sa;
		
		strncpy((char*)&sa , "" , sizeof sa);
		sa.sin_family = AF_INET;
		
		if(isdigit(hostname[0])){
			sa.sin_addr.s_addr = inet_addr(hostname);
		}
		//Resolve hostname to ip address
		else if( (host = gethostbyname(hostname)) != 0){
			strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
		}
		
        sa.sin_port = htons(port);
        //Create a socket of type internet
        sock = socket(AF_INET , SOCK_STREAM , 0);
         
        //Check whether socket created fine or not
        if(sock < 0) {
            perror("\nSocket");
            exit(1);
        }
        //Connect using that socket and sockaddr structure
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
         
        //not connected
        if( err < 0 ) {
            ret = 0;
        }
        //connected
        else{
            ret = 1;
        }
        close(sock);
		return ret;
	}

#ifdef	__cplusplus
}
#endif