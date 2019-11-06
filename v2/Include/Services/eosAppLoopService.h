#ifndef __eosAppLoopService__
#define	__eosAppLoopService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"


namespace eos {

    /// \brief Clase que implementa el servei del bucle principal
    ///        de l'aplicacio.
    ///
    class AppLoopService: public Service {
        public:
            struct Configuration {
                const ServiceConfiguration *serviceConfiguration;
            };
            
    	private:
    		bool initialized;

        protected:
            void onInitialize() override;
            void onTask() override;
            virtual void onSetup();
            virtual void onLoop();

        public:
            AppLoopService(Application *application);
            AppLoopService(Application *application, const Configuration *configuration);
    };
}


#endif // __eosAppLoopService__

