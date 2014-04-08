/* 
 * File:   registry.c
 * Author: aepp
 *
 * Created on 25. November 2013, 16:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>
#include <assert.h>
#include <jansson.h>
#include "registry.h"
#include "negotiation.h"

neg_ctx_t *reg_create_context(void) {
	neg_ctx_t *neg_ctx;
	neg_ctx = (neg_ctx_t *) malloc(sizeof (struct neg_ctx_t));
	neg_ctx->hash = NULL;
	neg_ctx->dict_collection = NULL;
	neg_ctx->final_capabilities = NULL;
	neg_ctx->root = json_object();
	neg_ctx->root_response = json_object();
	return neg_ctx;
}

int reg_set_remote_capability(neg_ctx_t *neg_ctx, const char *endpoint, const char *remote_body) {
	neg_dict_remote_collection_t *remote_dict = reg_get_remote_dict(neg_ctx, endpoint);
	neg_dict_remote_collection_t *tmp, *current_dict, *out;
	neg_dict_remote_collection_t *s = malloc(sizeof (*s));
	json_t *root, *value;
	const char *key;
	char *nego_key;
	json_error_t error;

	root = json_loads(remote_body, 0, &error);

	json_object_foreach(root, key, value) {
		if (strcmp(key, "general") == 0) {
			//TODO: Parse the general section
		} else if (strcmp(key, "idl") == 0) {
			//TODO: Parse the IDL section
		} else if (json_is_object(value)) {
			asprintf(&nego_key, "%s.", key);
			_reg_parse_dict(value, remote_dict, nego_key);
		}
	}

	HASH_ITER(hh, neg_ctx->dict_collection, current_dict, tmp) {
		HASH_FIND_STR(current_dict->sub, "security.mechanism.ssl.prec", out);
	}
	return 0;
}

int reg_set_final_capabilities(neg_ctx_t* neg_ctx, char *response) {
	json_t *root, *value;
	json_error_t error;
	const char *key;

	root = json_loads(response, 0, &error);
	void *iter = json_object_iter(root);
	
	while (iter) {
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		/* use key and value ... */
		iter = json_object_iter_next(root, iter);
	}
}

neg_dict_remote_collection_t* reg_get_remote_dict(neg_ctx_t *neg_ctx, const char *endpoint) {
	neg_dict_remote_collection_t *s = malloc(sizeof (*s));
	HASH_FIND_STR(neg_ctx->dict_collection, endpoint, s);
	if (s == NULL) {
		s = malloc(sizeof (struct neg_dict_remote_collection_t));
		s->id = endpoint;
		s->sub = NULL;
		s->value = "";
		HASH_ADD_KEYPTR(hh, neg_ctx->dict_collection, s->id, strlen(s->id), s);
	}
	return s;
}

int reg_set_capability(neg_ctx_t *neg_ctx, char *key, char *value) {
	neg_dict_t *s = malloc(sizeof (struct neg_dict_t));
	memset(s, 0, sizeof (struct neg_dict_t));
	s->id = key;
	s->value = value;
	HASH_ADD_KEYPTR(hh, neg_ctx->hash, s->id, strlen(s->id), s);
	return 0;
}

neg_dict_t* reg_get_capability(neg_ctx_t* neg_ctx, char* key) {
	HASH_FIND_STR(neg_ctx->hash, key, neg_ctx->neg_dict);
	return neg_ctx->neg_dict;
}

char* reg_get_local_capability_json(neg_ctx_t* neg_ctx) {
	return _reg_get_local_capability_json(neg_ctx->hash, neg_ctx->root);
}

char* _reg_get_local_capability_json(neg_dict_t *hash, json_t *root) {
	struct neg_dict_t *tmp;
	json_t *category = NULL;
	json_t *group = NULL;
	json_t *type = NULL;
	json_t *value = NULL;

	for (tmp = hash; tmp != NULL; tmp = (struct neg_dict_t *) tmp->hh.next) {
		int i;
		char id[strlen(tmp->id) + 1];
		strncpy(id, tmp->id, sizeof (id));
		char delimiter[] = ".";
		char *key;

		// initialisieren und ersten Abschnitt erstellen
		key = strtok(id, delimiter);
		i = 0;
		while (key != NULL) {
			switch (i) {
				case CATEGORY:
					category = json_object_get(root, key);
					if (category == NULL) {
						category = json_object();
						json_object_set(root, key, category);
					}
					break;
				case GROUP:
					group = json_object_get(category, key);
					if (group == NULL) {
						group = json_object();
						json_object_set(category, key, group);
					}
					break;
				case TYPE:
					type = json_object_get(group, key);
					if (type == NULL) {
						type = json_object();
						json_object_set(group, key, type);
					}
					break;
				case VALUE:
					value = json_object_get(type, key);
					if (value == NULL) {
						value = json_object();
						json_object_set(type, key, json_string(tmp->value));
					} else {
						json_object_update(value, json_string(tmp->value));
					}
					break;
			}
			key = strtok(NULL, delimiter);
			i++;
		}
	}
	return json_dumps(root, JSON_ENCODE_ANY);
}

int _reg_parse_dict(json_t* value, neg_dict_remote_collection_t* remote_dict, const char* nego_key) {
	json_t *new_value;
	const char *new_key;

	json_object_foreach(value, new_key, new_value) {
		if (json_is_object(new_value)) {
			const char *tmp_key;
			asprintf(&tmp_key, "%s%s.", nego_key, new_key);
			_reg_parse_dict(new_value, remote_dict, tmp_key);
		}
		if (json_is_string(new_value)) {
			neg_dict_remote_collection_t *s = malloc(sizeof (*s));
			s->id = (const char *) malloc((strlen(nego_key) + strlen(new_key) + 1) * sizeof (char));
			s->value = (char *) malloc((strlen(json_string_value(new_value)) + 1) * sizeof (char));
			strcat((char*) s->id, (char*) nego_key);
			strcat((char*) s->id, (char*) new_key);
			strcat(s->value, json_string_value(new_value));
			s->sub = NULL;
			HASH_ADD_KEYPTR(hh, remote_dict->sub, s->id, strlen(s->id), s);
		}
	}
	return 0;
}
