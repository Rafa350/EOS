#ifndef __eosTimerService__
#define __eosTimerService__


#include "eos.h"
#include "System/Collections/eosList.h"
#include "System/eosCallbacks.h"
#include "Services/eosService.h"


namespace eos {
    
    class Application;
    class TimerCounter;
       
    class TimerService: public Service {
        
        private:
            typedef List<TimerCounter*> TimerCounterList;
            
        private:
            TimerCounterList counters;
        
        public:
            TimerService(Application *application);
            ~TimerService();        
            
            void addCounter(TimerCounter *counter);
            void removeCounter(TimerCounter *counter);
            void removeCounters();
            
        private:
            void startCicle();
            void timeOut();
    };
    
    class TimerCounter {
        public:
            struct EventArgs {
                TimerCounter *counter;
            };
            
        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;
            
        private:
            TimerService *service;
            IEventCallback *callback;
        
        public:
            TimerCounter(TimerService *service);
            ~TimerCounter();
            
        friend TimerService;
    };
}


#endif // __eosTimerService__