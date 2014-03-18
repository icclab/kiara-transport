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
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

int main ()
{

	KT_Configuration config;
	config.set_application_type ( KT_STREAM );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	KT_Session* session = nullptr;
	KT_Client endpoint;
	endpoint.set_endpoint("tcp://localhost:81/negotiation");
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

	exit ( 0 );
}
