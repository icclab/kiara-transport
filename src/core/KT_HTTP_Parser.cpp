/*
 * KT_HTTP_Parser.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: habl
 */

#include "KT_HTTP_Parser.hpp"

namespace KIARA
{
namespace Transport
{

KT_HTTP_Parser::KT_HTTP_Parser (KT_Msg& msg)
{
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

    parser = (http_parser*) malloc ( sizeof ( http_parser ) );
    http_parser_init ( parser, HTTP_REQUEST );

    parser->data = static_cast<void*>(new std::string);
    http_parser_execute ( parser, &settings, msg.get_payload().data(), \
        msg.get_payload().size() );
    payload = static_cast<std::string*> (parser->data);
}

KT_HTTP_Parser::~KT_HTTP_Parser()
{
	// TODO Auto-generated destructor stub
}

std::string KT_HTTP_Parser::get_payload()
{
	return NULL != payload ? *payload : std::string("");
}

std::ostream& operator<< (std::ostream& lhs, KT_HTTP_Parser& rhs)
{
	lhs << rhs.get_payload();
	return lhs;
}

int body_cb (http_parser* p, char const* at, size_t len)
{
	std::string* s = static_cast<std::string*>(p->data);
    s->resize (len);
    s->insert (0, at, len);
    return 0;
}

} /* namespace Transport */
} /* namespace KIARA */
