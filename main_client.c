/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API

#include "client.h"

int main() {
	int buf_len, res = 0;
	char *msgData = "{\"J\":5,\"0\":\"N\"}";

	KIARA_ClientConfig config;
	KIARA_ClientContext *c_ctx;
	kt_messageraw inMsg;

	//set the config
	config.base_url = "tcp://localhost:5570";
	//initialize the client (network nego phase)
	c_ctx = initClient(config);
	//send some data. The Data to send must be serialized. As native http client
	//we still use curl. For KIARA to KIARA we use native TCP means, we have no
	//application protocol to parse.
	res = sendMessageSync(c_ctx, msgData, &inMsg);
	//Do something with the Result. inMsg->body contains the raw content of the
	//message wihtout any headers of the application protocol.
	buf_len = strlen(inMsg.body);
	//clean-up the client
	res = finalizeClient(c_ctx);
	return 0;
}
