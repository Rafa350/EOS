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
                timer1,
                timer2,
                timer3,
                timer4,
                timer5
            };

            enum class ClockDivider {
                div1,
                dir2,
                div4,
                div8,
                div16,
                div32,
                div64,
                div256
            };

        private:
            Registers *_regs;

            static Registers* getRegisterPtr(Timer timer);

        public:
            TMR(Timer timer);
            TMR(const TMR &tmr);

            void initialize(ClockDivider clkDiv, uint32_t period, bool mode32);
            void setCounter(uint32_t counter);
            void setPeriod(uint32_t period);

            void start();
            void stop();
    };

}


#endif // __PIC32_hal2TMR__
