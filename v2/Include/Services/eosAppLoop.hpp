#ifndef __EOS_SERVICES_APPLOOP_HPP
#define	__EOS_SERVICES_APPLOOP_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"


namespace eos {
    
    /// \brief Clase que implementa el servei del bucle principal 
    ///        de l'aplicacio.
    ///
    class AppLoopService: private IRunable {

        private:
            Task task;
                
        public:
            AppLoopService();
            
        protected:
            virtual void setup();
            virtual void loop();
            
        private:
            void run();
    };
}

#endif	

