/**
 * KIARA Transport Library Session
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */

#ifndef KT_SESSION_HPP
#define KT_SESSION_HPP

#include <string>

#include "KT_Client.hpp"

namespace KIARA {
namespace Transport {

/**
  * class KT_Session
  * 
  */

class KT_Session
{
private:
  // k_user_data is a pointer to an opaque data structure which is needed by the
  // upper layers of KIARA and will not be modified by the transport library.
  void* _k_user_data;
  KIARA::Transport::KT_Client _endpoint;
  
public:

    //
    // Constructors/Destructors
    //  

  KT_Session ( );
  virtual ~KT_Session ( );

  /**
   * Set the value of _k_user_data
   * k_user_data is a pointer to an opaque data structure which is needed by the
   * upper layers of KIARA and will not be modified by the transport library.
   * @param k_user_data the new value of _k_user_data
   */
  void set_k_user_data ( void* k_user_data )   {
      _k_user_data = k_user_data;
  }

  /**
   * Get the value of _k_user_data
   * k_user_data is a pointer to an opaque data structure which is needed by the
   * upper layers of KIARA and will not be modified by the transport library.
   * @return the value of _k_user_data
   */
  void* get_k_user_data ( )   {
    return _k_user_data;
  }

  /**
   * Set the value of _endpoint
   * @param endpoint the new value of _endpoint
   */
  void set_endpoint ( KIARA::Transport::KT_Client endpoint )   {
      _endpoint = endpoint;
  }

  /**
   * Get the value of _endpoint
   * @return the value of _endpoint
   */
  KIARA::Transport::KT_Client get_endpoint ( ) const {
    return _endpoint;
  }

};
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_SESSION_HPP
