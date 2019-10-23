#ifndef __eosTimerService__
#define __eosTimerService__


#include "eos.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosCallbacks.h"
#include "Services/eosService.h"


namespace eos {
    
    class Application;
    class TimerCounter;
    
    struct TimerServiceConfiguration {
        ServiceConfiguration serviceConfiguration;
        
    };
    
    class TimerService: public Service {
        
        private:
            List<TimerCounter, 10> TimerCounterList;
            
        private:
            TimerCounterList counters;
        
        public:
            TimerService(Application *application);
            ~TimerService();        
    };
    
    class TimerCounter {
        
        public:
            TimerCounter(TimerService *service);
            ~TimerCounter();
            
        friend TimerService;
    }
}


#endif // __eosTimerService__