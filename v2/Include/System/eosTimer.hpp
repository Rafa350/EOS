#ifndef __EOS_TIMER_H
#define	__EOS_TIMER_H


#include "eos.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosList.hpp"


namespace eos {
    
    class Timer;
    typedef Timer *TimerHandle;

    class Timer {
        private:
            typedef ICallbackP1<TimerHandle> ITimerEvent;
            
        private:
            void *handler;     
            bool autoreload;
            void *tag;
            ITimerEvent *evTimeout;
            
        public:
            Timer(bool autoreload = false);
            ~Timer();
            void start(unsigned timeout, unsigned blockTime);
            void stop(unsigned blockTime);
            
            /// \brief Asigna el event onTimeout
            /// \param instance: La instancia
            /// \param method: El metode
            ///
            template <class cls>
            void setEvTimeout(cls *instance, void (cls::*method)(TimerHandle timer)) { 
                
                evTimeout = new CallbackP1<cls, TimerHandle>(instance, method);
            }
            
            inline void setTag(void *tag) { this->tag = tag; }
            inline void *getTag() const { return tag; }
            bool isActive() const;
        private:
            static void timerCallback(void *handler);
    };
}


#endif	
