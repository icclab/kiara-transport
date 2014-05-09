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

//Local negotiation dictionary
typedef struct neg_dict_t {
    const char *id;
    char *value;             
    UT_hash_handle hh;
} neg_dict_t;

//Decision dictionary
typedef struct dec_dict_t {
    const char *id;
	struct dec_dict_t *sub;
    int value;             
    UT_hash_handle hh;
} dec_dict_t;

//Store for multiple endpoints
typedef struct neg_dict_remote_collection_t {
    const char *id;
    struct neg_dict_remote_collection_t *sub;
	char *value;
    UT_hash_handle hh;
} neg_dict_remote_collection_t;

//negotiation context
typedef struct neg_ctx_t {
	//TODO: remove this neg_dict
    neg_dict_t *neg_dict;
	neg_dict_t *hash;
	neg_dict_t *final_capabilities; 
	neg_dict_remote_collection_t *dict_collection;
	char* host;
	int port;
	int kiara_endpoint;
	char* server_repsonse;
	char* server_repsonse_body;
	json_t *root;
	json_t *root_response;
} neg_ctx_t;

enum precendence {
	MUST,
	MUST_NOT,
	SHOULD,
    SHOULD_NOT
};

char *neg_send_offer(neg_ctx_t *neg_ctx);
int neg_set_local_capability(neg_ctx_t *neg_ctx, char *key, char *value);
neg_dict_t *neg_get_capability(neg_ctx_t *neg_ctx, char *key);
void neg_get_final_capability(neg_ctx_t* neg_ctx, char* key);
char *neg_get_best_local_capability(neg_ctx_t *neg_ctx, const char *capability);
int neg_run_server(neg_ctx_t *neg_ctx);
char *neg_negotiate(neg_ctx_t *neg_ctx, const char *endpoint);
int neg_set_final_capabilities(neg_ctx_t* neg_ctx, char *response);
int neg_set_profile(int profile);
int neg_capability_to_int(char *capability);
int _prec_to_int(char *prec);
neg_ctx_t *neg_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* NEGOTIATION_H */

