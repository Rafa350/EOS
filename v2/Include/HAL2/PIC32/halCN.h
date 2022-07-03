#ifndef __PIC32_hal2CN__
#define __PIC32_hal2CN__


// HAL includes
//
#include "HAL2/hal.h"
#include "HAL2/PIC32/halGPIO.h"


#define HAL_CN_LINE_0             hal::CNLine::line0
#define HAL_CN_LINE_1             hal::CNLine::line1
#define HAL_CN_LINE_2             hal::CNLine::line2
#define HAL_CN_LINE_3             hal::CNLine::line3
#define HAL_CN_LINE_4             hal::CNLine::line4
#define HAL_CN_LINE_5             hal::CNLine::line5
#define HAL_CN_LINE_6             hal::CNLine::line6
#define HAL_CN_LINE_7             hal::CNLine::line7
#define HAL_CN_LINE_8             hal::CNLine::line8
#define HAL_CN_LINE_9             hal::CNLine::line9
#define HAL_CN_LINE_10            hal::CNLine::line10
#define HAL_CN_LINE_11            hal::CNLine::line11
#define HAL_CN_LINE_12            hal::CNLine::line12
#define HAL_CN_LINE_13            hal::CNLine::line13
#define HAL_CN_LINE_14            hal::CNLine::line14
#define HAL_CN_LINE_15            hal::CNLine::line15
#define HAL_CN_LINE_16            hal::CNLine::line16
#define HAL_CN_LINE_17            hal::CNLine::line17
#define HAL_CN_LINE_18            hal::CNLine::line18
#define HAL_CN_LINE_19            hal::CNLine::line19
#define HAL_CN_LINE_20            hal::CNLine::line20
#define HAL_CN_LINE_21            hal::CNLine::line21


namespace hal {

    class CN {
        public:
            enum class Trigger {
                none,
                rising,
                falling,
                changing
            };

        private:
            int _lineNumber;

        public:
            CN(CNLine line);
            template <typename Info_> CN(Info_ info);
            CN(const CN &cn);

            void setTrigger(Trigger trigger);
            void setPullUp(bool pullUp);

            void enableInterrupt();
            void disableInterrupt();

            CN & operator = (const CN &cn);
    };


    template <typename Info_>
    CN::CN(Info_ info) :
        CN(info.cn) {

    }

}


#endif // __PIC32_hal2CN__

