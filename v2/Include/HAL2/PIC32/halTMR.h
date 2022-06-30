#ifndef __PIC32_hal2TMR__
#define __PIC32_hal2TMR__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

    class TMR {
        private:
            typedef struct  __attribute__((packed , aligned(4))) {
                union {
                    __T1CONbits_t TAxCON;
                    __T2CONbits_t TBxCON;
                };
                volatile uint32_t TxCONCLR;
                volatile uint32_t TxCONSET;
                volatile uint32_t TxCONINV;
                volatile uint32_t TMRx;
                volatile uint32_t TMRxCLR;
                volatile uint32_t TMRxSET;
                volatile uint32_t TMRxINV;
                volatile uint32_t PRx;
                volatile uint32_t PRxCLR;
                volatile uint32_t PRxSET;
                volatile uint32_t PRxINV;
            } Registers;

        public:
            enum class Timer {
                timer1 = 0,
#ifdef _TMR2
                timer2 = 1,
#endif
#ifdef _TMR3
                timer3 = 2,
#endif
#ifdef _TMR4
                timer4 = 3,
#endif
#ifdef _TMR5
                timer5 = 4
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

        private:
            Registers *_regs;

            static Registers* getRegisterPtr(Timer timer);

        public:
            TMR(Timer timer);
            TMR(const TMR &tmr);

            void setClockDivider(ClockDivider divider);
            void setClockSource(ClockSource source);
            void setResolution(Resolution resolution);
            void setCounter(uint32_t counter);
            void setPeriod(uint32_t period);

            void enableInterrupts(uint32_t event);
            uint32_t disableInterrupts(uint32_t event);
            bool getInterruptFlags(uint32_t event);
            void clearInterruptFlags(uint32_t event);

            void start();
            void stop();
    };

}


#endif // __PIC32_hal2TMR__
