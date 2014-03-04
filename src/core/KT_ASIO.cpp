/*
 * KT_ASIO.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: habl
 */

#include "KT_ASIO.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace KIARA {
namespace Transport {

KT_ASIO::KT_ASIO()
{
}

KT_ASIO::~KT_ASIO()
{
}

KT_Session* KT_ASIO::connect(KT_Client& endpoint)
{
}

void KT_ASIO::send(KT_Msg& message,
		KT_Session& session, int linger)
{
}

KT_Msg KT_ASIO::recv(KT_Session& session, int linger)
{
}

void KT_ASIO::disconnect(KT_Session& session)
{
}

void KT_ASIO::register_callback(
		void (*callback)(KT_Msg& message, KT_Session& session))
{
}

void KT_ASIO::bind()
{
}

void KT_ASIO::unbind()
{
}


} /* end of Transport namespace */
} /* end of KIARA namespace */
