/* 
 * File:   negotiation.c
 * Author: aepp
 *
 * Created on 26. November 2013, 09:47
 */

#include <stdio.h>
#include <stdlib.h>
#include "reco_engine.h"
#include "registry.h"

/*
 * 
 */
neg_ctx_t *neg_init(){
	return reg_create_context();
}

int neg_set_local_capability(neg_ctx_t *neg_ctx, char *key, char *value){
	reg_set_capability(neg_ctx, key, value);
	return 1;
}

neg_dict_t *neg_get_capability(neg_ctx_t* neg_ctx, char* key){
	return reg_get_capability(neg_ctx, key);
}

int neg_send_offer(neg_ctx_t *neg_ctx){
	reco_send_offer(neg_ctx->host);
	return 1;
}

int neg_run_server(neg_ctx_t *neg_ctx) {
	void* server = init_reco_server(neg_ctx->host, neg_ctx);
	reco_run_server(server);
	return 1;
}

