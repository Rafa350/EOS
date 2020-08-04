#include "eos.h"
#include "Services/eosHTTPService.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "Services/Http/httpserver.h"
#include "Services/Http/ethernetif.h"


using namespace eos;


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

	// Inicialitza el servidor
	//
	httpInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa la tasca del servei.
///
void HTTPService::onTask() {

	// Executa el servidor
	//
	httpThread();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servicoe web
///
void HTTPService::httpInitialize() {

	static struct netif gnetif;
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

	netif_set_default(&gnetif);
	if (netif_is_link_up(&gnetif))
		netif_set_up(&gnetif);
	else
		netif_set_down(&gnetif);

	http_server_init();
}


/// ----------------------------------------------------------------------
/// \brief    Executa el servidor
///
void HTTPService::httpThread() {

	http_server_thread(NULL);
}
