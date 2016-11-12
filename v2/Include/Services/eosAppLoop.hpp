#ifndef __EOS_APPLOOP_HPP
#define	__EOS_APPLOOP_HPP


#include "eos.hpp"
#include "Services/eosService.hpp"


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
            void initialize();

        protected:
            virtual void onSetup();
            virtual void onRun();

        private:
            void run(Task *task);
    };
}

#endif

