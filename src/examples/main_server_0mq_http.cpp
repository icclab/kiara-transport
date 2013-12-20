/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

void callback_handler ( KT_Msg&, KT_Session*, KT_Connection* );
void Dump ( const void* mem, unsigned int n );

int main ()
{

	KT_Configuration config;
	config.set_application_type ( KT_STREAM );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	sleep (300);

	connection->unbind();

	exit ( 0 );
}

void callback_handler ( KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	std::cout << msg.get_payload().data() << std::endl;
	std::string payload ( "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nHello World\r\n" );
	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );
}
