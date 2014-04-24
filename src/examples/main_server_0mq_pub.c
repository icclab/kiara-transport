/*
 * main_server_0mq_pub.c
 *
 *  Created on: Apr 22, 2014
 *      Author: habl
 */


#include <stdlib.h>
#include <string.h>
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
    kt_configuration_set_application_type( config, KT_PUBLISHSUBSCRIBE );
    kt_configuration_set_hostname( config, "*" );
    kt_configuration_set_port( config, 6060 );

    kt_conn_session_t* conn_session = kt_init_server(config, NULL);
    kt_run_server(conn_session);

    while (1)
    {
        kt_msg_t* msg = kt_msg_new();
        char* payload = malloc(sizeof(char)*6);
        strcpy(payload, "hello");
        kt_msg_set_payload(msg, (void*)payload, 6);

        kt_send(conn_session, msg, 0);
        sleep (1);
    }

    kt_stop_server(conn_session, 0);
}
