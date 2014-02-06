/*
 * KT_HTTP_Responder.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: habl
 */

#include "KT_HTTP_Responder.hpp"

namespace KIARA
{
namespace Transport
{

KT_HTTP_Responder::KT_HTTP_Responder()
{
	// TODO Auto-generated constructor stub

}

KT_HTTP_Responder::~KT_HTTP_Responder()
{
	// TODO Auto-generated destructor stub
}

std::string KT_HTTP_Responder::generate_200_OK(std::vector<char> payload)
{
	std::string response("HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\n");
	response.append(payload.data(), payload.size());
	return response;
}

std::string KT_HTTP_Responder::generate_418_IM_A_TEAPOT()
{
	// https://tools.ietf.org/html/rfc2324
	// Simple response method for testing
	std::string response ("            _\n"
			"         _,(_)._\n"
			"    ___,(_______).      ____\n"
			"  ,'__.           \\    /\\___\\-.\n"
			" /,' /             \\  /  /     \\\n"
			"| | |              |,'  /       \\\n"
			" \\`.|                  /       _|_\n"
			"  `. :           :    /        MMM\n"
			"    `.            :.,'        ZHAW\n"
			"      `-.________,-'          KIARA\n");
	return std::string("HTTP/1.0 418 IM A TEAPOT\r\nContent-Type: text/plain\r\nContent-Length: 301\r\n\r\n" + response);
}

} /* namespace Transport */
} /* namespace KIARA */
