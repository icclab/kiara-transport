#include "../../src/core/kt_server.h"

//This is the performCall methode from kiara_impl.cpp, as example

kt_srvctx_t *s_ctx;

void handleRequest()
{
	printf("Handling request\n");
	char *response = "Hello World";
	connect_to_backend(s_ctx);
	printf("Connected to backend\n");

	for (;;)
	{
		kt_messageraw_t *msg = recv_message(s_ctx);
		printf("Request: %s\n", msg->msgData);
		msg->msgData = response;
		send_message(s_ctx, msg);
	}
	disconnect_from_backend(s_ctx);
}

int main()
{
	//Define the Request handler
	void (*f)(kt_messageraw_t * msgData) = NULL;

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
