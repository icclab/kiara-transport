/**
 * KIARA Transport Library Connection
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */
 
#ifndef KT_CONNECTION_HPP
#define KT_CONNECTION_HPP

#include <string>
#include <map>

#include "KT_Configuration.hpp"
#include "KT_Msg.hpp"
#include "KT_Session.hpp"

namespace KIARA {
namespace Transport {

/**
  * class KT_Connection
  * 
  */

class KT_Connection
{
protected:

  void* _context;
  std::map< std::string*, KIARA::Transport::KT_Session* > _sessions;
  KIARA::Transport::KT_Configuration* _configuration;
  
public:

  KT_Connection ( );
  virtual ~KT_Connection ( );
  KT_Connection (const std::string &host);

  /**
   * @return int
   * @param endpoint Where to connect to
   */
  virtual KIARA::Transport::KT_Session*
  connect ( KIARA::Transport::KT_Client &endpoint ) = 0;

  /**
   * @param message Message for the receipient
   * @param linger Linger time before it aborts if sending synchronous,
   *    0 will block forever, -1 will make the call asynchronous
   */
  virtual void
  send ( KIARA::Transport::KT_Msg &message, KIARA::Transport::KT_Session &session, int linger = 0 ) = 0;

  /**
   * @return KIARA::Transport::KT_Msg
   * @param linger Linger time before it aborts if receiving synchronous,
   *    0 will block forever, -1 will make the call asynchronous and only
   *    return a message if there was one previously received
   */
  virtual KIARA::Transport::KT_Msg *
  recv ( KIARA::Transport::KT_Session& session, int linger = 0 ) = 0;

  /**
   * @return void*
   */
  virtual void
  disconnect ( KIARA::Transport::KT_Session& session ) = 0;

  /**
   * callback function must accept KT_Msg* and KT_Session* object
   * @param callback Function to be called when a message arrives
   */
  virtual void register_callback ( void (*callback)(KIARA::Transport::KT_Msg&, KIARA::Transport::KT_Session&) ) = 0;

  /**
   * bind requires a valid callback handler which is called when a message is
   * received, it binds according to the set configuration
   */
  virtual void bind ( ) = 0;
  
  /**
   * stops listening to incomming messages
   */
  virtual void unbind ( ) = 0;
  
  /**
   * Set the value of _context
   * @param context the new value of _context
   */
  virtual void set_context ( void* context ) {
      _context = context;
  }

  /**
   * Get the value of _context
   * @return the value of _context
   */
  virtual void* get_context ( ) {
    return _context;
  }

  /**
   * Set the value of _session
   * @param session the new value of _session
   */
  virtual void set_session ( std::map< std::string*, KIARA::Transport::KT_Session* > &session ) {
      _sessions = session;
  }

  /**
   * Get the value of _session
   * @return the value of _session
   */
  virtual std::map< std::string*, KIARA::Transport::KT_Session* > &get_session ( ) {
    return _sessions;
  }

  /**
   * Set the value of _configuration
   * @param configuration the new value of _configuration
   */
  virtual void set_configuration ( KIARA::Transport::KT_Configuration* configuration ) {
      _configuration = configuration;
  }

  /**
   * Get the value of _configuration
   * @return the value of _configuration
   */
  virtual KIARA::Transport::KT_Configuration* get_configuration ( )   {
    return _configuration;
  }
  
  
}; // end of KT_Connection class
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_CONNECTION_HPP
