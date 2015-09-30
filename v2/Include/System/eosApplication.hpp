#ifndef __EOS_APPLICATION_HPP
#define	__EOS_APPLICATION_HPP


#include "System/eosProcess.hpp"


namespace eos {

    class Application {
        public:
            Application();
            void addProcess(eos::HProcess process);
            void addQueue();
            void execute();
    };
    
    typedef Application *HApplication;
}


#endif	


