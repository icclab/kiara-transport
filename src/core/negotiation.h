/* 
 * File:   negotiation.h
 * Author: aepp
 *
 * Created on 25. November 2013, 16:46
 */
#include <uthash.h>
#include <jansson.h>

#ifndef NEGOTIATION_H
#define	NEGOTIATION_H

#ifdef	__cplusplus
extern "C" {
#endif
	
typedef struct neg_dict_t {
    const char *id;
    char *value;             
    UT_hash_handle hh;
} neg_dict_t;

typedef struct neg_dict_remote_collection_t {
    const char *id;
    struct neg_dict_remote_collection_t *sub;
	char *value;
    UT_hash_handle hh;
} neg_dict_remote_collection_t;
	
typedef struct neg_ctx_t {
    neg_dict_t *neg_dict;
	neg_dict_t *hash;
	neg_dict_remote_collection_t *dict_collection;
	char* host;
	char* server_repsonse;
	char* server_repsonse_body;
	json_t *root;
}neg_ctx_t;

enum precendence {
	MUST,
	MUST_NOT,
	SHOULD,
    SHOULD_NOT
};

int neg_send_offer(neg_ctx_t *neg_ctx);
int neg_set_local_capability(neg_ctx_t *neg_ctx, char *key, char *value);
neg_dict_t *neg_get_capability(neg_ctx_t *neg_ctx, char *key);
int neg_run_server(neg_ctx_t *neg_ctx);
neg_ctx_t *neg_init();

#ifdef	__cplusplus
}
#endif

#endif	/* NEGOTIATION_H */

