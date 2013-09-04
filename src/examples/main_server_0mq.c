#include "../../src/core/kt_server.h"

//This is the performCall methode from kiara_impl.cpp, as example

kt_srvctx_t *s_ctx;

kt_messageraw_t* handleRequest(kt_messageraw_t* msg)
{
	char *response = "Hello World";
	printf("Request: %s\n", msg->msgData);
	msg->msgData = response;
	return msg;
}

int main()
{
	//Define the Request handler
	kt_messageraw_t* (*f)(kt_messageraw_t * msg) = NULL;

	kt_connconf_t config;
	int res = 0;

	//set the config
	config.network_config.network = IPLEGACY;
	config.network_config.transport = TCP;
	config.network_config.crypto = NONE;
	config.network_config.application = ZEROMQ;
	config.network_config.port = 5670;
	config.base_url = "*";

	f = &handleRequest;
	s_ctx = kt_init_server(config);
	res = kt_run_server(s_ctx, f);
	res = kt_stop_server(s_ctx);
	return 0;
}
