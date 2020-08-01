#ifndef __eosHTTPService__
#define __eosHTTPService__


#include "eos.h"
#include "Services/eosService.h"


namespace eos {
    
    class HTTPService: public Service {
		protected:
			void onInitialize() override;
			void onTask() override;

		public:
            HTTPService(Application* application);
    };
    
}


#endif // __eosHTTPService__
