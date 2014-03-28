/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../core/KT_Zeromq.hpp"
#include <iostream>

using namespace KIARA::Transport;


int main ()
{
	KT_Configuration config;
	config.set_application_type ( KT_REQUESTREPLY );
	config.set_transport_layer( KT_TCP );
	config.set_hostname("localhost");
	config.set_port_number( 5555 );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	KT_Session* session = nullptr;

	if ( 0 != connection->connect ( &session ) )
	{
		std::cerr << "Failed to connect" << std::endl;
	}

	// Be sure to NULL-terminate the string
	std::string payload ( "Hello World, here you can store up to 1024bytes of payload\0" );
	KT_Msg message;
	message.set_payload ( payload );

	connection->send ( message, *session, 0 );

	KT_Msg reply;
	connection->recv ( *session, reply, 0 );

	std::vector<char> answer_vector = reply.get_payload();
	std::string answer(answer_vector.begin(), answer_vector.end());
	std::cout << answer << std::endl;

	connection->disconnect ( (*session) );


	exit ( 0 );
}
