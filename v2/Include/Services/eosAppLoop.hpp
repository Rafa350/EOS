#ifndef __EOS_SERVICES_APPLOOP_HPP
#define	__EOS_SERVICES_APPLOOP_HPP


#include "eos.hpp"
#include "Services/eosService.hpp"


namespace eos {
    
    class Application;
    
    /// \brief Clase que implementa el servei del bucle principal 
    ///        de l'aplicacio.
    ///
    class AppLoopService: public Service {
        public:
            AppLoopService(Application *application);
            
        protected:
            virtual void setup();
            virtual void loop();
            
        private:
            void run(Task *task);
    };
}

#endif	

