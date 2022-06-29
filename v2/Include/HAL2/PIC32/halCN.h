#ifndef __PIC32_hal2CN__
#define __PIC32_hal2CN__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_CN_LINE_0             hal::CN::Line::line0
#define HAL_CN_LINE_1             hal::CN::Line::line1
#define HAL_CN_LINE_2             hal::CN::Line::line2
#define HAL_CN_LINE_3             hal::CN::Line::line3
#define HAL_CN_LINE_4             hal::CN::Line::line4
#define HAL_CN_LINE_5             hal::CN::Line::line5
#define HAL_CN_LINE_6             hal::CN::Line::line6
#define HAL_CN_LINE_7             hal::CN::Line::line7
#define HAL_CN_LINE_8             hal::CN::Line::line8
#define HAL_CN_LINE_9             hal::CN::Line::line9
#define HAL_CN_LINE_10            hal::CN::Line::line10
#define HAL_CN_LINE_11            hal::CN::Line::line11
#define HAL_CN_LINE_12            hal::CN::Line::line12
#define HAL_CN_LINE_13            hal::CN::Line::line13
#define HAL_CN_LINE_14            hal::CN::Line::line14
#define HAL_CN_LINE_15            hal::CN::Line::line15
#define HAL_CN_LINE_16            hal::CN::Line::line16
#define HAL_CN_LINE_17            hal::CN::Line::line17
#define HAL_CN_LINE_18            hal::CN::Line::line18
#define HAL_CN_LINE_19            hal::CN::Line::line19
#define HAL_CN_LINE_20            hal::CN::Line::line20
#define HAL_CN_LINE_21            hal::CN::Line::line21


namespace hal {

    class CN {
        public:
            enum class Line {
                line0, line1, line2, line3, line4, line5, line6, line7,
                line8, line9, line10, line11, line12, line13, line14, line15,
                line16, line17, line18, line19, line20, line21
            };

            enum class Trigger {
                none,
                rising,
                falling,
                changing
            };

        private:
            int _lineNumber;

            static int getLineNumber(Line line);

        public:
            CN(Line line);
            CN(const CN &cn);

            void initialize(Trigger trigger, bool pullUp);

            void enableInterrupt();
            void disableInterrupt();

            CN & operator = (const CN &cn);
    };

}


#endif // __PIC32_hal2CN__

