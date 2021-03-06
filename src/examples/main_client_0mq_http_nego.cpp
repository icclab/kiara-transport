/*
 * main_client_0mq_http.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: habl
 */

#include "../core/KT_Zeromq.hpp"
#include "../core/KT_Msg.hpp"
#include "../core/KT_HTTP_Parser.hpp"
#include "../core/KT_HTTP_Responder.hpp"
#include "../core/negotiation.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

int main ()
{
	
	char *response;
	int ret = 0;
	
	neg_ctx_t *neg_ctx = neg_init();
	
	neg_set_local_capability(neg_ctx, "network.transport-protocols.tcp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.transport-protocols.udp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.transport-port.80.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.transport-port.*.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.transport-protocols.udp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.user-protocols.suuuuu.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.user-protocols.notnull.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.communication-paradigm.req-rep.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "network.communication-paradigm.pub-su.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.tls.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.ssl.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "application.application-type.stream.prec", "SHOULD");
	neg_ctx->host = "localhost";
	neg_ctx->port = 5556;
	response = neg_send_offer(neg_ctx);
	
	if(neg_ctx->kiara_endpoint == 0){
		printf("Not a KIARA endpoint\n");
	}
	else {
		if(neg_ctx->client_nego == 1) {
			printf("This is it:\n %s \n", response);
			neg_negotiate_remote(neg_ctx, "some_unique_id", response);
		}
		else {
			int ret = neg_set_final_capabilities(neg_ctx, response);
		}
	}

	KT_Configuration config;
	
	config.negotiation(neg_ctx);

	// Or alternatively:
	// config.set_transport_layer( KT_TCP );
	// config.set_hostname("localhost");
	// config.set_port_number( 5555 );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	KT_Session* session = nullptr;

	if ( 0 != connection->connect(&session) )
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

	exit ( 0 );
}
