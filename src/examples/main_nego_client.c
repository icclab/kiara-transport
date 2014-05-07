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
int main(void) {
	char *response, *foo;
	int ret = 0;
	
	neg_ctx_t *neg_ctx = neg_init();
	
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.tcp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.transport-port.*.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.transport-port.80.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.transport-protocols.udp.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.user-protocols.suuuuu.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.user-protocols.notnull.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.communication-paradigm.req-rep.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "transport.communication-paradigm.pub-su.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.tls.prec", "SHOULD");
	neg_set_local_capability(neg_ctx, "security.mechanism.ssl.prec", "SHOULD");
	neg_ctx->host = "localhost";
	neg_ctx->port = 5556;
	response = neg_send_offer(neg_ctx);
	
	if(neg_ctx->kiara_endpoint == 0){
		printf("Not a KIARA endpoint");
	}
	else {
		int ret = neg_set_final_capabilities(neg_ctx, response);
		neg_get_final_capability(neg_ctx, "transport.transport-protocols");
		printf("Transport protocl is: %s\n", neg_ctx->neg_dict->value);
		neg_get_final_capability(neg_ctx, "transport.communication-paradigm");
		printf("Communication paradigm is: %s\n", neg_ctx->neg_dict->value);
		neg_get_final_capability(neg_ctx, "security.mechanism");
		printf("Security mechanism is: %s\n", neg_ctx->neg_dict->value);
		neg_get_final_capability(neg_ctx, "transport.transport-port");
		printf("Transport Port is: %s\n", neg_ctx->neg_dict->value);
		foo = neg_get_best_local_capability(neg_ctx, "transport.transport-port");
		printf("Best own decission for port is: %s\n", foo);
		free(foo);
	}
	return ret;
}

