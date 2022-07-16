#ifndef __PIC32_htlCN__
#define __PIC32_htlCN__


// EOS includes
//
#include "eos.h"


namespace htl {

    enum class CNLine {
        cn0,
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
        cnNone
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

    template <int dummy_>
    class CN_x {
        private:
            static CNInterruptFunction _isrFunction;
            static CNInterruptParam _isrParam;

        private:
            CN_x() = delete;
            CN_x(const CN_x &) = delete;
            CN_x(const CN_x &&) = delete;
            ~CN_x() = delete;

            CN_x & operator = (const CN_x &) = delete;
            CN_x & operator = (const CN_x &&) = delete;

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

    template <int dummy_> CNInterruptFunction CN_x<dummy_>::_isrFunction = nullptr;
    template <int dummy_> CNInterruptParam CN_x<dummy_>::_isrParam = nullptr;

    using CN_1 = CN_x<1>;
}


#endif // __PIC32_thlCN__