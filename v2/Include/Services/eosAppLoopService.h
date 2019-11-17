#ifndef __eosAppLoopService__
#define	__eosAppLoopService__

#include "eos.h"
#include "Services/eosService.h"


namespace eos {

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
            AppLoopService(Application *application);
    };
}


#endif // __eosAppLoopService__

