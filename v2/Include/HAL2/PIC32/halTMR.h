#ifndef __PIC32_hal2TMR__
#define __PIC32_hal2TMR__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

    class TMR {
        public:
            enum class Timer {
                timer1,
                #ifdef _TMR2
                    timer2,
                #endif
                #ifdef _TMR3
                    timer3,
                #endif
                #ifdef _TMR4
                    timer4,
                #endif
                #ifdef _TMR5
                    timer5
                #endif
            };

            enum class Resolution {
                res16,
                res32
            };

            enum class ClockDivider {
                div1,
                div2,
                div4,
                div8,
                div16,
                div32,
                div64,
                div256
            };

            enum class ClockSource {
                pclk,
                ext
            };

            enum class InterruptEvent {
                update,
            };

        private:
            uint32_t _addr;

			TMR(const TMR &&) = delete;
			TMR & operator = (const TMR &&) = delete;

        public:
            TMR(Timer timer);
            TMR(const TMR &tmr);

            void setClockDivider(ClockDivider divider);
            void setClockSource(ClockSource source);
            void setResolution(Resolution resolution);
            void setCounter(uint32_t counter);
            void setPeriod(uint32_t period);

            void enableInterrupt(InterruptEvent event);
            bool disableInterrupt(InterruptEvent event);
            bool getInterruptFlag(InterruptEvent event);
            void clearInterruptFlag(InterruptEvent event);
            void interruptHandler(InterruptEvent event);

            void start();
            void stop();

            TMR & operator = (const TMR &tmr);
    };

}


#endif // __PIC32_hal2TMR__
