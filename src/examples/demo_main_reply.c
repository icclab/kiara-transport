/*
 * main_client_0mq_rep.c
 *
 *  Created on: Mar 14, 2014
 *      Author: habl
 */


#include <stdlib.h>
#include <stdio.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

kt_conn_session_t* conn_session_publisher = NULL;

void cb (kt_conn_session_t*, kt_msg_t*);
void cb (kt_conn_session_t* conn_sess, kt_msg_t* msg) {
    printf("From Client: %.*s\n", kt_msg_get_payload_size(msg), (char*)kt_msg_get_payload(msg));
    kt_msg_t* message = kt_msg_new();
    char* payload = malloc(5);
    asprintf ( &payload, "hello");
    kt_msg_set_payload( message, payload, 5 );

    kt_send(conn_session_publisher, msg, 0);

    kt_send( conn_sess, message, 0 );
}

int main ()
{
    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config_reply = kt_configuration_create();
    kt_configuration_set_network_layer( config_reply, KT_IPLEGACY );
    kt_configuration_set_application_layer( config_reply, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config_reply, KT_TCP );
    kt_configuration_set_application_type( config_reply, KT_REQUESTREPLY );
    kt_configuration_set_hostname( config_reply, "*" );
    kt_configuration_set_port( config_reply, 5555 );

    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config_publisher = kt_configuration_create();
    kt_configuration_set_network_layer( config_publisher, KT_IPLEGACY );
    kt_configuration_set_application_layer( config_publisher, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config_publisher, KT_TCP );
    kt_configuration_set_application_type( config_publisher, KT_PUBLISHSUBSCRIBE );
    kt_configuration_set_hostname( config_publisher, "*" );
    kt_configuration_set_port( config_publisher, 6060 );

    kt_conn_session_t* conn_session_reply = kt_init_server(config_reply, &cb);
    kt_run_server(conn_session_reply);

    conn_session_publisher = kt_init_server(config_publisher, NULL);
    kt_run_server(conn_session_publisher);

    sleep (600);

    kt_stop_server(conn_session_publisher, 0);
    kt_stop_server(conn_session_reply, 0);
}
