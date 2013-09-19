/* 
 * File:   kt_server.c
 * Author: aepp
 *
 * Created on 26. Juli 2013, 14:02
 */

#include "kt_server.h"
#include "debug.h"

static void _server_worker(void *args, zctx_t *ctx, void *pipe);
static void* _connect_to_backend(zctx_t *ctx, bool israw);
static void _disconnect_from_backend(zctx_t *ctx, void* socket);
static kt_messageraw_t* _recv_message(kt_srvctx_t *kt_ctx, void *sock);
static int _send_message(kt_srvctx_t *kt_ctx, void *sock, kt_messageraw_t *msg);

//Validate the config params here and return a context

kt_srvctx_t *kt_init_server(kt_connconf_t config)
{
	//TODO: Validate params and check if server can be started
	//TODO: Set parameters on context
	kt_srvctx_t *kt_ctx;
	kt_ctx = malloc(sizeof(kt_srvctx_t));
	kt_ctx->config = config;
	kt_ctx->ctx = zctx_new();

	char *endpoint = compile_endpoint_string(config);
	debug("configured endpoint: %s\n", endpoint);

	kt_ctx->frontend = zsocket_new(kt_ctx->ctx, ZMQ_ROUTER);
	//Bring the socket in correct mode
	if (kt_ctx->config.network_config.application != ZEROMQ)
		zsocket_set_router_raw(kt_ctx->frontend, 1);
	zsocket_bind(kt_ctx->frontend, endpoint);

	//The worker sockets are talking via inproc
	kt_ctx->backend = zsocket_new(kt_ctx->ctx, ZMQ_DEALER);
	zsocket_bind(kt_ctx->backend, "inproc://backend");

	free(endpoint);
	return kt_ctx;
}

//The main server function, accessed by the world

int kt_run_server(kt_srvctx_t *kt_ctx, kt_messageraw_t *(*f)(kt_messageraw_t* msgData))
{
	//Launch the pool
	//int thread_nbr;
	//for (thread_nbr = 0; thread_nbr < 5; thread_nbr++)
	struct forking_params_hack args;
	args.f = f;
	args.kt_ctx = kt_ctx;
	zthread_fork(kt_ctx->ctx, _server_worker, &args);

	//connect workers and frontend
	zmq_proxy(kt_ctx->frontend, kt_ctx->backend, NULL);

	return 1;
}

int kt_stop_server(kt_srvctx_t *kt_ctx)
{
	//TODO: We never get here, save shutdown
	zctx_destroy(&(kt_ctx->ctx));
	return 0;
}

static void _server_worker(void *args, zctx_t *ctx, void *pipe)
{
	struct forking_params_hack* argstruct = (struct forking_params_hack*) args;
	kt_messageraw_t* (*f)(kt_messageraw_t * msg) = argstruct->f;
	kt_srvctx_t *srvctx = argstruct->kt_ctx;

	kt_messageraw_t *msg;

	void *sock = _connect_to_backend(ctx, srvctx->config.network_config.application == ZEROMQ ? false : true);
	for (;;)
	{
		msg = _recv_message(srvctx, sock);
		msg = f(msg);
		_send_message(srvctx, sock, msg);

	}
	_disconnect_from_backend(ctx, sock);
}

static void* _connect_to_backend(zctx_t *ctx, bool israw)
{
	void *sock = NULL;
	if (israw) {
		debug("create a raw socket for incoming data\n");
		sock = zsocket_new(ctx, ZMQ_DEALER);
	} else {
		debug("create a ZMQ_REP socket for incoming messages\n");
		sock = zsocket_new(ctx, ZMQ_REP);
	}
	assert(sock);
	zsocket_connect(sock, "inproc://backend");
	debug("connected to dispatcher backend, waiting for messages\n");
	return sock;
}

static void _disconnect_from_backend(zctx_t *ctx, void* socket)
{
	zsocket_disconnect(socket, "inproc://backend");
	zsocket_destroy(ctx, socket);
	debug("disconnected from dispatcher backend\n");
}

static kt_messageraw_t* _recv_message(kt_srvctx_t *kt_ctx, void *sock)
{
	zmsg_t *m = zmsg_recv(sock);
	assert(m);
	kt_messageraw_t *msg = malloc(sizeof(kt_messageraw_t));
	if (kt_ctx->config.network_config.application != ZEROMQ)
		msg->_identity = zmsg_unwrap(m);
	msg->msgData = zmsg_popstr(m);
	zmsg_destroy(&m);
	return msg;
}

static int _send_message(kt_srvctx_t *kt_ctx, void *sock, kt_messageraw_t *msg)
{
	zframe_t *frame_reply = zframe_new(msg->msgData, strlen(msg->msgData));
	if (kt_ctx->config.network_config.application != ZEROMQ)
		zframe_send(&msg->_identity, sock,
		ZFRAME_MORE + ZFRAME_REUSE);
	zframe_send(&frame_reply, sock, ZFRAME_REUSE);
	zframe_destroy(&frame_reply);
	if (kt_ctx->config.network_config.application != ZEROMQ)
		zframe_destroy (&msg->_identity);
	free (msg->msgData);
	free (msg);
	return 0;
}
