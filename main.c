/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API

#include "kt_server.h"
#include "client.h"

//This is the performCall methode from kiara_impl.cpp, as example

void handleRequest(kt_messageraw_t* msgData) {
	//Do some work
	sleep(1);
}

int main_server() {
	//Define the Request handler
	void (*f)(kt_messageraw_t* msgData) = NULL;

	kt_srvconf config;
	kt_srvctx *s_ctx;
	int res = 0;

	//set the config
	config.base_url = "tcp://*:5570";
	//config.base_url = "tcps://*:5570";
	//config.base_url = "dccp://*:5570";
	//config.base_url = "dccps://*:5570";

	//Asign it
	f = &handleRequest;
	//initialize the server (network nego phase)
	s_ctx = kt_init_server(config);
	//The initialization of the Server sets the parameters out of the config
	//parameters that are not set will be negotiated with the network. s_ctx can
	//still be modified
	res = kt_run_server(s_ctx, f);
	//TODO: Debugg/Err
	//TODO: We never get here, pass correct Err/Succ Message
	res = kt_stop_server(s_ctx);
	return 0;
}

int main_client() {
	int buf_len, res = 0;
	char *msgData = "{\"J\":5,\"0\":\"N\"}";

	KIARA_ClientConfig config;
	KIARA_ClientContext *c_ctx;
	kt_messageraw_t inMsg;

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

int main(int argc, char** argv) {
	int res;

	res = main_server();
	res = main_client();
	return 0;
}