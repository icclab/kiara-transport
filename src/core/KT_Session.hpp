/**
 * KIARA Transport Library Session
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */

#ifndef KT_SESSION_HPP
#define KT_SESSION_HPP

#include <string>
#include <vector>

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
  void* _k_user_data = nullptr;
  void* _socket = nullptr;
  std::string _endpoint;
  std::vector< char > _zeromq_identifier;
  
public:

    //
    // Constructors/Destructors
    //  

  KT_Session ( );
  virtual ~KT_Session ( );

	void set_socket ( void* socket )
	{
		_socket = socket;
	}

	void* get_socket ( )
	{
		return _socket;
	}

	void set_endpoint ( std::string endpoint) {
		_endpoint = endpoint;
	}

	std::string get_endpoint () {
		return _endpoint;
	}

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

	const std::vector< char >& get_zeromq_identifier() const
	{
		return _zeromq_identifier;
	}

	void set_zeromq_identifier(const std::vector< char >& zeromqIdentifier)
	{
		_zeromq_identifier = zeromqIdentifier;
	}
};
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_SESSION_HPP
