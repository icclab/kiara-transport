/* 
 * File:   client.h
 * Author: aepp
 *
 * Created on 24. Juli 2013, 14:25
 */

#include "kiara.h"
#include "ktransport.h"

#ifndef CLIENT_H
#define	CLIENT_H

#ifdef	__cplusplus
extern "C" {
#endif
	
typedef struct KIARA_ClientConfig KIARA_ClientConfig;
typedef struct KIARA_ClientContext KIARA_ClientContext;
	
//public
struct KIARA_ClientConfig {
	int type;
	char *base_url;
};

//private
struct KIARA_ClientContext {
	struct KIARA_ClientConfig config;
	zctx_t *ctx;
};

//public
KIARA_ClientContext *initClient(KIARA_ClientConfig config);
KIARA_Result finalizeClient(KIARA_ClientContext *context);

KIARA_Result sendMessageSync(KIARA_ClientContext *context, char *msgData, KIARA_MessageRaw *inMsg);
KIARA_Result sendMessageSyncMore(KIARA_ClientContext *context, char *msgData, KIARA_MessageRaw *inMsg);
KIARA_Result sendMessageAsync(KIARA_ClientContext *context, char *msgData, KIARA_MessageRaw *inMsg);
KIARA_Result sendMessageAsyncMore(KIARA_ClientContext *context, char *msgData, KIARA_MessageRaw *inMsg);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */

