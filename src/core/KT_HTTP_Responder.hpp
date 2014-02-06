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

class KT_HTTP_Responder
{
public:
	KT_HTTP_Responder();
	virtual ~KT_HTTP_Responder();
	static std::string generate_200_OK(std::vector<char> payload);
	static std::string generate_418_IM_A_TEAPOT();
};

} /* namespace Transport */
} /* namespace KIARA */

#endif /* KT_HTTP_RESPONDER_HPP_ */
