#include "eos.h"
#include "Services/Http/eosHttpServer.h"
#include "Services/Http/ethernetif.h"
#include "lwip/api.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "string.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
HttpServer::HttpServer() {

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

//extern "C" { void http_server_serve(struct netconn *conn); }


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servidor.
///
void HttpServer::run() {

	// Create a new TCP connection handle
	//
	HConnection hListenConnection = netconn_new(NETCONN_TCP);
	if (hListenConnection != NULL) {

		// Bind to port (HTTP) with default IP address
		//
		if (netconn_bind(hListenConnection, NULL, eosHTTPService_Port) == ERR_OK) {

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
#if 1
				    struct netbuf *inbuf;
				    if (netconn_recv(hConnection, &inbuf) == ERR_OK) {
				    	if (netconn_err(hConnection) == ERR_OK) {

				    	    char* data;
				    	    u16_t dataLength;
				    		netbuf_data(inbuf, (void**)&data, &dataLength);

				    		processData(hConnection, data, dataLength);
				    	}
				    }

				    // Close the connection (server closes in HTTP)
				    //
				    netconn_close(hConnection);

				    // Delete the buffer (netconn_recv gives us ownership,
				    // so we have to make sure to deallocate the buffer)
				    //
				    netbuf_delete(inbuf);
#else
					http_server_serve(hConnection);
#endif

					// Delete connection
					//
					netconn_delete(hConnection);
				}
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les dades del paquet.
/// \brief    hConnection: La conexio.
/// \param    data: Buffer de dades
/// \param    dataLength: Longitut del buffer de dades.
///
void HttpServer::processData(
	HConnection hConnection,
	const char* data,
	unsigned dataLength) {

	const char* header =
		"HTTP/1.1 200 OK\r\n"
	    "Content-Length: 12\r\n"
		"Content-Type: text/plain; charset=utf-8\r\n"
		"\r\n";

	netconn_write(hConnection, header, strlen(header), NETCONN_NOCOPY);
	netconn_write(hConnection, "Hola capullo", 12, NETCONN_NOCOPY);
}


void HttpServer::processGET(
	HConnection hConnection,
	const char* data,
	unsigned dataLength) {

}


void HttpServer::error(
	HConnection hConnection) {

}
