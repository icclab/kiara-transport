
#ifndef KT_CLIENT_HPP
#define KT_CLIENT_HPP

#include <string>


namespace KIARA {
namespace Transport {

/**
  * class KT_Client
  * 
  */

class KT_Client
{
private:
  std::string _endpoint_identifier;

public:

    //
    // Constructors/Destructors
    //  

  KT_Client ( );
  virtual ~KT_Client ( );

  /**
   * @param endpoint to be set
   */
  void set_endpoint ( std::string endpoint )
  {
    _endpoint_identifier = endpoint;
  }

  /**
   * @return string
   */
  std::string get_endpoint ( )
  {
    return _endpoint_identifier;
  }

  /**
   * Set the value of _endpoint_identifier
   * @param identifier the new value of _endpoint_identifier
   */
  void set_endpoint_identifier ( std::string identifier ) {
      _endpoint_identifier = identifier;
  }

  /**
   * Get the value of _endpoint_identifier
   * @return the value of _endpoint_identifier
   */
  std::string get_endpoint_identifier ( ) {
    return _endpoint_identifier;
  }
  
};
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_CLIENT_HPP
