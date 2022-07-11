#ifndef __PIC32_hal2CN__
#define __PIC32_hal2CN__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_CN_LINE_0             hal::CNLine::cn0
#define HAL_CN_LINE_1             hal::CNLine::cn1
#define HAL_CN_LINE_2             hal::CNLine::cn2
#define HAL_CN_LINE_3             hal::CNLine::cn3
#define HAL_CN_LINE_4             hal::CNLine::cn4
#define HAL_CN_LINE_5             hal::CNLine::cn5
#define HAL_CN_LINE_6             hal::CNLine::cn6
#define HAL_CN_LINE_7             hal::CNLine::cn7
#define HAL_CN_LINE_8             hal::CNLine::cn8
#define HAL_CN_LINE_9             hal::CNLine::cn9
#define HAL_CN_LINE_10            hal::CNLine::cn10
#define HAL_CN_LINE_11            hal::CNLine::cn11
#define HAL_CN_LINE_12            hal::CNLine::cn12
#define HAL_CN_LINE_13            hal::CNLine::cn13
#define HAL_CN_LINE_14            hal::CNLine::cn14
#define HAL_CN_LINE_15            hal::CNLine::cn15
#define HAL_CN_LINE_16            hal::CNLine::cn16
#define HAL_CN_LINE_17            hal::CNLine::cn17
#define HAL_CN_LINE_18            hal::CNLine::cn18
#define HAL_CN_LINE_19            hal::CNLine::cn19
#define HAL_CN_LINE_20            hal::CNLine::cn20
#define HAL_CN_LINE_21            hal::CNLine::cn21


namespace hal {

    enum class CNLine {
        cn0 = 0,
        cn1,
        cn2,
        cn3,
        cn4,
        cn5,
        cn6,
        cn7,
        cn8,
        cn9,
        cn10,
        cn11,
        cn12,
        cn13,
        cn14,
        cn15,
        cn16,
        cn17,
        cn18,
        cn19,
        cn20,
        cn21,
        cnNone = -1
    };

    enum class CNTrigger {
        none,
        rising,
        falling,
        changing
    };

    enum class CNPull {
        none,
        up
    };

    class CN {
        private:
			CN(const CN &&) = delete;
			CN & operator = (const CN &&) = delete;

        public:
            CN();
            CN(const CN &cn);

            void init(CNLine line, CNTrigger trigger = CNTrigger::none, CNPull pull = CNPull::none);

            void enableLine(CNLine line);
            void disableLine(CNLine line);

            void enableInterrupt();
            bool disableInterrupt();
            bool getInterruptFlag();
            void clearInterruptFlags();

            CN & operator = (const CN &cn);
    };
}


#endif // __PIC32_hal2CN__

