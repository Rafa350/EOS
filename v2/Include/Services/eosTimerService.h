#ifndef __eosTimerService__
#define __eosTimerService__


// EOS includes
//
#include "eos.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Collections/eosPriorityQueue.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class TimerCounter;

    class TimerService final : public Service {
        private:
            enum class OpCode: uint8_t {
                start,
                stop,
                pause,
                resume,
                timeOut
            };
            struct Command {
                OpCode opCode;
                union {
                    TimerCounter *timer;
                    unsigned period;
                };
            };
            typedef CallbackP1<TimerService, const Timer::EventArgs&> TimerEventCallback;
            typedef Queue<Command> CommandQueue;
            typedef DynamicArray<TimerCounter*> TimerList;
            typedef DynamicArray<TimerCounter*>::Iterator TimerListIterator;
            typedef PriorityQueue<unsigned, TimerCounter*> TimerQueue;
            //typedef PriorityQueue<unsigned, TimerCounter*>::Iterator TimerQueueIterator;

        public:
            struct InitParams {
                TMRTimer timer;
                unsigned period;
            };

        private:
            CommandQueue commandQueue;
            TimerList timers;
            TimerQueue activeQueue;
            unsigned osPeriod;
            Timer osTimer;
            TimerEventCallback osTimerEventCallback;

        public:
            TimerService(Application* application);
            ~TimerService();

            void addTimer(TimerCounter* timer);
            void removeTimer(TimerCounter* timer);
            void removeTimers();

            void start(TimerCounter* timer, unsigned period, unsigned blockTime);
            void stop(TimerCounter* timer, unsigned blockTime);
            void pause(TimerCounter* timer, unsigned blockTime);
            void resume(TimerCounter *timer, unsigned blockTime);

        protected:
            void onInitialize() override;
            void onTask(Task *task) override;

        private:
            void cmdStart(TimerCounter* timer);
            void cmdStop(TimerCounter* timer);
            void cmdPause(TimerCounter* timer);
            void cmdResume(TimerCounter* timer);
            void cmdTimeOut();
            void osTimerEventHandler(const Timer::EventArgs& args);
    };

    class TimerCounter {
        public:
            enum class EventType: uint8_t {
                start,
                stop,
                pause,
                resume,
                timeout
            };
            struct EventArgs {
                EventType type;
                TimerCounter *timer;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;

        private:
            TimerService *service;
            IEventCallback *eventCallback;
            unsigned period;
            unsigned currentPeriod;
            unsigned expireTime;

        public:
            TimerCounter(TimerService* service, IEventCallback* callback = nullptr);
            ~TimerCounter();

            inline void setEventCallback(IEventCallback* callback) {
                eventCallback = callback;
            }

            void start(unsigned period, unsigned blockTime = ((unsigned)-1)) {
                service->start(this, period, blockTime);
            }

            void stop(unsigned blockTime = ((unsigned)-1)) {
                service->stop(this, blockTime);
            }

            void pause(unsigned blockTime = ((unsigned)-1)) {
                service->pause(this, blockTime);
            }

            void resume(unsigned blockTime = ((unsigned)-1)) {
                service->resume(this, blockTime);
            }

        friend TimerService;
    };

}


#endif // __eosTimerService__