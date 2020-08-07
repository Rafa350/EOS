#ifndef __eosHTTPService__
#define __eosHTTPService__


#include "eos.h"
#include "Services/eosService.h"
#include "Services/Http/eosHttpServer.h"


namespace eos {
    
    class HTTPService: public Service {
    	public:
    		struct InitParams {
    		};

    	private:
    		HttpServer httpServer;

		protected:
			void onInitialize() override;
			void onTask() override;

		public:
            HTTPService(Application* application);
    };
    
}


#endif // __eosHTTPService__
