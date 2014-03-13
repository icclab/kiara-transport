/**
 * KIARA Transport Library Connection
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */
 
#ifndef KT_ZEROMQ_HPP
#define KT_ZEROMQ_HPP

#include <zmq.h>
#include <cstring>
#include <cassert>
#include <cerrno>
#include <string>
#include <thread>
#include <vector>

#include "../../include/k_transport.h"
#include "KT_Configuration.hpp"
#include "KT_Connection.hpp"
#include "KT_Msg.hpp"
#include "KT_Session.hpp"

namespace KIARA {
namespace Transport {

/**
  * class KT_Connection
  * 
  */

class KT_Zeromq : public KT_Connection
{
private:
	std::thread* poller_thread;
	bool interupted;
	void poller ( void* socket, std::string endpoint );

public:

  KT_Zeromq ( );
  virtual ~KT_Zeromq ( );
  KT_Zeromq ( std::string const& host);

  /**
   * @return int
   * @param ret Return a KT_Session pointer when successful
   */
  int
  connect ( KT_Session** ret);

  /**
   * @param message Message for the receipient
   * @param linger Linger time before it aborts if sending synchronous,
   *    0 will block forever, -1 will make the call asynchronous
   */
  int
  send ( KT_Msg& message, KT_Session& session, int linger = 0 );

  /**
   * @return KIARA::Transport::KT_Msg
   * @param linger Linger time before it aborts if receiving synchronous,
   *    0 will block forever, -1 will make the call asynchronous and only
   *    return a message if there was one previously received
   */
  int
  recv ( KT_Session& session, KT_Msg& ret, int linger = 0 );

  /**
   *
   */
  int
  disconnect ( KT_Session& session );

  /**
   * callback function must accept KT_Msg* and KT_Session* object
   * @param callback Function to be called when a message arrives
   */
  int register_callback ( void (*callback)(KT_Msg& message, KT_Session* session, KIARA::Transport::KT_Connection* obj) );

  /**
   * bind requires a valid callback handler which is called when a message is
   * received, it binds according to the set configuration
   */
  int bind ( );
  
  /**
   * stops listening to incomming messages
   */
  int unbind ( );

}; // end of KT_Connection class
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_CONNECTION_HPP
