#ifndef __eosTimerService__
#define __eosTimerService__

#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosSemaphore.h"


namespace eos {
    
    class Application;
    class TimerCounter;
       
    class TimerService final : public Service {       
        private:
            enum class OpCode {
                start,
                stop,
                pause,
                resume
            };
            struct Command {
                TimerCounter *timer;
                OpCode opCode;
            };
            typedef Queue<Command> CommandQueue;
            typedef List<TimerCounter*> TimerList;            
            
        private:
            CommandQueue commandQueue;
            TimerList timers;
            TimerList activeTimers;
        
        public:
            TimerService(Application *application);
            ~TimerService();        
            
            void addTimer(TimerCounter *timer);
            void removeTimer(TimerCounter *timer);
            void removeTimers();
            
            void start(TimerCounter *timer, int time);
            void stop(TimerCounter *timer);
            void pause(TimerCounter *timer);
            void resume(TimerCounter *timer);
            
        protected:
            void onTask() override;
            
        private:
            void processActiveTimers();
            void processCommands();
            void waitTime();
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
            int time;
            int counter;
        
        public:
            TimerCounter(TimerService *service, IEventCallback *callback = nullptr);
            ~TimerCounter();
            
            inline void setEventCallback(IEventCallback *callback) { this->callback = callback; }
            
            void start(int time) { service->start(this, time); }
            void stop() { service->stop(this); }
            void pause() { service->pause(this); }
            void resume() { service->resume(this); }
            
        friend TimerService;
    };
}


#endif // __eosTimerService__