/*
 * main_client_0mq_req.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: habl
 */


#include "../../include/KT_Zeromq.hpp"
#include "http_parser.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace KIARA::Transport;

void callback_handler ( KT_Msg&, KT_Session*, KT_Connection* );
int body_cb ( http_parser*, char const*, size_t );
void Dump ( const void* mem, unsigned int n );

int main ()
{

	KT_Configuration config;
	config.set_application_type ( KT_STREAM );

	KT_Connection* connection = new KT_Zeromq ();
	connection->set_configuration (config);

	connection->register_callback( &callback_handler );
	connection->bind("tcp://*:5555");

	sleep (300);

	connection->unbind();

	exit ( 0 );
}

void callback_handler ( KT_Msg& msg, KT_Session* sess, KT_Connection* obj ) {
    http_parser_settings settings;

    // seems that we have to 0 all unused callback hooks
    // srsly ... save initializing? Anyone?
    settings.on_message_complete = 0;
    settings.on_status = 0;
    settings.on_message_begin = 0;
    settings.on_url = 0;
    settings.on_headers_complete = 0;
    settings.on_header_field = 0;
    settings.on_header_value = 0;
    
    settings.on_body = body_cb;

    http_parser* parser = (http_parser*) malloc ( sizeof ( http_parser ) );
    http_parser_init ( parser, HTTP_REQUEST );    

    http_parser_execute ( parser, &settings, msg.get_payload().data(), \
        512 );

	std::cout << msg.get_payload().data() << std::endl;
	std::string payload ( "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nHello World\r\n" );
	KT_Msg message;
	message.set_payload ( payload );

	obj->send ( message, (*sess), 0 );
}

int body_cb ( http_parser* p, char const* at, size_t len ) {
    std::cout << "HTTP Body CB hook" << std::endl << std::endl << std::endl;
    
    std::cout << "------ CONTENT ------" << std::endl;
    std::cout << at;
    std::cout << "------ END OF CONTENT ------" << std::endl;

    std::cout << std::endl << std::endl << std::endl;
    return 0;
}
