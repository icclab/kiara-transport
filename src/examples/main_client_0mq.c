/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API
#include "../../src/core/kt_client.h"
#include <stdlib.h>

int main()
{
	kt_connconf_t config;
	int buf_len, res = 0;
	char *msgData = "Hello server? You there?\0";

	//set the config
	config.network_config.network = IPLEGACY;
	config.network_config.transport = TCP;
	config.network_config.crypto = NONE;
	config.network_config.application = ZEROMQ;
	config.network_config.port = 5670;
	config.type = REQUESTREPLY;
	config.base_url = "localhost";

	//initialize the client (network nego phase)
	kt_clientctx_t *k_ctx = kt_client_init(config);
	//connect to the endpoint
	kt_client_connect(k_ctx);

	//simulate request
	kt_messageraw_t *msg = malloc(sizeof(kt_messageraw_t));
	msg->msgData = msgData;
	send_message(k_ctx, msg);

	//receive reply, dump it
	msg = recv_message(k_ctx);
	printf("%s\n", msg->msgData);

	kt_client_disconnect(k_ctx);

	return 0;
}
