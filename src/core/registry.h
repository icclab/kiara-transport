/* 
 * File:   registry.h
 * Author: aepp
 *
 * Created on 25. November 2013, 16:45
 */

#include <uthash.h>
#include "negotiation.h"

#ifndef REGISTRY_H
#define	REGISTRY_H

#ifdef	__cplusplus
extern "C" {
#endif
	
enum dict_struct {
	CATEGORY,
	GROUP,
	TYPE,
    VALUE
};

neg_ctx_t *reg_create_context();
int reg_set_capability(neg_ctx_t *neg_ctx, char *key, char *value);
neg_dict_t *reg_get_capability(neg_ctx_t* neg_ctx, char* key);
char** _reg_str_split(char* a_str, const char a_delim);
char* reg_get_local_capability_json(neg_ctx_t* neg_ctx);

#ifdef	__cplusplus
}
#endif

#endif	/* REGISTRY_H */

