/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>

using namespace KIARA::Transport;

void callback_handler ( KIARA::Transport::KT_Msg& msg, KIARA::Transport::KT_Session* sess, KIARA::Transport::KT_Connection* obj) {
	std::cout << "Callback called ...";
	std::cout << msg.get_payload().data() << std::endl;
	std::string payload ( "Hello" );
	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );

}

int main ()
{
	KT_Connection* connection = new KT_Zeromq ();

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	exit ( 0 );
}
