/* 
 * File:   main_nego.c
 * Author: aepp
 *
 * Created on 7. MÃ¤rz 2014, 14:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "../core/negotiation.h"
/*
 * 
 */
int main(void) {
	int f, status;
	
	neg_ctx_t *neg_ctx = neg_init();
	neg_set_local_profile(neg_ctx, KT_WEBSERVER);
	neg_ctx->host = "localhost";
	neg_ctx->port = 5556;
	neg_ctx->client_nego = 1;
	
	f = fork();
	if(f == 0) {
		//Start the negotiation Server
		int rc = neg_run_server(neg_ctx);
	}
	else {
		//Start the Server for the Service
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		strcat(cwd, "/server_0mq_http_pp");
		execl(cwd, "server_0mq_http_pp", 0, NULL);
		printf("Server did not start successful\n");
		wait(&status);
	}
	
	return 0;
}
