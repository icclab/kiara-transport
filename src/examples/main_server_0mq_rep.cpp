/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>

using namespace KIARA::Transport;

void callback_handler ( KIARA::Transport::KT_Msg& msg, KIARA::Transport::KT_Session& sess) {
	std::cout << "Callback called ...";
	std::cout << msg.get_payload().data() << std::endl;
}

int main ()
{
	KT_Connection* connection = new KT_Zeromq ();

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	exit ( 0 );
}
