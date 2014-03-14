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
	neg_ctx->root = json_object();
	return neg_ctx;
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
	json_t *category = json_object();
	json_t *group = json_object();
	json_t *type = json_object();
	json_t *value = json_object();
	
	for (tmp = neg_ctx->hash; tmp != NULL; tmp = (struct neg_dict_t *) tmp->hh.next) {
		char** tokens;
		int i;
		char id[strlen(tmp->id)];
		
		strncpy(id, tmp->id, sizeof(id));
		tokens = _reg_str_split(id, '.');
		for (i = 0; *(tokens + i); i++) {
			
			switch(i) {
				case CATEGORY:
					json_object_set(category, *(tokens + i), group);
					json_object_update(neg_ctx->root, category);
					break;
				case GROUP:
					json_object_set(group, *(tokens + i), type);
					break;
				case TYPE:
					json_object_set(type, *(tokens + i), value);
					break;
				case VALUE:
					json_object_set(value, *(tokens + i), json_string(tmp->value));
					break;
			}
			free(*(tokens + i));
		}
	}
	return json_dumps(neg_ctx->root, JSON_ENCODE_ANY);;
}

char** _reg_str_split(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;

	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	count += last_comma < (a_str + strlen(a_str) - 1);
	count++;
	result = (char **) malloc(sizeof (char*) * count);
	if (result) {
		size_t idx = 0;
		char* token = strtok((char *)a_str, ".");

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, ".");
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}
	return result;
}