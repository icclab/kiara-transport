/* 
 * File:   kt_server.c
 * Author: aepp
 *
 * Created on 26. Juli 2013, 14:02
 */
#include <stdio.h>
#include <czmq.h>
#include <zmq.h>

#include "debug.h"
#include "kt_server.h"

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

	void *sock = _connect_to_backend(ctx);
	for (;;)
	{
		msg = _recv_message(srvctx, sock);
		msg = f(msg);
		_send_message(srvctx, sock, msg);

	}
	_disconnect_from_backend(ctx, sock);
}

void* _connect_to_backend(zctx_t *ctx)
{
	void* sock = zsocket_new(ctx, ZMQ_REP);
	zsocket_connect(sock, "inproc://backend");
	debug("connected to dispatcher backend, waiting for messages\n");
	return sock;
}

void _disconnect_from_backend(zctx_t *ctx, void* socket)
{
	zsocket_disconnect(socket, "inproc://backend");
	zsocket_destroy(ctx, socket);
	debug("disconnected from dispatcher backend\n");
}

kt_messageraw_t* _recv_message(kt_srvctx_t *kt_ctx, void *sock)
{
	kt_messageraw_t *msg = malloc(sizeof(kt_messageraw_t));
	zmsg_t *m = zmsg_recv(sock);
	assert(m);
	if (kt_ctx->config.network_config.application != ZEROMQ)
		msg->_identity = zmsg_pop(m);
	msg->msgData = zframe_strdup(zmsg_pop(m));
	zmsg_destroy(&m);
	return msg;
}

int _send_message(kt_srvctx_t *kt_ctx, void *sock, kt_messageraw_t *msg)
{
	zframe_t *frame_reply = zframe_new(msg->msgData, strlen(msg->msgData));
	if (kt_ctx->config.network_config.application != ZEROMQ)
		zframe_send(&msg->_identity, sock,
		ZFRAME_MORE + ZFRAME_REUSE);
	zframe_send(&frame_reply, sock, ZFRAME_REUSE);

	zframe_destroy(&frame_reply);
	return 0;
}
