/*
 * main_client_0mq_rep.c
 *
 *  Created on: Mar 14, 2014
 *      Author: habl
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/k_transport.h"
#include "../../src/core/KT_Configuration.h"

kt_conn_session_t* conn_session_publisher = NULL;

void cb (kt_conn_session_t*, kt_msg_t*);
void cb (kt_conn_session_t* conn_sess, kt_msg_t* msg) {

    // Print the message received from the broker
    printf("From Client:\n %.*s\n", kt_msg_get_payload_size(msg), (char*)kt_msg_get_payload(msg));

    // Prepare reply or do_complex_computation();
    // We can safely use strlen on result as it's zero-terminated
    char* result = "\n\nHello, I'm your result.";

    kt_msg_t* published_message = kt_msg_new();
    kt_msg_t* reply = kt_msg_new();

    // Prepare payload to publish
    size_t mem_to_alloc_for_publishing = kt_msg_get_payload_size(msg);
    mem_to_alloc_for_publishing += strlen(result);
    char* payload_for_publishing = malloc(mem_to_alloc_for_publishing);

    strncpy(payload_for_publishing, (char*)kt_msg_get_payload(msg), kt_msg_get_payload_size(msg));
    strncpy(payload_for_publishing + kt_msg_get_payload_size(msg), result, strlen(result));
    kt_msg_set_payload( published_message, payload_for_publishing, mem_to_alloc_for_publishing );

    // Prepare payload for reply
    char* payload_for_reply = malloc(strlen(result));
    strncpy(payload_for_reply, result, strlen(result));
    kt_msg_set_payload(reply, payload_for_reply, strlen(result));

    // Publish results
    kt_send(conn_session_publisher, published_message, 0);

    // Reply with the results
    kt_send( conn_sess, reply, 0 );
    kt_msg_destroy(msg);
}

int main ()
{
    // Setup reply-server
    // FIXME: Memory leak, also create destroy function
    kt_configuration_t* config_reply = kt_configuration_create();
    kt_configuration_set_network_layer( config_reply, KT_IPLEGACY );
    kt_configuration_set_application_layer( config_reply, KT_ZEROMQ );
    kt_configuration_set_transport_layer( config_reply, KT_TCP );
    kt_configuration_set_application_type( config_reply, KT_REQUESTREPLY );
    kt_configuration_set_hostname( config_reply, "*" );
    kt_configuration_set_port( config_reply, 5555 );

    // Setup publisher resp. publish-server
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

    // Here again we could add a signal handler
    sleep (600);

    kt_stop_server(conn_session_publisher, 0);
    kt_stop_server(conn_session_reply, 0);
}
