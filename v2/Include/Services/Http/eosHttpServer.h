#ifndef __eosHttpServer__
#define __eosHttpServer__


#include "eos.h"
#include "System/eosString.h"
#include "System/Collections/eosDynamicArray.h"

#include "lwip/api.h"
#define CONNECTION_HANDLER struct netconn*


namespace eos {

    // \brief Solicitut HTTP
    //
	class HttpRequest {
		private:
			const char* pVerb;
			const char* pUri;
			unsigned verbLength;
			unsigned uriLength;

		private:
			void parseData(const String& data);

		public:
			HttpRequest(const String& data);

			inline String getVerb() const { return String(pVerb, 0, verbLength); }
			inline String getUri() const { return String(pUri, 0, uriLength); }
	};

	/// \brief Resposta HTTP
	///
	class HttpResponse {
		public:
			HttpResponse();

	};

	/// \brief Controlador de verbs del servidor HTTP
	///
	class HttpController {
		public:
			HttpController(const String& verb);
	};


	/// \brief Servidor HTTP
	///
    class HttpServer {
    	private:
		    typedef DynamicArray<HttpController*> ControllerList;
    		typedef CONNECTION_HANDLER HConnection;

    	private:
    		ControllerList controllers;
    		uint8_t port;

    	private:
    		void error(HConnection hConnection);
    		void processGET(HConnection hConnection, const char* data, unsigned dateLength);
    		void processData(HConnection hConnection, const char* data, unsigned dataLength);

        public:
            HttpServer(uint8_t port);
            
            void addController(HttpController* controller);

            void initialize();
            void run();
    };
}


#endif // __httpServer__
