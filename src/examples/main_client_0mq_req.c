/*
 * main_client_0mq_req.c
 *
 *  Created on: Mar 14, 2014
 *      Author: habl
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

int main ()
{
    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config = kt_configuration_create();
    kt_configuration_set_network_layer( config, KT_IPLEGACY );
    kt_configuration_set_application_layer( config, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config, KT_TCP );
    kt_configuration_set_application_type( config, KT_REQUESTREPLY );
    kt_configuration_set_hostname( config, "localhost" );
    kt_configuration_set_port( config, 5555 );

    kt_conn_session_t* conn_session = kt_connect( config );

    kt_msg_t* message = kt_msg_new();
    char* payload = malloc(5);
    asprintf ( &payload, "hello");
    kt_msg_set_payload( message, payload, 5 );

    kt_send( conn_session, message, 0 );
    kt_msg_t* reply = kt_recv( conn_session, 0 );

    printf("From Server: %.*s\n", kt_msg_get_payload_size(reply), (char*)kt_msg_get_payload(reply));
}
