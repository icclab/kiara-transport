/**
 * KIARA Transport Library Message
 * 
 * Author: Mathias Hablützel <habl@zhaw.ch>
 */

#ifndef KT_MSG_HPP
#define KT_MSG_HPP

#include <string>
#include <map>
#include <vector>

namespace KIARA {
namespace Transport {


/**
  * class KT_Msg
  * Since payload is handled as a pointer to a binary memory allocation
  * *free_payload() is responsible to destroy/deallocate the beforementioned
  * memory.
  * 
  * According to settings in kt_conn_session_t defined it will generate valid
  * header and body structures from the metadata and payload when sent. The
  * same applies the other way around when receiving messages.
  */

class KT_Msg
{
private:
  std::map< std::string, std::string > _metadata;
  std::vector< char > _payload;

public:
  KT_Msg ( );
  virtual ~KT_Msg ( );
  KT_Msg ( std::vector< char >& payload);

  void add_metadata ( std::string &key, std::string &value );
  std::string get_serialized_metadata ( const std::string delim = ":");
  
  //
  // Simple getter/setter methods
  //

  /**
   * Set the value of _metadata
   * @param metadata the new value of _metadata
   */
  void set_metadata ( std::map< std::string, std::string > &metadata ) {
      _metadata = metadata;
  }

  /**
   * Get the value of _metadata
   * @return the value of _metadata
   */
  std::map< std :: string, std :: string > get_metadata ( ) {
    return _metadata;
  }

  /**
   * Set the value of _payload
   * @param payload the new value of _payload
   */
  void set_payload ( std::vector< char > payload ) {
    _payload = payload;
  }

  void set_payload ( std::string &payload) {
	  _payload.resize (payload.size());
	  _payload.assign (payload.begin(), payload.end());
  }

  /**
   * Get the value of _payload
   * @return the value of _payload
   */
  std::vector< char > get_payload ( ) {
    return _payload;
  }


};
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_MSG_HPP
