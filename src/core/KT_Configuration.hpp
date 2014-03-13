
#ifndef KT_CONFIGURATION_HPP
#define KT_CONFIGURATION_HPP

#include <string>
#include "KT_Configuration_glob.h"

namespace KIARA {
namespace Transport {

/**
  * class KT_Configuration
  * 
  */

class KT_Configuration
{

private:

  // Layer 3 in the networking stack
  unsigned int _network_layer;
  // Layer 4 in the networking stack
  unsigned int _transport_layer;
  std::string _hostname;
  unsigned int _port_number;
  // Optional crypto layer, based on OpenSSL
  unsigned int _crypto_layer;
  unsigned int _application_layer;
  unsigned int _application_type;
  
public:

  KT_Configuration ( );
  virtual ~KT_Configuration ( );

  /**
   * Set the value of _network_layer
   * Layer 3 in the networking stack
   * @param network_layer the new value of _network_layer
   */
  void set_network_layer ( kt_network_layer network_layer );

  /**
   * Get the value of _network_layer
   * Layer 3 in the networking stack
   * @return the value of _network_layer
   */
  kt_network_layer get_network_layer ( );

  /**
   * Set the value of _transport_layer
   * Layer 4 in the networking stack
   * @param transport_layer the new value of _transport_layer
   */
  void set_transport_layer ( kt_transport_layer transport_layer );

  /**
   * Get the value of _transport_layer
   * Layer 4 in the networking stack
   * @return the value of _transport_layer
   */
  kt_transport_layer get_transport_layer ( );

  const std::string& get_hostname() const
  {
	  return _hostname;
  }

  void set_hostname(const std::string& hostname)
  {
	  _hostname = hostname;
  }

  unsigned int get_port_number() const
  {
	  return _port_number;
  }

  void set_port_number(unsigned int portNumber)
  {
	  _port_number = portNumber;
  }

  /**
   * Set the value of _crypto_layer
   * Optional crypto layer, based on OpenSSL
   * @param crypto_layer the new value of _crypto_layer
   */
  void set_crypto_layer ( kt_crypto_layer crypto_layer );

  /**
   * Get the value of _crypto_layer
   * Optional crypto layer, based on OpenSSL
   * @return the value of _crypto_layer
   */
  kt_crypto_layer get_crypto_layer ( );

  /**
   * Set the value of _application_layer
   * @param application_layer the new value of _application_layer
   */
  void set_application_layer ( kt_application_layer application_layer );

  /**
   * Get the value of _application_layer
   * @return the value of _application_layer
   */
  kt_application_layer get_application_layer ( );

  /**
   * Set the value of _application_type
   * @param application_type the new value of _application_type
   */
  void set_application_type ( kt_application_type application_type );
  /**
   * Get the value of _application_type
   * @return the value of _application_type
   */
  kt_application_type get_application_type ( );

  void set_host (kt_transport_layer transport_layer, std::string hostname, unsigned int port_number);

};
} // end of Transport namespace
} // end of KIARA namespace

#endif // KT_CONFIGURATION_HPP
