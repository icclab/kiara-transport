/*
 * main_client_0mq_sub.c
 *
 *  Created on: Apr 24, 2014
 *      Author: habl
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

int main ()
{
    // Setup subscriber
    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config = kt_configuration_create();
    kt_configuration_set_network_layer( config, KT_IPLEGACY );
    kt_configuration_set_application_layer( config, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config, KT_TCP );
    kt_configuration_set_application_type( config, KT_PUBLISHSUBSCRIBE );
    kt_configuration_set_hostname( config, "localhost" );
    kt_configuration_set_port( config, 6060 );

    kt_conn_session_t* conn_session = kt_connect( config );

    while (1)
    {
        // Blocks until message arrived
        kt_msg_t* message = kt_recv(conn_session, 0);

        // A little bit of pretty-printing ...
        printf("  _______    _     __          __\n");
        printf(" |___  / |  | |   /\\ \\        / /\n");
        printf("    / /| |__| |  /  \\ \\  /\\  / / \n");
        printf("   / / |  __  | / /\\ \\ \\/  \\/ /  \n");
        printf("  / /__| |  | |/ ____ \\  /\\  /   \n");
        printf(" /_____|_|  |_/_/    \\_\\/  \\/    \n");

        // Imagine this would be a receipt printer or similar
        time_t ltime;
        ltime=time(NULL);
        printf("%s\n\n",asctime( localtime(&ltime) ) );

        // Actually print the received message
        printf("%.*s\n", kt_msg_get_payload_size(message), (char*)kt_msg_get_payload(message));
    }
}
