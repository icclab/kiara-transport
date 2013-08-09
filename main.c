//Example of KIARAClient/Server API
//the following two includes are soon replaced by ktransport.h and kmessage.h
#include <czmq.h>
#include <zmq.h>

#include "server.h"
#include "client.h"

//This is the performCall methode from kiara_impl.cpp, as example
void performCall(char *serviceUrl, char *requestData, char *responseData) {
	//Do some work
	sleep(1);
}

int main_server(){
	//Define the function to be executed
	void (*f)(char*, char*, char*) = NULL;
	
	KIARA_ServerConfig config;
	KIARA_ServerContext *s_ctx;
	int res = 0;
	
	//set the config
	config.base_url = "tcp://*:5570";
	//config.base_url = "tcps://*:5570";
	//config.base_url = "dccp://*:5570";
	//config.base_url = "dccps://*:5570";
	
	//If the type of the application-protocoll is not defined, we use native tcp
	//with own message-types
	config.type = HTTP;
	//Asign it
	f = &performCall;
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

int main_client(){
	int buf_len, res = 0;
	char *msgData = "{\"J\":5,\"0\":\"N\"}";
	
	KIARA_ClientConfig config;
	KIARA_ClientContext *c_ctx;
	KIARA_MessageRaw inMsg;
	
	//set the config
	config.base_url = "tcp://*:5570";
	config.type = HTTP;
	//initialize the client (network nego phase)
	c_ctx = initClient(config);
	//send some data. The Data to send must be serialized. As native http client
	//we still use curl. For KIARA to KIARA we use native TCP means, we have no
	//application protocol to parse.
	res = sendMessageSync(c_ctx, msgData, inMsg);
	//Do something with the Result. inMsg->body contains the raw content of the
	//message wihtout any headers of the application protocol.
	buf_len = strlen(inMsg->body);
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