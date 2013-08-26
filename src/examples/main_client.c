/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API

#include "../../src/core/kt_client.h"

int main()
{
	kt_connconf_t config;
	int buf_len, res = 0;
	char *msgData = "{\"J\":5,\"0\":\"N\"}";

	//set the config
	config.network_config.network = IPLEGACY;
	config.network_config.transport = TCP;
	config.network_config.crypto = NONE;
	config.network_config.application = HTTP;
	config.network_config.port = 8080;
	config.base_url = "localhost";
	//initialize the client (network nego phase)
	kt_clientctx_t *k_ctx = kt_client_init (config);
	//send some data. The Data to send must be serialized. As native http client
	//we still use curl. For KIARA to KIARA we use native TCP means, we have no
	//application protocol to parse.
	//res = sendMessageSync(c_ctx, msgData, &inMsg);
	//Do something with the Result. inMsg->body contains the raw content of the
	//message wihtout any headers of the application protocol.
	//buf_len = strlen(inMsg.body);
	//clean-up the client
	//res = finalizeClient(c_ctx);
	return 0;
}
