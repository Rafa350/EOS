#ifndef __EOS_APPLOOP_HPP
#define	__EOS_APPLOOP_HPP


#include "System/eosTask.hpp"


namespace eos {
    
    class AppLoopService: private IRunable {

        private:
            Task task;
                
        public:
            AppLoopService();
        private:
            void run();
    };
}

#endif	

