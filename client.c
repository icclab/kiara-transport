/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 7. August 2013, 17:00
 */
#include <czmq.h>
#include <zmq.h>

#include "client.h"
#include "kmessage.h"
#include "ktransport.h"

//TODO: Implementation in existing message.c in the KIARA Project.
//TODO: curl is used as http-client
//TODO: For KIARA2KIARA traffic, we use ZMQ DEALER Clients with identity
static void *client_native(void *args) {
    zctx_t *ctx = zctx_new();
    void *client = zsocket_new(ctx, ZMQ_DEALER);

    //  Set random identity to make tracing easier
    char identity [10];
    sprintf(identity, "%04X-%04X", randof(0x10000), randof(0x10000));
    //zsockopt_set_identity(client, identity);
    zsocket_connect(client, "tcp://localhost:5570");
	
	zstr_sendf(client, "request #%d", 1);
	zmsg_t *msg = zmsg_recv(client);
    zframe_print(zmsg_last(msg), identity);
    zmsg_destroy(&msg);
    zctx_destroy(&ctx);
    return NULL;
}

static void *client_curl(void *args) {
    
}

int main(int argc, char** argv) {
	client_native(NULL);
	//zclock_sleep (5 * 1000);
    return (EXIT_SUCCESS);
}