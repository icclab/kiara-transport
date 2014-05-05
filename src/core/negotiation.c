/* 
 * File:   negotiation.c
 * Author: aepp
 *
 * Created on 26. November 2013, 09:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>
#include "reco_engine.h"
#include "registry.h"

/*
 * 
 */
neg_ctx_t *neg_init() {
	return reg_create_context();
}

int neg_set_local_capability(neg_ctx_t *neg_ctx, char *key, char *value) {
	reg_set_capability(neg_ctx, key, value);
	return 1;
}

neg_dict_t *neg_get_capability(neg_ctx_t* neg_ctx, char* key) {
	return reg_get_capability(neg_ctx, key);
}

void neg_get_final_capability(neg_ctx_t* neg_ctx, char* key) {
	reg_get_final_capability(neg_ctx, key);
}

char *neg_send_offer(neg_ctx_t *neg_ctx) {
	return reco_send_offer(neg_ctx->host, neg_ctx);
}

int neg_run_server(neg_ctx_t *neg_ctx) {
	void* server = init_reco_server(neg_ctx->host, neg_ctx);
	reco_run_server(server);
	return 1;
}

int neg_set_final_capabilities(neg_ctx_t* neg_ctx, char *response) {
	reg_set_final_capabilities(neg_ctx, response);
	return 1;
}

char *neg_negotiate(neg_ctx_t *neg_ctx, const char *endpoint) {
	neg_dict_remote_collection_t *s = malloc(sizeof (*s));
	neg_dict_remote_collection_t* remote_dict = reg_get_remote_dict(neg_ctx, endpoint);
	neg_dict_t *current_dict, *tmp;
	dec_dict_t *dec_dict, *dec_tmp, *dec_it, *dec, *d_tmp;

	dec_dict = NULL;
	char delimiter[] = ".";
	char *key;

	HASH_ITER(hh, neg_ctx->hash, current_dict, tmp) {
		s = malloc(sizeof (struct neg_dict_remote_collection_t));
		HASH_FIND_STR(remote_dict->sub, current_dict->id, s);
		if (s == NULL) {
			printf("No coresponding value found in dict\n");
		} else {
			//Found value, negotiate
			int i;
			char *nego_key, *tmp_id;
			char id[strlen(current_dict->id) + 1];

			strncpy(id, current_dict->id, sizeof (id));
			key = strtok(id, delimiter);
			i = 1;
			while (key != NULL) {
				if (i <= 2) {
					if (i == 2) {
						asprintf(&nego_key, "%s.%s", nego_key, key);
					} else {
						asprintf(&nego_key, "%s", key);
					}
				} else if (i == 3) {
					HASH_FIND_STR(dec_dict, nego_key, dec_tmp);
					if (dec_tmp == NULL) {
						dec_tmp = malloc(sizeof (*dec_tmp));
						dec_tmp->id = nego_key;
						dec_tmp->sub = NULL;
						dec_tmp->value = 0;
						HASH_ADD_KEYPTR(hh, dec_dict, nego_key, strlen(nego_key), dec_tmp);
					}
					tmp_id = (char*) malloc(sizeof (char) * (strlen(key) + 1));
					strncpy(tmp_id, key, strlen(key));
					tmp_id[strlen(key)] = '\0';
				} else if (i == 4) {
					int l_prec = _prec_to_int(current_dict->value);
					int r_prec = _prec_to_int(s->value);
					int neg_value = (l_prec * r_prec) + (l_prec - r_prec);
					HASH_FIND_STR(dec_dict, nego_key, dec_it);

					HASH_ITER(hh, dec_it->sub, dec, d_tmp) {
						if (neg_value > dec->value) {
							HASH_DEL(dec_it->sub, dec);
						} else {
							neg_value = 0;
						}
					}
					if (neg_value > 0) {
						dec = malloc(sizeof (*dec));
						dec->id = tmp_id;
						dec->sub = NULL;
						dec->value = neg_value;
						HASH_ADD_KEYPTR(hh, dec_it->sub, dec->id, strlen(dec->id), dec);
					}
				}
				key = strtok(NULL, delimiter);
				i++;
			}
		}
	}
	neg_dict_t *neg_dict, *nego_tmp;
	neg_dict = NULL;

	HASH_ITER(hh, dec_dict, dec_it, dec_tmp) {

		HASH_ITER(hh, dec_it->sub, dec, d_tmp) {
			char *response_key;
			nego_tmp = malloc(sizeof (*nego_tmp));
			asprintf(&response_key, "%s.%s.prec", dec_it->id, dec->id);
			nego_tmp->id = response_key;
			nego_tmp->value = "1";
			HASH_ADD_KEYPTR(hh, neg_dict, response_key, strlen(response_key), nego_tmp);
		}
	}
	char *json = _reg_get_local_capability_json(neg_dict, neg_ctx->root_response);
	return json;
}

int _prec_to_int(char *prec) {
	int ret;

	if (strcmp(prec, "MUST") == 0) {
		ret = 4;
	} else if (strcmp(prec, "SHOULD") == 0) {
		ret = 3;
	} else if (strcmp(prec, "SHOULD NOT") == 0) {
		ret = 2;
	} else if (strcmp(prec, "MUST NOT") == 0) {
		ret = 1;
	} else {
		//Unknown stuff here
	}
	return ret;
}