/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../core/KT_Zeromq.hpp"
#include "../core/Debug.hpp"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

void callback_handler ( KT_Msg&, KT_Session*, KT_Connection* );
void Dump ( const void* mem, unsigned int n );

int main ()
{

	KT_Configuration config;
	config.set_application_type ( KT_REQUESTREPLY );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	sleep (300);

	connection->unbind();

	exit ( 0 );
}

void callback_handler ( KT_Msg& msg, KT_Session* sess, KT_Connection* obj) {
	std::vector<char> answer_vector = msg.get_payload();
	std::string answer(answer_vector.begin(), answer_vector.end());
	std::cout << answer << std::endl;
	std::cout << "Memory hex dump:" << std::endl << std::endl;
	Dump ( msg.get_payload().data(), msg.get_payload().size() );

	std::string payload ( "Here comes the answer" );
	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );
}
