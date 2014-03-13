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

	config.set_host( KT_TCP, "localhost", 5555);

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
