#ifndef __EOS_TIMER_HPP
#define	__EOS_TIMER_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"


namespace eos {
    
    class Timer {
        private:
            typedef ICallbackP1<Timer*> ITimerEvent;
            
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
            void setEvTimeout(cls *instance, void (cls::*method)(Timer *timer)) {   
                if (evTimeout != nullptr)
                    delete evTimeout;
                evTimeout = new CallbackP1<cls, Timer*>(instance, method);
            }
            
            inline void setTag(void *tag) { this->tag = tag; }
            inline void *getTag() const { return tag; }
            bool isActive() const;
            
        private:
            static void timerCallback(void *handler);
    };
}


#endif	

