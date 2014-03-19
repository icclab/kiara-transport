/*
 * KT_HTTP_Requester.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: aepp
 */

#include "KT_HTTP_Requester.hpp"

namespace KIARA
{
namespace Transport
{
namespace KT_HTTP_Requester
{
std::string generate_request(std::string method, std::string host, std::string path, std::vector<char> payload)
{
	std::string request(make_header(method, path));
	request += "User-Agent: KIARA\r\n";
	request += "Host: ";
	request += host;
	request += "\r\n\r\n";
	return request;
}

std::string make_header(std::string method, std::string path)
{
	std::string header(method);
	header += " ";
	header += path;
	header += " HTTP/1.1\r\n";
	return header;
}

std::string content_length(std::vector<char> payload)
{
	return std::string ("Content-Length: " + std::to_string(payload.size()));
}

/*namespace Content_Type {
	const char* _text_plain  = "Content-Type: text/plain\r\n";
}*/

} /* namespace KT_HTTP_Requester */
} /* namespace Transport */
} /* namespace KIARA */
