#ifndef __EOS_SYSTEM_APPLICATION_HPP
#define	__EOS_SYSTEM_APPLICATION_HPP


#include "eos.hpp"


namespace eos {

    class Application {
        public:
            Application();
            void execute();
        protected:
            virtual void onExecute() { }
            virtual void onInitialize() { }
            virtual void onTerminate() { }
    };
}


#endif	


