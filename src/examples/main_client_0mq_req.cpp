/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include <iostream>

using namespace KIARA::Transport;

int main()
{
	KT_Connection* connection = new KT_Zeromq();
	KT_Client endpoint;
	endpoint.set_endpoint("tcp://127.0.0.1:5555");
	connection->connect(endpoint);
	std::string payload ("Hello");
	KT_Msg* message = new KT_Msg ();
	message->set_payload (payload);

/*
  kt_conn_session_t* sess = kt_connect ("tcp://160.85.122.107:5555");

  kt_msg_t* msg = kt_msg_new();
  char* payload = "Blabla";
  kt_msg_set_payload (msg, payload, 6, NULL);

  kt_send ( sess, msg, 0);
  msg = kt_recv ( sess, 0 );
  printf ("%s\n", (char*) kt_msg_get_payload(msg));

  kt_disconnect (sess);
	return 0;
*/
}
