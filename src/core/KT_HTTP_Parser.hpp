/*
 * KT_HTTP_Parser.hpp
 *
 *  Created on: Jan 29, 2014
 *      Author: habl
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
int url_cb (http_parser* p, char const* at, size_t len);

class KT_HTTP_Parser
{
public:
	KT_HTTP_Parser (KT_Msg& msg);
	virtual ~KT_HTTP_Parser();
	std::string get_payload();
	std::string get_url();
	int method;
private:
	friend std::ostream& operator<< (std::ostream& lhs, KT_HTTP_Parser& rhs);
	http_parser* parser;
	std::string* payload;
	std::string* query_string;
};

typedef struct {
	std::string* query_string;
	std::string* body;
} tmp_parser_fields;

} /* namespace Transport */
} /* namespace KIARA */

#endif /* KT_HTTP_PARSER_HPP_ */
