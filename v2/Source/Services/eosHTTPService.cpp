#include "eos.h"
#include "Services/eosHTTPService.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "Services/Http/httpserver.h"
#include "Services/Http/ethernetif.h"


using namespace eos;


struct netif gnetif;


/// ----------------------------------------------------------------------
/// \brief    Contructor del objecte.
/// \param    application: L'aplicacio.
///
HTTPService::HTTPService(
	Application* application):

	Service(application) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void HTTPService::onInitialize() {

	setPriority(Task::Priority::high);

	// Inicialitza la comunicacio TCPIP
	//
	tcpip_init(NULL, NULL);

	initInterface();
    http_server_init();
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa la tasca del servei.
///
void HTTPService::onTask() {

	http_server_thread(NULL);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la interficio TCPIP
//
void HTTPService::initInterface(){

	ip_addr_t addr;
	ip_addr_t mask;
	ip_addr_t gw;

#ifdef USE_DHCP
	ip_addr_set_zero_ip4(&addr);
	ip_addr_set_zero_ip4(&mask);
	ip_addr_set_zero_ip4(&gw);
#else
	IP_ADDR4(&addr, eosHTTPService_Addr0, eosHTTPService_Addr1, eosHTTPService_Addr2, eosHTTPService_Addr3);
	IP_ADDR4(&mask, eosHTTPService_Mask0, eosHTTPService_Mask1, eosHTTPService_Mask2, eosHTTPService_Mask3);
	IP_ADDR4(&gw, eosHTTPService_Gateway0, eosHTTPService_Gateway1, eosHTTPService_Gateway2, eosHTTPService_Gateway3);
#endif

	netif_add(&gnetif, &addr, &mask, &gw, NULL, &ethernetif_init, &tcpip_input);
	netif_set_default(&gnetif);
	if (netif_is_link_up(&gnetif))
		netif_set_up(&gnetif);
	else
		netif_set_down(&gnetif);
}
