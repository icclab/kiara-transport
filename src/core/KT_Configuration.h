/*
 * KT_Configuration.h
 *
 *  Created on: Mar 13, 2014
 *      Author: habl
 */

#ifndef KT_CONFIGURATION_H_
#define KT_CONFIGURATION_H_

#include "KT_Configuration_glob.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kt_configuration kt_configuration_t;

kt_network_layer kt_configuration_get_network_layer (kt_configuration_t* config);
void kt_configuration_set_network_layer (kt_configuration_t* config, kt_network_layer network_layer);

kt_transport_layer kt_configuration_get_transport_layer (kt_configuration_t* config);
void kt_configuration_set_transport_layer (kt_configuration_t* config, kt_transport_layer transport_layer);

kt_crypto_layer kt_configuration_get_crypto_layer (kt_configuration_t* config);
void kt_configuration_set_crypto_layer (kt_configuration_t* config, kt_crypto_layer crypto_layer);

kt_application_layer kt_configuration_get_application_layer (kt_configuration_t* config);
void kt_configuration_set_application_layer (kt_configuration_t* config, kt_application_layer application_layer);

kt_application_type kt_configuration_get_application_type (kt_configuration_t* config);
void kt_configuration_set_application_type (kt_configuration_t* config, kt_application_type application_type);

#ifdef __cplusplus
}
#endif

#endif /* KT_CONFIGURATION_H_ */
