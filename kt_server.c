/* 
 * File:   kt_server.c
 * Author: aepp
 *
 * Created on 26. Juli 2013, 14:02
 */
#include <czmq.h>
#include <zmq.h>

#include "kt_server.h"
#include "kiara.h"
#include "ktransport.h"

//Validate the config params here and return a context

kt_srvctx *kt_init_server(kt_srvconf config) {
	//TODO: Validate params and check if server can be started
	//TODO: Set parameters on context
	kt_srvctx *kt_ctx;
	kt_ctx = malloc(sizeof (kt_srvctx));
	kt_ctx->config = config;
        kt_ctx->ctx = zctx_new();

        //This is the front-end, usually talks TCP
	kt_ctx->frontend = zsocket_new(kt_ctx->ctx, ZMQ_ROUTER);
	//Bring the socket in correct mode
	zsocket_set_router_raw(kt_ctx->frontend, kt_ctx->config.type);
	zsocket_bind(kt_ctx->frontend, kt_ctx->config.base_url);

	//The worker sockets are talking via inproc
	kt_ctx->backend = zsocket_new(kt_ctx->ctx, ZMQ_DEALER);
	zsocket_bind(kt_ctx->backend, "inproc://backend");

	return kt_ctx;
}

//The main server function, accessed by the world

int kt_run_server(kt_srvctx *kt_ctx, void (*f)(kt_messageraw* msgData)) {
	//Launch the pool
	int thread_nbr;
	for (thread_nbr = 0; thread_nbr < 5; thread_nbr++)
		zthread_fork(kt_ctx->ctx, server_worker, f);

	//connect workers and frontend
	zmq_proxy(kt_ctx->frontend, kt_ctx->backend, NULL);

	return 1;
}

int kt_stop_server(kt_srvctx *kt_ctx){
    	//TODO: We never get here, save shutdown
	//TODO: Put this in stopServer
	zctx_destroy(&(kt_ctx->ctx));
}

//The main worker function

static void server_worker(void *args, zctx_t *ctx, void *pipe) {
	void *worker = zsocket_new(ctx, ZMQ_DEALER);
	void (*f)(kt_messageraw* msgData) = args;
	zsocket_connect(worker, "inproc://backend");

	for (;;) {
		//At the moment, just send back Hello World with http header
		char *http_ok = "HTTP/1.0 200 OK\r\nVary: Accept-Encoding, Accept-Language\r\nConnection: Close\r\nContent-Type: text/plain\r\nContent-Length:12\r\n\r\nHello, World";

		zmsg_t *msg = zmsg_recv(worker);
		zframe_t *frame_identity = zmsg_pop(msg);
		zframe_t *frame_content = zmsg_pop(msg);
		assert(frame_content);
		assert(frame_identity);

		//parse the http request
		//kmessage_parse(frame_content);

		zmsg_destroy(&msg);

		//TODO: Put this in server_worker_compose_response
		zframe_t *frame_reply = zframe_new(http_ok, strlen(http_ok));
		//Pass the correct args here after parsing
		//f("1", "1", "1");
		//kmessage_compose();

		zframe_send(&frame_identity, worker, ZFRAME_MORE + ZFRAME_REUSE);
		zframe_send(&frame_reply, worker, ZFRAME_REUSE);

		zframe_destroy(&frame_identity);
		zframe_destroy(&frame_content);
		zframe_destroy(&frame_reply);
	}
}