#ifndef __eosTimerService__
#define __eosTimerService__


// EOS includes
//
#include "eos.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosVector.h"
#include "System/Collections/eosPriorityQueue.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class TimerCounter;

    struct QueueComparator {
        bool operator () (const TimerCounter* left, const TimerCounter* right);
    };

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
                    TimerCounter* timer;
                    unsigned period;
                };
            };
            using TimerEventCallback = CallbackP1<TimerService, const Timer::EventArgs&>;
            using CommandQueue = Queue<Command>;
            typedef Vector<TimerCounter*> TimerList;
            typedef TimerList::Iterator TimerIterator;
            typedef PriorityQueue<TimerCounter*, QueueComparator> TimerQueue;

        public:
            struct InitParams {
                halTMRTimer timer;
                unsigned period;
            };

        private:
            CommandQueue _commandQueue;
            TimerList _timers;
            TimerQueue _activeQueue;
            unsigned _osPeriod;
            Timer _osTimer;
            TimerEventCallback _osTimerEventCallback;

        public:
            TimerService(Application *application);
            ~TimerService();

            void addTimer(TimerCounter *timer);
            void removeTimer(TimerCounter *timer);
            void removeTimers();

            void start(TimerCounter *timer, unsigned period, unsigned blockTime);
            void stop(TimerCounter *timer, unsigned blockTime);
            void pause(TimerCounter *timer, unsigned blockTime);
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
            TimerService *_service;
            IEventCallback *_eventCallback;
            unsigned _period;
            unsigned _currentPeriod;
            unsigned _expireTime;

        public:
            TimerCounter(TimerService* service);
            ~TimerCounter();

            inline void setEventCallback(IEventCallback &callback) {
                _eventCallback = &callback;
            }

            void start(unsigned period, unsigned blockTime = ((unsigned)-1)) {
                _service->start(this, period, blockTime);
            }

            void stop(unsigned blockTime = ((unsigned)-1)) {
                _service->stop(this, blockTime);
            }

            void pause(unsigned blockTime = ((unsigned)-1)) {
                _service->pause(this, blockTime);
            }

            void resume(unsigned blockTime = ((unsigned)-1)) {
                _service->resume(this, blockTime);
            }

        friend TimerService;
        friend QueueComparator;
    };

}


#endif // __eosTimerService__