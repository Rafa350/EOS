#ifndef __eosAppLoop__
#define	__eosAppLoop__


#include "eos.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Application;

    /// \brief Clase que implementa el servei del bucle principal
    ///        de l'aplicacio.
    ///
    class AppLoopService: public Service {
    	private:
    		bool initialized;

        public:
            AppLoopService(Application *application);
            AppLoopService(Application *application, unsigned stackSize, TaskPriority prioirity);
            void initialize();

        protected:
            virtual void onSetup();
            virtual void onRun();

        private:
            void run(Task *task);
    };
}

#endif // __eosAppLoop__

