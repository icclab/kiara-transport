/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../core/KT_Zeromq.hpp"
#include "../core/KT_HTTP_Parser.hpp"
#include "../core/KT_HTTP_Responder.hpp"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

void callback_handler ( KT_Msg&, KT_Session*, KT_Connection* );

int main ()
{

	KT_Configuration config;
	config.set_application_type ( KT_STREAM );
	config.set_transport_layer( KT_TCP );
	config.set_hostname( "*" );
	config.set_port_number( 9090 );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	connection->register_callback( &callback_handler );
	connection->bind();

	sleep (600);

	connection->unbind();

	exit ( 0 );
}

void callback_handler ( KT_Msg& msg, KT_Session* sess, KT_Connection* obj ) {
	KT_HTTP_Parser parser (msg);
	std::cout << parser << std::endl;

	//std::string payload ( "Hello World, welcome to KIARA::Transport" );
	//payload = KT_HTTP_Responder::generate_200_OK( std::vector<char>(payload.begin(), payload.end()) );
	std::string payload = KT_HTTP_Responder::generate_418_IM_A_TEAPOT();

	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );
}
