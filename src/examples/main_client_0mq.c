#include "../../include/k_transport.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
  kt_conn_session_t* sess = kt_connect ("tcp://160.85.122.107:5555");
  
  kt_msg_t* msg = kt_msg_new();
  char* payload = "Blabla";
  kt_msg_set_payload (msg, payload, 6, NULL);

  kt_send ( sess, msg, 0);
  msg = kt_recv ( sess, 0 );
  printf ("%s\n", (char*) kt_msg_get_payload(msg));

  kt_disconnect (sess);
	return 0;
}
