#ifndef __PIC32_htlCN__
#define __PIC32_htlCN__


// EOS includes
//
#include "eos.h"


#define HAL_CN_LINE_0             htl::CNLine::cn0
#define HAL_CN_LINE_1             htl::CNLine::cn1
#define HAL_CN_LINE_2             htl::CNLine::cn2
#define HAL_CN_LINE_3             htl::CNLine::cn3
#define HAL_CN_LINE_4             htl::CNLine::cn4
#define HAL_CN_LINE_5             htl::CNLine::cn5
#define HAL_CN_LINE_6             htl::CNLine::cn6
#define HAL_CN_LINE_7             htl::CNLine::cn7
#define HAL_CN_LINE_8             htl::CNLine::cn8
#define HAL_CN_LINE_9             htl::CNLine::cn9
#define HAL_CN_LINE_10            htl::CNLine::cn10
#define HAL_CN_LINE_11            htl::CNLine::cn11
#define HAL_CN_LINE_12            htl::CNLine::cn12
#define HAL_CN_LINE_13            htl::CNLine::cn13
#define HAL_CN_LINE_14            htl::CNLine::cn14
#define HAL_CN_LINE_15            htl::CNLine::cn15
#define HAL_CN_LINE_16            htl::CNLine::cn16
#define HAL_CN_LINE_17            htl::CNLine::cn17
#define HAL_CN_LINE_18            htl::CNLine::cn18
#define HAL_CN_LINE_19            htl::CNLine::cn19
#define HAL_CN_LINE_20            htl::CNLine::cn20
#define HAL_CN_LINE_21            htl::CNLine::cn21


namespace htl {

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

    enum class CNEvent {
        unknown,
        change
    };

    typedef void *CNInterruptParam ;
    typedef void (*CNInterruptFunction)(CNEvent event, CNInterruptParam);

    class CN {
        private:
            CN() = delete;
            CN(const CN &) = delete;
            CN(const CN &&) = delete;
            ~CN() = delete;

            CN & operator = (const CN &) = delete;
            CN & operator = (const CN &&) = delete;

        private:
            static CNInterruptFunction _isrFunction;
            static CNInterruptParam _isrParam;

        public:
            inline static void init(CNLine line, CNTrigger trigger = CNTrigger::none, CNPull pull = CNPull::none) {
                CNCONbits.ON = 1;
                if (pull == CNPull::up)
                    CNPUESET = 1 << static_cast<uint32_t>(line);
                else
                    CNPUECLR = 1 << static_cast<uint32_t>(line);
            }

            inline static void enableLine(CNLine line) {
                CNENSET = 1 << static_cast<uint32_t>(line);
            }

            inline static void disableLine(CNLine line) {
                CNENCLR = 1 << static_cast<uint32_t>(line);
            }

            inline static void enableInterrupt() {
                IEC1bits.CNIE = 1;
            }

            inline static bool disableInterrupt() {
                bool state = IEC1bits.CNIE == 1;
                IEC1bits.CNIE = 0;
                return state;
            }

            inline static bool getInterruptFlag() {
                return IFS1bits.CNIF != 0;
            }

            inline static void clearInterruptFlags() {
                IFS1bits.CNIF = 0;
            }

            inline static void setInterruptFunction(CNInterruptFunction function, CNInterruptParam param = nullptr) {
                _isrFunction = function;
                _isrParam = param;
            }

            inline static void interruptHandler(CNEvent event) {
                if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
    };

    CNInterruptFunction CN::_isrFunction = nullptr;
    CNInterruptParam CN::_isrParam = nullptr;
}


#endif // __PIC32_thlCN__