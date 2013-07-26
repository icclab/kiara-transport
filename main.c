//Example of KIARAServer API
//At the moment, only native clients can connect like curl or any Browser that
//sends a valid HTTP Request. The response is just "Hello World"
#include <czmq.h>
#include <zmq.h>

#include "server.h"

//This is the performCall methode from kiara_impl.cpp, as example
void performCall(char *serviceUrl, char *requestData, char *responseData) {
	//Do some work
	sleep(1);
}

int main(int argc, char** argv) {
	//Define the function to be executed
	void (*f)(char*, char*, char*) = NULL;
	KIARAServerConfig config;
	KIARAServerContext *context;
	
	//set the config
	config.base_url = "tcp://*:5570";
	config.type = TCP_HTTP;
	//Asign it
	f = &performCall;
	//initialize the server
	context = initServer(config);
    //Pass it to the server
    runServer(context, f);
    //TODO: Debugg/Err
	//TODO: We never get here, pass correct Err/Succ Message
    return 0;
}