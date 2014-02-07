/*
 * KT_HTTP_Responder.hpp
 *
 *  Created on: Feb 6, 2014
 *      Author: habl
 */

#ifndef KT_HTTP_RESPONDER_HPP_
#define KT_HTTP_RESPONDER_HPP_

#include <vector>
#include <string>
#include <iostream>

namespace KIARA
{
namespace Transport
{

namespace KT_HTTP_Responder
{
	std::string generate_200_OK (std::vector<char> payload);
	std::string generate_400_BAD_REQUEST(std::vector<char> payload);
	std::string generate_401_UNAUTHORIZED(std::vector<char> payload);
	std::string generate_404_NOT_FOUND(std::vector<char> payload);
	std::string generate_500_INTERNAL_SERVER_ERROR(std::vector<char> payload);
	std::string generate_418_IM_A_TEAPOT();

	static std::string content_length(std::vector<char> payload);

	extern const char* header_delimiter;

	namespace HTTP_Code
	{
		extern const char* _200;
		extern const char* _400;
		extern const char* _401;
		extern const char* _404;
		extern const char* _500;
	}

	namespace Content_Type
	{
		extern const char* _text_plain;
	}
} /* namespace KT_HTTP_Responder */

} /* namespace Transport */
} /* namespace KIARA */

#endif /* KT_HTTP_RESPONDER_HPP_ */
