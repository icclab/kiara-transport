/* 
 * File:   main_nego.c
 * Author: aepp
 *
 * Created on 7. März 2014, 14:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "../core/negotiation.h"
/*
 * 
 */
int main(int argc, char** argv) {
	neg_ctx_t *neg_ctx = neg_init();
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.tcp.prec", "MUST");
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.udp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "qos.user-protocols.http.prec", "MUST");
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.sctp.prec", "SHOULD");
	
	neg_set_local_capability(neg_ctx, "transport.user-protocols.none.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.communication-paradigm.req-rep.prec", "MUST");
	neg_ctx->host = "tcp://*:81";
	int rc = neg_run_server(neg_ctx);
	return 5;
}

