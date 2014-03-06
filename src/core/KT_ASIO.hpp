/**
 * KIARA Transport Library Connection
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */
 
#ifndef KT_ASIO_HPP
#define KT_ASIO_HPP

#include <string>
#include <map>

#include "KT_Connection.hpp"
#include "KT_Configuration.hpp"
#include "KT_Msg.hpp"
#include "KT_Session.hpp"

namespace KIARA {
namespace Transport {

/**
  * class KT_Connection
  * 
  */

class KT_ASIO : public KT_Connection
{

public:

  KT_ASIO ( );
  virtual ~KT_ASIO ( );
  KT_ASIO ( std::string const& host);

  /**
   * @return int
   * @param endpoint Where to connect to
   */
  KT_Session*
  connect ( KT_Client& endpoint );

  /**
   * @param message Message for the receipient
   * @param linger Linger time before it aborts if sending synchronous,
   *    0 will block forever, -1 will make the call asynchronous
   */
  void
  send ( KT_Msg& message, KT_Session& session, int linger = 0 );

  /**
   * @return KIARA::Transport::KT_Msg
   * @param linger Linger time before it aborts if receiving synchronous,
   *    0 will block forever, -1 will make the call asynchronous and only
   *    return a message if there was one previously received
   */
  KT_Msg
  recv ( KT_Session& session, int linger = 0 );

  /**
   * @return void*
   */
  void
  disconnect ( KT_Session& session );

  /**
   * callback function must accept KT_Msg* and KT_Session* object
   * @param callback Function to be called when a message arrives
   */
  void register_callback ( void (*callback)(KT_Msg& message, KT_Session& session) );

  /**
   * bind requires a valid callback handler which is called when a message is
   * received, it binds according to the set configuration
   */
  void bind ( );
  
  /**
   * stops listening to incomming messages
   */
  void unbind ( );
  

}; // end of KT_ASIO class
} // end of Transport namespace
} // end of KIARA namespace


#endif // KT_ASIO_HPP
