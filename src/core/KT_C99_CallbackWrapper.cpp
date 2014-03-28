/*
 * C99CallbackWrapper.cpp
 *
 *  Created on: Mar 20, 2014
 *      Author: habl
 */

#include "KT_C99_CallbackWrapper.hpp"

namespace KIARA
{
namespace Transport
{

KT_C99_CallbackWrapper::KT_C99_CallbackWrapper (kt_handle_t handle) :
        _c99_cb (handle)
{

}

KT_C99_CallbackWrapper::~KT_C99_CallbackWrapper ()
{
    // TODO Auto-generated destructor stub
}

std::function<void (KT_Msg&, KT_Session*, KT_Connection*)> KT_C99_CallbackWrapper::make_function ()
{
    using namespace std::placeholders;
    return std::bind(&KT_C99_CallbackWrapper::callback_wrapper, this, _1, _2, _3);
}

void KT_C99_CallbackWrapper::callback_wrapper (KT_Msg& msg, KT_Session* sess,
        KT_Connection* conn)
{
    if (nullptr == _c99_cb) return;

    kt_conn_session_t* conn_sess = new kt_conn_session {conn, sess};
    kt_msg_t* msg_t = reinterpret_cast<kt_msg_t*>(&msg);
    _c99_cb(conn_sess, msg_t);
}

} /* namespace Transport */
} /* namespace KIARA */
