/**
 * @file KT_HTTP_Parser.hpp
 * @author Mathias Hablützel <habl@zhaw.ch>
 * @version 1.0
 * @license TBD
 *
 * @brief Simple wrapper for http_parser.c with ostream support.
 */

#ifndef KT_HTTP_PARSER_HPP_
#define KT_HTTP_PARSER_HPP_

#include <iostream>
#include <string>
#include "KT_Msg.hpp"
#include "http_parser.h"

namespace KIARA
{
namespace Transport
{

int body_cb (http_parser* p, char const* at, size_t len);

class KT_HTTP_Parser
{
public:
	KT_HTTP_Parser (KT_Msg& msg);
	virtual ~KT_HTTP_Parser();
	std::string get_payload();
private:
	friend std::ostream& operator<< (std::ostream& lhs, KT_HTTP_Parser& rhs);
	http_parser* parser;
	std::string* payload;
};

} /* namespace Transport */
} /* namespace KIARA */

#endif /* KT_HTTP_PARSER_HPP_ */
