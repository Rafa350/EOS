#pragma once
#ifndef __eosHttpServer__
#define __eosHttpServer__


#include "eos.h"
#include "System/eosString.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosVector.h"

#include "lwip/api.h"
#define CONNECTION_HANDLER struct netconn*


namespace eos {

    // \brief Solicitut HTTP
    //
	class HttpRequest {
		private:
			String _method;
			String _uri;
			const char *_pHeaders;
			unsigned _headersLength;

		private:
			void parseText(const String& text);

		public:
			HttpRequest(const String &text);
			HttpRequest(const HttpRequest &other);

			inline const String& getMethod() const { return _method; }
			inline const String& getUri() const { return _uri; }
			inline String getHeader(const String &name) const;
	};

	/// \brief Resposta HTTP
	///
	class HttpResponse {
		private:
			unsigned _statusCode;
			String _statusMessage;
			String _body;

		private:
			String printText() const;

		public:
			HttpResponse();
			HttpResponse(unsigned statusCode, const String &statusMessage, const String &body);
			HttpResponse(const HttpResponse &other);

			String getText() const;
	};

	/// \brief Controlador de verbs del servidor HTTP
	///
	class HttpController {
		public:
        	typedef ICallbackP1R<HttpResponse, const HttpRequest&> ICallback;

		private:
			String _method;
			ICallback *_callback;

		public:
			HttpController(const String &method, ICallback *callback);

			bool canProcess(const HttpRequest &request) const;
			HttpResponse process(const HttpRequest &request);

			inline const String & getMethod() const { return _method; }
	};


	/// \brief Servidor HTTP
	///
    class HttpServer {
    	private:
            typedef CallbackP1R<HttpServer, HttpResponse, const HttpRequest&> ControllerCallback;
		    typedef Vector<HttpController*> ControllerList;
    		typedef CONNECTION_HANDLER HConnection;

    	private:
    		ControllerList _controllers;
    		ControllerCallback _getCallback;
    		ControllerCallback _headCallback;
    		ControllerCallback _postCallback;
    		uint8_t _port;

    	private:
    		void error(HConnection hConnection);
    		HttpResponse getHandler(const HttpRequest& request);
    		HttpResponse headHandler(const HttpRequest& request);
    		HttpResponse postHandler(const HttpRequest& request);

        public:
            HttpServer(uint8_t port);
            
            void addController(HttpController* controller);

            void initialize();
            void run();
    };
}


#endif // __httpServer__
