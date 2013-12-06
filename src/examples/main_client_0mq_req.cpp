/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>

using namespace KIARA::Transport;

int main ()
{
	KT_Connection* connection = new KT_Zeromq ();

	KT_Client endpoint;
	endpoint.set_endpoint ( "tcp://127.0.0.1:5555" );
	KT_Session *session = connection->connect ( endpoint );

	std::string payload ( "Hello" );
	KT_Msg message;
	message.set_payload ( payload );

	connection->send ( message, (*session), 0 );

	KT_Msg* reply = connection->recv ( (*session), 0 );

	std::string answer ( reply->get_payload().data() );
	std::cout << answer << std::endl;

	connection->disconnect ( (*session) );

	exit ( 0 );
}
