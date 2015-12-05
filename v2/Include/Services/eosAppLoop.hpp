#ifndef __EOS_APPLOOP_HPP
#define	__EOS_APPLOOP_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif

#ifndef __EOS_TASK_HPP
#include "System/Core/eosTask.hpp"
#endif


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

