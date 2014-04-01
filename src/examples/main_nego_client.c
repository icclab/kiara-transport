/* 
 * File:   main_nego_client.c
 * Author: aepp
 *
 * Created on 19. März 2014, 10:42
 */

#include <stdio.h>
#include <stdlib.h>
#include "../core/negotiation.h"
/*
 * 
 */
int main(int argc, char** argv) {
	neg_ctx_t *neg_ctx = neg_init();
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.tcp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.udp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.user-protocols.suuuuu.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.user-protocols.notnull.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.communication-paradigm.req-rep.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.communication-paradigm.pub-su.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.tls.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.ssl.prec", "SHOULD");
	neg_ctx->host = "tcp://localhost:5555";
	int rc = neg_send_offer(neg_ctx);
	return 0;
}

