#include <czmq.h>
#include <zmq.h>

#include "server.h"

//Validate the config params here and return a context
KIARAServerContext *initServer(KIARAServerConfig config){
	//TODO: Validate params and check if server can be started
	//TODO: Set parameters on context
	KIARAServerContext *context;
	context->config = config;
	return context;
}

//The main server function, accessed by the world
void *runServer(KIARAServerContext *context, void (*f)(char*, char*, char*)) {
	zctx_t *ctx = zctx_new();

	//This is the front-end, usually talks TCP
	void *frontend = zsocket_new(ctx, ZMQ_ROUTER);
	//Bring the socket in correct mode
	zsocket_set_router_raw(frontend, context->config.type);
	zsocket_bind(frontend, context->config.base_url);

	//The worker sockets are talking via inproc
	void *backend = zsocket_new(ctx, ZMQ_DEALER);
	zsocket_bind(backend, "inproc://backend");

	//Launch the pool
	int thread_nbr;
	for (thread_nbr = 0; thread_nbr < 5; thread_nbr++)
		zthread_fork(ctx, server_worker, f);

	//connect workers and frontend
	zmq_proxy(frontend, backend, NULL);

	//TODO: We never get here, save shutdown
	zctx_destroy(&ctx);
	return NULL;
}

//The main worker function
static void server_worker(void *args, zctx_t *ctx, void *pipe) {
	void *worker = zsocket_new(ctx, ZMQ_DEALER);
	void (*f)(char*, char*, char*) = args;
	zsocket_connect(worker, "inproc://backend");

	while (1) {
		//At the moment, just send back Hello World with http header
		char *http_ok = "HTTP/1.0 200 OK\r\nVary: Accept-Encoding, Accept-Language\r\nConnection: Close\r\nContent-Type: text/plain\r\nContent-Length:12\r\n\r\nHello, World";

		zmsg_t *msg = zmsg_recv(worker);
		zframe_t *frame_identity = zmsg_pop(msg);
		zframe_t *frame_content = zmsg_pop(msg);
		assert(frame_content);
		assert(frame_identity);

		//parse the http request
		server_worker_parse_request(frame_content);

		zmsg_destroy(&msg);

		zframe_t *frame_reply = zframe_new(http_ok, strlen(http_ok));
		//Pass the correct args here
		//f("1", "1", "1");

		zframe_send(&frame_identity, worker, ZFRAME_MORE + ZFRAME_REUSE);
		zframe_send(&frame_reply, worker, ZFRAME_REUSE);

		zframe_destroy(&frame_identity);
		zframe_destroy(&frame_content);
		zframe_destroy(&frame_reply);
	}
}