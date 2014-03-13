
/**
 * Lazy way to have C99 wrapper and C++ class implementation in one file
 */
#include "KT_Configuration.hpp"    // class declaration
#include "KT_Configuration.h"      // wrapper declaration

namespace KIARA {
namespace Transport {


KT_Configuration::KT_Configuration ( ) { }

KT_Configuration::~KT_Configuration ( ) { }

void KT_Configuration::set_network_layer ( unsigned int network_layer )   {
    _network_layer = network_layer;
}

unsigned int KT_Configuration::get_network_layer ( )   {
  return _network_layer;
}

void KT_Configuration::set_transport_layer ( unsigned int transport_layer )   {
    _transport_layer = transport_layer;
}

unsigned int KT_Configuration::get_transport_layer ( )   {
  return _transport_layer;
}

void KT_Configuration::set_crypto_layer ( unsigned int crypto_layer )   {
    _crypto_layer = crypto_layer;
}

unsigned int KT_Configuration::get_crypto_layer ( )   {
  return _crypto_layer;
}

void KT_Configuration::set_application_layer ( unsigned int application_layer )   {
    _application_layer = application_layer;
}

unsigned int KT_Configuration::get_application_layer ( )   {
  return _application_layer;
}

void KT_Configuration::set_application_type ( unsigned int application_type )   {
    _application_type = application_type;
}

unsigned int KT_Configuration::get_application_type ( )   {
  return _application_type;
}

} // end of namespace Transport
} // end of namespace KIARA


/*
 * Wrapper C99 function around KT_Configuration class
 */
extern "C" {
using namespace KIARA::Transport;
/*
 * A simple preprocessor trick to deduplicate the casting.
 *
 * Takes a parameter which pointer is to be casted to a KT_Configuration* named config_obj.
 * Since this is done by the preprocessor there is no runtime overhead by calling a function
 * that casts the pointer to said object. It may also be done by a inline function but both
 * cases however would not reduce the size of the binary.
 */
#define CASTER(obj) KT_Configuration* config_obj = reinterpret_cast<KT_Configuration*> (obj);

kt_network_layer kt_configuration_get_network_layer (kt_configuration_t* config) {
	CASTER(config)
	return config_obj->get_network_layer ();
}
void kt_configuration_set_network_layer (kt_configuration_t* config, kt_network_layer network_layer) {
	CASTER(config)
	config_obj->set_network_layer (network_layer);
}

kt_transport_layer kt_configuration_get_transport_layer (kt_configuration_t* config) {
	CASTER(config)
	return config_obj->get_transport_layer ();
}
void kt_configuration_set_transport_layer (kt_configuration_t* config, kt_transport_layer transport_layer) {
	CASTER(config)
	config_obj->set_transport_layer (transport_layer);
}

kt_crypto_layer kt_configuration_get_crypto_layer (kt_configuration_t* config) {
	CASTER(config)
	return config_obj->get_crypto_layer ();
}
void kt_configuration_set_crypto_layer (kt_configuration_t* config, kt_crypto_layer crypto_layer) {
	CASTER(config)
	config_obj->set_crypto_layer (crypto_layer);
}

kt_application_layer kt_configuration_get_application_layer (kt_configuration_t* config) {
	CASTER(config)
	return config_obj->get_application_layer ();
}
void kt_configuration_set_application_layer (kt_configuration_t* config, kt_application_layer application_layer) {
	CASTER(config)
	config_obj->set_application_layer (application_layer);
}

kt_application_type kt_configuration_get_application_type (kt_configuration_t* config) {
	CASTER(config)
	return config_obj->get_application_type ();
}
void kt_configuration_set_application_type (kt_configuration_t* config, kt_application_type application_type) {
	CASTER(config)
	config_obj->set_application_type (application_type);
}

/*
 * undef CASTER to prevent any accidents in further code
 */
#undef CASTER
}
