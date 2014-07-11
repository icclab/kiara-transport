/**
 * @file KT_HTTP_Parser.cpp
 * @author Mathias Hablützel <habl@zhaw.ch>
 * @version 1.0
 * @license TBD
 *
 * @brief Simple wrapper for http_parser.c with ostream support.
 */

#include "KT_HTTP_Parser.hpp"

namespace KIARA
{
namespace Transport
{

/**
 * @brief Instantiate the parser and configure it to extract the body.
 * @param msg The message to parse.
 */
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
    http_parser_init ( parser, HTTP_BOTH );

    // FIXME: Memory leak here
    parser->data = static_cast<void*>(new std::string);
    http_parser_execute ( parser, &settings, msg.get_payload().data(), \
        msg.get_payload().size() );
    payload = static_cast<std::string*> (parser->data);
}

/**
 * @destructor
 */
KT_HTTP_Parser::~KT_HTTP_Parser()
{
    delete (static_cast<std::string*>(parser->data));
    free (parser);
}

/**
 * @brief Internal method to get the payload.
 * @return String with the payload.
 */
std::string KT_HTTP_Parser::get_payload()
{
	return NULL != payload ? *payload : std::string("");
}

/**
 * @brief Overloaded << stream operator to return the actual HTTP Body
 * @param lhs Next ostream object, lhs.
 * @param rhs The parser reference
 * @return Ostream object.
 * @note Use it like that: std::cout << KIARA::Transport::KT_HTTP_Parser(msg) << std::endl;
 */
std::ostream& operator<< (std::ostream& lhs, KT_HTTP_Parser& rhs)
{
	lhs << rhs.get_payload();
	return lhs;
}

/**
 * @brief Callback called when the HTTP body is found.
 */
int body_cb (http_parser* p, char const* at, size_t len)
{
    std::string* s = static_cast<std::string*>(p->data);
    s->resize (len);
    s->insert (0, at, len);
    return 0;
}

} /* namespace Transport */
} /* namespace KIARA */
