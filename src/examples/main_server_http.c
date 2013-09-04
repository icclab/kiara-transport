/* 
 * File:   ktransport.h
 * Author: aepp
 *
 * Created on 26. Juli 2013, 13:58
 */
//Example of KIARAClient/Server API

#include "../../src/core/kt_server.h"

//This is the performCall methode from kiara_impl.cpp, as example

kt_srvctx_t *s_ctx;

kt_messageraw_t* handleRequest(kt_messageraw_t* msg)
{
	char *http_ok = "HTTP/1.0 200 OK\r\nVary: Accept-Encoding, Accept-Language\r\nConnection: Close\r\nContent-Type: text/plain\r\nContent-Length:12\r\n\r\nHello, World";
	printf("Handling request\n");
	//printf("Request: %s\n", msg->msgData);
	msg->msgData = http_ok;
	return msg;
}

int main() {
    //Define the Request handler
	kt_messageraw_t* (*f)(kt_messageraw_t * msg) = NULL;

    kt_connconf_t config;
    int res = 0;

    //set the config
    config.network_config.network = IPLEGACY;
    config.network_config.transport = TCP;
    config.network_config.crypto = NONE;
    config.network_config.application = HTTP;
    config.network_config.port = 8080;
    config.base_url = "*";

    f = &handleRequest;
    //initialize the server (network nego phase)
    s_ctx = kt_init_server(config);
    //The initialization of the Server sets the parameters out of the config
    //parameters that are not set will be negotiated with the network. s_ctx can
    //still be modified
    res = kt_run_server(s_ctx, f);
    res = kt_stop_server(s_ctx);
    return 0;
}
