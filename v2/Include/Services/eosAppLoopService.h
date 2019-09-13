#ifndef __eosAppLoop__
#define	__eosAppLoop__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"


namespace eos {

	struct AppLoopServiceConfiguration {
		ServiceConfiguration serviceConfiguration;
	};

    /// \brief Clase que implementa el servei del bucle principal
    ///        de l'aplicacio.
    ///
    class AppLoopService: public Service {
    	private:
    		bool initialized;

        protected:
            void onInitialize() override;
            void onTask() override;
            virtual void onSetup();
            virtual void onLoop();

        public:
            AppLoopService(Application *pApplication);
            AppLoopService(Application *pApplication, const AppLoopServiceConfiguration &configuration);
    };
}


#endif // __eosAppLoop__

