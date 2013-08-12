/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API

#include "server.h"

//This is the performCall methode from kiara_impl.cpp, as example

void handleRequest(KIARA_MessageRaw* msgData) {
	//Do some work
	sleep(1);
}

int main() {
	//Define the Request handler
	void (*f)(KIARA_MessageRaw* msgData) = NULL;

	KIARA_ServerConfig config;
	KIARA_ServerContext *s_ctx;
	int res = 0;

	//set the config
	config.base_url = "tcp://*:5570";
	//config.base_url = "tcps://*:5570";
	//config.base_url = "dccp://*:5570";
	//config.base_url = "dccps://*:5570";

	//Asign it
	f = &handleRequest;
	//initialize the server (network nego phase)
	s_ctx = initServer(config);
	//The initialization of the Server sets the parameters out of the config
	//parameters that are not set will be negotiated with the network. s_ctx can
	//still be modified
	res = runServer(s_ctx, f);
	//TODO: Debugg/Err
	//TODO: We never get here, pass correct Err/Succ Message
	res = stopServer(s_ctx);
	return 0;
}
