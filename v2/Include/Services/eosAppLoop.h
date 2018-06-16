#ifndef __eosAppLoop__
#define	__eosAppLoop__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Application;

    /// \brief Clase que implementa el servei del bucle principal
    ///        de l'aplicacio.
    ///
    class AppLoopService: public Service {
        public:
            AppLoopService(Application *application);
            AppLoopService(Application *application, unsigned stackSize, TaskPriority prioirity);

        protected:
            void onSetup();
            void onLoop();
    };
}

#endif // __eosAppLoop__

