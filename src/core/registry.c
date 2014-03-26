/* 
 * File:   registry.c
 * Author: aepp
 *
 * Created on 25. November 2013, 16:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>
#include <assert.h>
#include <jansson.h>
#include "registry.h"
#include "negotiation.h"

/*
 * 
 */

neg_ctx_t *reg_create_context() {
	neg_ctx_t *neg_ctx;
	neg_ctx = (neg_ctx_t *) malloc(sizeof (struct neg_ctx_t));
	neg_ctx->hash = NULL;
	neg_ctx->dict_collection = NULL;
	neg_ctx->root = json_object();
	return neg_ctx;
}

int reg_set_remote_capability(neg_ctx_t *neg_ctx, const char *endpoint, const char *remote_body){
	neg_dict_remote_collection_t *remote_dict = reg_get_remote_dict(neg_ctx, endpoint);
	neg_dict_remote_collection_t *tmp, *current_dict, *out;
	neg_dict_remote_collection_t *s = malloc(sizeof(*s));
	s->id = "some.negotiation.id";
	s->sub = NULL;
	s->value = "MUST";
	HASH_ADD_KEYPTR(hh, remote_dict->sub, s->id, strlen(s->id), s);
	HASH_ITER(hh, neg_ctx->dict_collection, current_dict, tmp) {
		HASH_FIND_STR(current_dict->sub, "some.negotiation.id", out);
		printf("%s\n", out->value);
	}
	return 0;
}

neg_dict_remote_collection_t* reg_get_remote_dict(neg_ctx_t *neg_ctx, const char *endpoint){
	neg_dict_remote_collection_t *s = malloc(sizeof(*s));
	HASH_FIND_STR(neg_ctx->dict_collection, endpoint, s);
	if(s == NULL) {
		s = malloc(sizeof (struct neg_dict_remote_collection_t));
		s->id = endpoint;
		s->sub = NULL;
		s->value = "";
		HASH_ADD_KEYPTR(hh, neg_ctx->dict_collection, s->id, strlen(s->id), s);
	}
	return s;
}

int reg_set_capability(neg_ctx_t *neg_ctx, char *key, char *value) {
	neg_ctx->neg_dict = (neg_dict_t *) malloc(sizeof (struct neg_dict_t));
	neg_ctx->neg_dict->id = key;
	neg_ctx->neg_dict->value = value;
	HASH_ADD_KEYPTR(hh, neg_ctx->hash, neg_ctx->neg_dict->id,
			strlen(neg_ctx->neg_dict->id), neg_ctx->neg_dict);
}

neg_dict_t* reg_get_capability(neg_ctx_t* neg_ctx, char* key) {
	HASH_FIND_STR(neg_ctx->hash, key, neg_ctx->neg_dict);
	return neg_ctx->neg_dict;
}

char* reg_get_local_capability_json(neg_ctx_t* neg_ctx) {
	struct neg_dict_t *tmp;
	json_t *category;
	json_t *group;
	json_t *type;
	json_t *value;
	
	for (tmp = neg_ctx->hash; tmp != NULL; tmp = (struct neg_dict_t *) tmp->hh.next) {
		int i;
		char id[strlen(tmp->id)];
		strncpy(id, tmp->id, sizeof(id));
		char delimiter[] = ".";
		char *key;

		// initialisieren und ersten Abschnitt erstellen
		key = strtok(id, delimiter);
		i = 0;
		while(key != NULL) {
			switch(i) {
				case CATEGORY:
					category = json_object_get(neg_ctx->root, key);
					if(category == NULL) {
						category = json_object();
						json_object_set(neg_ctx->root, key, category);	
					}
					break;
				case GROUP:
					group = json_object_get(category, key);
					if(group == NULL) {
						group = json_object();
						json_object_set(category, key, group);	
					}
					break;
				case TYPE:
					type = json_object_get(group, key);
					if(type == NULL) {
						type = json_object();
						json_object_set(group, key, type);	
					}
					break;
				case VALUE:
					value = json_object_get(type, key);
					if(value == NULL) {
						value = json_object();
						json_object_set(type, key, json_string(tmp->value));
					}
					else {
						json_object_update(value, json_string(tmp->value));
					}
					break;
			}
			key = strtok(NULL, delimiter);
			i++;
		}
	}
	return json_dumps(neg_ctx->root, JSON_ENCODE_ANY);
}