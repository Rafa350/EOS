#pragma once
#ifndef __eosHTTPService__
#define __eosHTTPService__


#include "eos.h"
#include "Services/eosService.h"
#include "Services/Http/eosHttpServer.h"


namespace eos {

    class HTTPService: public Service {
        public:
            static constexpr uint32_t stackSize = 300;
            static constexpr const char *serviceName = "HTTPS";

    	private:
    		HttpServer httpServer;

		protected:
			void onExecute() override;

		public:
            HTTPService();
    };

}


#endif // __eosHTTPService__
