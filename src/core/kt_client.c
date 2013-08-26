#include <stdio.h>
#include <czmq.h>
#include <zmq.h>

#include "debug.h"

#include "kt_client.h"

kt_clientctx_t *kt_client_init(kt_connconf_t config)
{
	//TODO: Validate params and check if server can be started
	//TODO: Set parameters on context
	kt_clientctx_t *kt_ctx;
	kt_ctx = malloc(sizeof(kt_clientctx_t));
	kt_ctx->config = config;
	kt_ctx->ctx = zctx_new();

	kt_ctx->socket = zsocket_new(kt_ctx->ctx, ZMQ_REQ);

	return kt_ctx;
}

int kt_client_connect(kt_clientctx_t *kt_ctx)
{
	char *endpoint = compile_endpoint_string(kt_ctx->config);
	zsocket_connect(kt_ctx->socket, endpoint);
	debug ("connected to: %s\n", endpoint);
	free (endpoint);
	return 0;
}
int kt_client_disconnect(kt_clientctx_t *kt_ctx) {
	char *endpoint = compile_endpoint_string(kt_ctx->config);
	zsocket_disconnect(kt_ctx->socket, endpoint);
	debug ("disconnected from: %s\n", endpoint);
	free (endpoint);
	return 0;
}
kt_messageraw_t* recv_message(kt_clientctx_t *kt_ctx) {
	kt_messageraw_t *msg = malloc(sizeof(kt_messageraw_t));
	zmsg_t *m = zmsg_recv(kt_ctx->socket);
	msg->msgData = zframe_strdup(zmsg_pop(m));
	zmsg_destroy(&m);
	return msg;
}
int send_message(kt_clientctx_t *kt_ctx, kt_messageraw_t *msg) {
	zframe_t *sendframe = zframe_new(msg->msgData, strlen(msg->msgData));
	zframe_send(&sendframe, kt_ctx->socket, 0);

	zframe_destroy(&sendframe);
	return 0;
}
