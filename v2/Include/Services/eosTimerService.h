#ifndef __eosTimerService__
#define __eosTimerService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosEvents.h"
#include "System/Core/eosQueue.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

	class TimerCounter;

    using TimerList = IntrusiveForwardList<TimerCounter, 1>;
    using TimerListNode = IntrusiveForwardListNode<TimerCounter, 1>;


    class TimerService final : public Service {
        public:
            enum class NotifyID {
            	timeout,
            };
            struct NotifyEventArgs {
            	union {
            		struct {
            			TimerCounter *timer;
            		} timeout;
            	};
            };
			using ER = NotifyEventRaiser<NotifyID, NotifyEventArgs>;
			using INotifyEvent = ER::IEvent;
			template <typename Instance_> using NotifyEvent = ER::Event<Instance_>;

        private:
            enum class CommandID {
                timerStart,
                timerStop,
                timerPause,
                timerResume,
                tick
            };
            struct Command {
                CommandID id;
                union {
                	struct {
                        TimerCounter* timer;
                        unsigned period;
                        bool autorestart;
                	} timerStart;
                	struct {
                        TimerCounter* timer;
                	} timerStop;
                	struct {
                        TimerCounter* timer;
                	} timerPause;
                	struct {
                        TimerCounter* timer;
                	} timerResume;
                	struct {
                	} tick;
                };
            };
			using CommandQueue = Queue<Command>;

        private:
			constexpr static const unsigned _commandQueueSize = 4;

        private:
			TimerList _timers;
            CommandQueue _commandQueue;
            ER _erNotify;
            unsigned _ticks;

        private:
            void commandDispatcher(const Command &command) const;
            bool updateTicks();

            void timeout(TimerCounter *timer) const;

            void notifyTimeout(TimerCounter *timer) const;

        protected:
            void onExecute() override;

        public:
            TimerService();

            void addTimer(TimerCounter *timer);
            void removeTimer(TimerCounter *timer);
            void removeTimers();

            inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
            	_erNotify.set(event, enabled);
            }
            inline void enableNotifyEvent() {
            	_erNotify.enable();
            }
            inline void disableNotifyEvent() {
            	_erNotify.disable();
            }

            void start(TimerCounter *timer, unsigned period, bool autorestart, unsigned blockTime);
            void stop(TimerCounter *timer, unsigned blockTime);
            void pause(TimerCounter *timer, unsigned blockTime);
            void resume(TimerCounter *timer, unsigned blockTime);

            void tick(unsigned blockTime);
            void tickISR();
    };

    class TimerCounter final: public TimerListNode {
        public:
            enum class State {
                running,
                stoped,
				paused
            };

        private:
            TimerService *_service;
            State _state;
            bool _autorestart;
            unsigned _period;
            unsigned _counter;

        private:
            void processStart(unsigned period, bool autorestart);
            void processStop();
            void processPause();
            void processResume();
            bool processTick();

        public:
            TimerCounter(TimerService* service);
            ~TimerCounter();

            void start(unsigned period, bool autorestart, unsigned blockTime = ((unsigned) -1)) {
                _service->start(this, period, autorestart, blockTime);
            }

            void stop(unsigned blockTime = ((unsigned) -1)) {
                _service->stop(this, blockTime);
            }

            void pause(unsigned blockTime = ((unsigned) -1)) {
                _service->pause(this, blockTime);
            }

            void resume(unsigned blockTime = ((unsigned) -1)) {
                _service->resume(this, blockTime);
            }

            State getState() const { return _state; }
            unsigned getCounter() const { return _counter; }

            friend TimerService;
    };

}


#endif // __eosTimerService__
