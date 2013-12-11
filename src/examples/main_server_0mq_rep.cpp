/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>
#include <unistd.h>

using namespace KIARA::Transport;

void callback_handler ( KT_Msg&, KT_Session*, KT_Connection* );

int main ()
{
	KT_Connection* connection = new KT_Zeromq ();

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	sleep (5);

	connection->unbind();

	exit ( 0 );
}

void callback_handler ( KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	std::cout << "Callback called ...";
	std::cout << msg.get_payload().data() << std::endl;
	std::string payload ( "Hello" );
	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );
}
