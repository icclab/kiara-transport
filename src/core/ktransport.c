#include "ktransport.h"

static const char* kt_transport_prefix[] = {
	"tcp://",
	"udp://",
	"dccp://",
	"sctp://"
};

char* compile_endpoint_string(kt_connconf_t config)
{
	//FIXME: Dynamic allocation of memory for endpoint
	char *endpoint = malloc(256);
	snprintf(endpoint, 255, "%s%s:%i",
		kt_transport_prefix[config.network_config.transport],
		config.base_url,
		config.network_config.port
		);
	return endpoint;
}
