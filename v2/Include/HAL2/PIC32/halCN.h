#ifndef __PIC32_hal2CN__
#define __PIC32_hal2CN__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_CN_LINE_0             CNLine::line0
#define HAL_CN_LINE_1             CNLine::line1
#define HAL_CN_LINE_2             CNLine::line2
#define HAL_CN_LINE_3             CNLine::line3
#define HAL_CN_LINE_4             CNLine::line4
#define HAL_CN_LINE_5             CNLine::line5
#define HAL_CN_LINE_6             CNLine::line6
#define HAL_CN_LINE_7             CNLine::line7
#define HAL_CN_LINE_8             CNLine::line8
#define HAL_CN_LINE_9             CNLine::line9
#define HAL_CN_LINE_10            CNLine::line10
#define HAL_CN_LINE_11            CNLine::line11
#define HAL_CN_LINE_12            CNLine::line12
#define HAL_CN_LINE_13            CNLine::line13
#define HAL_CN_LINE_14            CNLine::line14
#define HAL_CN_LINE_15            CNLine::line15
#define HAL_CN_LINE_16            CNLine::line16
#define HAL_CN_LINE_17            CNLine::line17
#define HAL_CN_LINE_18            CNLine::line18
#define HAL_CN_LINE_19            CNLine::line19
#define HAL_CN_LINE_20            CNLine::line20
#define HAL_CN_LINE_21            CNLine::line21


namespace eos {

    enum class CNLine {
        line0, line1, line2, line3, line4, line5, line6, line7,
        line8, line9, line10, line11, line12, line13, line14, line15,
        line16, line17, line18, line19, line20, line21
    };

    enum class CNTrigger {
        none,
        rising,
        falling,
        changing
    };

    class CN {
        private:
            int _lineNumber;

            static int getLineNumber(CNLine line);

        public:
            CN(CNLine line);
            CN(const CN &cn);

            void initialize(CNTrigger trigger, bool pullUp);

            void enableInterrupt();
            void disableInterrupt();

            CN & operator = (const CN &cn);
    };

}


#endif // __PIC32_hal2CN__

