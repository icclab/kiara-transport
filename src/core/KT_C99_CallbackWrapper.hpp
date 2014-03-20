/*
 * C99CallbackWrapper.hpp
 *
 *  Created on: Mar 20, 2014
 *      Author: habl
 */

#ifndef C99CALLBACKWRAPPER_HPP_
#define C99CALLBACKWRAPPER_HPP_

#include "../../include/k_transport.h"
#include <functional>
#include <iostream>

#include "KT_Msg.hpp"
#include "KT_Connection.hpp"
#include "KT_Session.hpp"

namespace KIARA
{
namespace Transport
{

class KT_C99_CallbackWrapper
{
public:
    KT_C99_CallbackWrapper(kt_handle_t);
    std::function<void(KT_Msg&, KT_Session*, KT_Connection*)> make_function();
    virtual ~KT_C99_CallbackWrapper ();
    void set_callback (kt_handle_t);
    void callback_wrapper (KT_Msg&, KT_Session*, KT_Connection*);

private:
    kt_handle_t _c99_cb = nullptr;
};

} /* namespace Transport */
} /* namespace KIARA */

#endif /* C99CALLBACKWRAPPER_HPP_ */
