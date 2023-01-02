#include "eos.h"
#include "eosAssert.h"
#include "Services/Http/eosHttpServer.h"
#include "Services/Http/ethernetif.h"
#include "lwip/api.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
HttpServer::HttpServer(
	uint8_t port):

	_getCallback(*this, &HttpServer::getHandler),
	_headCallback(*this, &HttpServer::headHandler),
	_postCallback(*this, &HttpServer::postHandler),
	_port(port) {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un controlador.
/// \param    controller: El controlador.
///
void HttpServer::addController(
	HttpController *controller) {

	eosAssert(controller != nullptr);

	_controllers.pushBack(controller);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servidor.
///
void HttpServer::initialize() {

	static struct netif gnetif;
	ip_addr_t addr;
	ip_addr_t mask;
	ip_addr_t gw;

	tcpip_init(NULL, NULL);


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


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servidor.
///
void HttpServer::run() {

	addController(new HttpController("GET", &_getCallback));
	addController(new HttpController("HEAD", &_headCallback));
	addController(new HttpController("POST", &_postCallback));

	// Create a new TCP connection handle
	//
	HConnection hListenConnection = netconn_new(NETCONN_TCP);
	if (hListenConnection != NULL) {

		// Bind to port (HTTP) with default IP address
		//
		if (netconn_bind(hListenConnection, NULL, _port) == ERR_OK) {

			// Put the connection into LISTEN state
			//
			netconn_listen(hListenConnection);

			while (true) {

				// Accept any icoming connection
				//
				HConnection hConnection;
				if (netconn_accept(hListenConnection, &hConnection) == ERR_OK) {

					// Serve connection
					//
				    struct netbuf *inbuf;
				    if (netconn_recv(hConnection, &inbuf) == ERR_OK) {
				    	if (netconn_err(hConnection) == ERR_OK) {

				    	    char* data;
				    	    u16_t dataLength;
				    		netbuf_data(inbuf, (void**)&data, &dataLength);

				    		HttpRequest request(String(data, 0, dataLength));

				    		for (auto it = _controllers.begin(); it != _controllers.end(); it++) {
				    			HttpController* controller = *it;

				    			if (controller->canProcess(request)) {
				    				HttpResponse response = controller->process(request);
				    				String text = response.getText();
				    				netconn_write(hConnection, text, text.getLength(), NETCONN_NOCOPY);
				    			}
				    		}

				    	}
				    }

				    // Close the connection (server closes in HTTP)
				    //
				    netconn_close(hConnection);

				    // Delete the buffer (netconn_recv gives us ownership,
				    // so we have to make sure to deallocate the buffer)
				    //
				    netbuf_delete(inbuf);

					// Delete connection
					//
					netconn_delete(hConnection);
				}
			}
		}
	}
}


HttpResponse HttpServer::getHandler(
	const HttpRequest& request) {

	return HttpResponse(200, "OK", "Hola capullo");
}


HttpResponse HttpServer::headHandler(
	const HttpRequest& request) {

	return HttpResponse(400, String(""), String(""));
}


HttpResponse HttpServer::postHandler(
	const HttpRequest& request) {

	return HttpResponse(400, "", "");
}


void HttpServer::error(
	HConnection hConnection) {
}
