#ifndef __EOS_APPLOOP_HPP
#define	__EOS_APPLOOP_HPP


#include "System/eosTask.hpp"


namespace eos {
    
    class AppLoopService {
        
        class ServiceTask: public Task {
            public:
                ServiceTask():Task(512, 5){}
                void run();
        };
        
        public:
            AppLoopService();
        private:
            ServiceTask task;
    };
}

#endif	

