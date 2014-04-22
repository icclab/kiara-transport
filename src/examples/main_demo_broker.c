/*
 * main_demo_broker.c
 *
 *  Created on: Apr 15, 2014
 *      Author: habl
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

void cb (kt_conn_session_t*, kt_msg_t*);
kt_msg_t* hello_request_reply(kt_msg_t*);

void cb (kt_conn_session_t* conn_sess, kt_msg_t* msg) {
    // When we get the HTTP request, we connect to a req/rep service and
    // forward the answer back to the HTTP client

    printf("From Client: %.*s\n", kt_msg_get_payload_size(msg), (char*)kt_msg_get_payload(msg));

    kt_msg_t* message = hello_request_reply(msg);
    message = kt_msg_http_reply(kt_msg_get_payload(message), kt_msg_get_payload_size(message));

    kt_send( conn_sess, message, 0 );
}

kt_msg_t* hello_request_reply (kt_msg_t* msg)
{
    kt_configuration_t* config = kt_configuration_create();
    kt_configuration_set_network_layer( config, KT_IPLEGACY );
    kt_configuration_set_application_layer( config, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config, KT_TCP );
    kt_configuration_set_application_type( config, KT_REQUESTREPLY );
    kt_configuration_set_hostname( config, "localhost" );
    kt_configuration_set_port( config, 5555 );

    kt_conn_session_t* conn_session = kt_connect( config );

    kt_send( conn_session, msg, 0 );
    kt_msg_t* reply = kt_recv( conn_session, 0 );

    kt_disconnect(conn_session);
    return reply;
}

int main ()
{
    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config = kt_configuration_create();
    kt_configuration_set_network_layer( config, KT_IPLEGACY );
    kt_configuration_set_application_layer( config, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config, KT_TCP );
    kt_configuration_set_application_type( config, KT_WEBSERVER );
    kt_configuration_set_hostname( config, "*" );
    //kt_configuration_set_port( config, 8080 );

    kt_conn_session_t* conn_session = kt_init_server(config, &cb);
    kt_run_server(conn_session);

    sleep (600);

    kt_stop_server(conn_session, 0);
}
