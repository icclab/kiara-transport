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
	neg_ctx->host = "tcp://localhost:81";
	int rc = neg_send_offer(neg_ctx);
	printf("### Full server response: \n%s\n\n", neg_ctx->server_repsonse);
	printf("### Content: \n%s\n", neg_ctx->server_repsonse_body);
	return 0;
}

