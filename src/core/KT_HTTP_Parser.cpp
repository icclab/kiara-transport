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
	
	tmp_parser_fields *parser_fields;
	parser_fields = new tmp_parser_fields;
	parser_fields->host = new std::string("0");
	parser_fields->body = new std::string;
	parser_fields->query_string = new std::string;

    // seems that we have to 0 all unused callback hooks
    // srsly ... save initializing? Anyone?
    settings.on_message_complete = 0;
    settings.on_status = 0;
    settings.on_message_begin = 0;
    settings.on_headers_complete = 0;
    settings.on_header_field = 0;
    settings.on_header_value = 0;

    settings.on_body = body_cb;
	settings.on_url = url_cb;
	settings.on_header_field = header_field_cb;
	settings.on_header_value = header_value_cb;

    parser = (http_parser*) malloc ( sizeof ( http_parser ) );
    http_parser_init ( parser, HTTP_BOTH );

    parser->data = parser_fields;
    http_parser_execute ( parser, &settings, msg.get_payload().data(), \
        msg.get_payload().size() );
	
    payload = ((tmp_parser_fields*)parser->data)->body;
	query_string = ((tmp_parser_fields*)parser->data)->query_string;
	method = parser->method;
	host = ((tmp_parser_fields*)parser->data)->host;
	identifier = ((tmp_parser_fields*)parser->data)->host;
	*identifier += *((tmp_parser_fields*)parser->data)->query_string;
}

KT_HTTP_Parser::~KT_HTTP_Parser()
{
    delete (static_cast<std::string*>(parser->data));
    free (parser);
}

std::string KT_HTTP_Parser::get_payload()
{
	return NULL != payload ? *payload : std::string("");
}

std::string KT_HTTP_Parser::get_url()
{
	return NULL != query_string ? *query_string : std::string("");
}

std::string KT_HTTP_Parser::get_host()
{
	return NULL != host ? *host : std::string("");
}

std::string KT_HTTP_Parser::get_identifier()
{
	return NULL != identifier ? *identifier : std::string("");
}

std::ostream& operator<< (std::ostream& lhs, KT_HTTP_Parser& rhs)
{
	lhs << rhs.get_payload();
	return lhs;
}

int body_cb (http_parser* p, char const* at, size_t len)
{
	tmp_parser_fields *parser_fields;
	parser_fields = (tmp_parser_fields*) p->data;
	parser_fields->body->resize(len);
    parser_fields->body->insert (0, at, len);
    return 0;
}

int url_cb (http_parser* p, char const* at, size_t len)
{
	tmp_parser_fields *parser_fields;
	parser_fields = (tmp_parser_fields*) p->data;
    parser_fields->query_string->resize (len);
    parser_fields->query_string->insert (0, at, len);
    return 0;
}

int header_field_cb (http_parser* p, char const* at, size_t len)
{
	std::string field;
	field.resize (len);
    field.insert (0, at, len);
	if(field.compare(0, 4, "Host") == 0) {
		tmp_parser_fields *parser_fields;
		parser_fields = (tmp_parser_fields*) p->data;
		parser_fields->host = new std::string("1");;
	}
    return 0;
}

int header_value_cb (http_parser* p, char const* at, size_t len)
{
	tmp_parser_fields *parser_fields;
	parser_fields = (tmp_parser_fields*) p->data;
	if(parser_fields->host->compare(0, 4, "1") == 0) {
		parser_fields->host->clear();
		parser_fields->host->resize (len);
		parser_fields->host->insert (0, at, len);
	}
    return 0;
}

} /* namespace Transport */
} /* namespace KIARA */
