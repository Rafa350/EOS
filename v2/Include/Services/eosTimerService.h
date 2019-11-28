#ifndef __eosTimerService__
#define __eosTimerService__

#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosArrayList.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class Application;
    class TimerCounter;

    class TimerService final : public Service {
        private:
            enum class OpCode {
                start,
                stop,
                pause,
                resume,
                timeOut
            };
            struct Command {
                TimerCounter *timer;
                OpCode opCode;
            };
            typedef CallbackP1<TimerService, const Timer::EventArgs&> TimerEventCallback;
            typedef Queue<Command> CommandQueue;
            typedef ArrayList<TimerCounter*> TimerList;

        private:
            CommandQueue commandQueue;
            TimerList timers;
            TimerList activeTimers;
            Timer osTimer;
            TimerEventCallback osTimerEventCallback;

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
            void processTime(int period);
            void osTimerEventHandler(const Timer::EventArgs &args);
    };

    class TimerCounter {
        public:
            struct EventArgs {
                TimerCounter *timer;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;

        private:
            TimerService *service;
            IEventCallback *callback;
            int time;
            int counter;
            bool paused;

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