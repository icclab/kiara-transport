#include "KT_Configuration.hpp"

KIARA::Transport::KT_Configuration::KT_Configuration ( ) { }

KIARA::Transport::KT_Configuration::~KT_Configuration()
{
}

void KIARA::Transport::KT_Configuration::set_host(unsigned int transport_layer,
		std::string hostname, unsigned int port_number)
{

	this->set_transport_layer( transport_layer );
	this->set_hostname( hostname );
	this->set_port_number( port_number );
}
