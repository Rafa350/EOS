#ifndef __PIC32_htlTMR__
#define __PIC32_htlTMR__


// EOS includes
//
#include "eos.h"


namespace htl {

    enum class TMRTimer {
        #ifdef _TMR1
            timer1,
        #endif
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
            timer5,
        #endif
        timerNone
    };

    enum class TMRResolution {
        res16,
        res32
    };

    enum class TMRClockDivider {
        div1,
        div2,
        div4,
        div8,
        div16,
        div32,
        div64,
        div256
    };

    enum class TMRClockSource {
        pclk,
        ext
    };

    enum class TMREvent {
        unknown,
        update
    };

    using TMRInterruptParam = void*;
    using TMRInterruptFunction = void (*)(TMREvent event, TMRInterruptParam param);

    template <TMRTimer timer_>
    struct TMRInfo {
        static const uint32_t addr;
        static const bool isT1;
    };

    template <TMRTimer timer_>
    class TMR_x {
        private:
            struct  __attribute__((packed , aligned(4))) RegistersT1 {
                __T1CONbits_t T1xCON;
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
            };
            struct  __attribute__((packed , aligned(4))) RegistersT2 {
                __T2CONbits_t T2xCON;
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
            };
            using Info = TMRInfo<timer_>;

        private:
            constexpr static const uint32_t _addr = Info::addr;
            constexpr static const bool _isT1 = Info::isT1;
            constexpr static const bool _isT2 = !Info::isT1;
            static TMRInterruptFunction _isrFunction;
            static TMRInterruptParam _isrParam;

        private:
            TMR_x() = delete;
            TMR_x(const TMR_x &) = delete;
            TMR_x(const TMR_x &&) = delete;
            ~TMR_x() = delete;

            TMR_x & operator = (const TMR_x &) = delete;
            TMR_x & operator = (const TMR_x &&) = delete;

        public:
            static void init() {
                stop();
            }

            static void deInit() {
                stop();
            }

            static void setClockDivider(TMRClockDivider divider) {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    switch (divider) {
                        case TMRClockDivider::div8:
                            regs->T1xCON.TCKPS = 1;
                            break;

                        case TMRClockDivider::div64:
                            regs->T1xCON.TCKPS = 2;
                            break;

                        case TMRClockDivider::div256:
                            regs->T1xCON.TCKPS = 3;
                            break;

                        default:
                            regs->T1xCON.TCKPS = 0;
                            break;
                    }
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    switch (divider) {
                        case TMRClockDivider::div2:
                            regs->T2xCON.TCKPS = 1;
                            break;

                        case TMRClockDivider::div4:
                            regs->T2xCON.TCKPS = 2;
                            break;

                        case TMRClockDivider::div8:
                            regs->T2xCON.TCKPS = 3;
                            break;

                        case TMRClockDivider::div16:
                            regs->T2xCON.TCKPS = 4;
                            break;

                        case TMRClockDivider::div32:
                            regs->T2xCON.TCKPS = 5;
                            break;

                        case TMRClockDivider::div64:
                            regs->T2xCON.TCKPS = 6;
                            break;

                        case TMRClockDivider::div256:
                            regs->T2xCON.TCKPS = 7;
                            break;

                        default:
                            regs->T2xCON.TCKPS = 0;
                            break;
                    }
                }
            }

            static void setClockSource(TMRClockSource source) {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    regs->T1xCON.TCS = 0;
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->T2xCON.TCS = 0;
                }
            }

            static void setResolution(TMRResolution resolution) {
                if constexpr (_isT2) {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->T2xCON.T32 = resolution == TMRResolution::res32;
                }
            }

            static void setCounter(uint32_t counter) {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    regs->TMRx = counter & 0xFFFF;
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->TMRx = counter & 0xFFFF;
                    if (regs->T2xCON.T32 == 1) {
                        RegistersT2 *regs32 = reinterpret_cast<RegistersT2*>(_addr + 0x200);
                        regs32->TMRx = (counter >> 16) & 0xFFFF;
                    }
                }
            }

            static void setPeriod(uint32_t period) {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    regs->PRx = period & 0xFFFF;
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->PRx = period & 0xFFFF;
                    if (regs->T2xCON.T32 == 1) {
                        RegistersT2 *regs32 = reinterpret_cast<RegistersT2*>(_addr + 0x200);
                        regs32->PRx = (period >> 16) & 0xFFFF;
                    }
                }
            }

            static void enableInterrupt(TMREvent event) {
                #ifdef _TMR1
                    if constexpr (timer_ == TMRTimer::timer1)
                        IEC0bits.T1IE = 1;
                #endif
                #ifdef _TMR2
                    if constexpr (timer_ == TMRTimer::timer2)
                        IEC0bits.T2IE = 1;
                #endif
                #ifdef _TMR3
                    if constexpr (timer_ == TMRTimer::timer3)
                        IEC0bits.T3IE = 1;
                #endif
                #ifdef _TMR4
                    if constexpr (timer_ == TMRTimer::timer4)
                        IEC0bits.T4IE = 1;
                #endif
                #ifdef _TMR5
                    if constexpr (timer_ == TMRTimer::timer5)
                        IEC0bits.T5IE = 1;
                #endif
            }

            static bool disableInterrupt(TMREvent event) {

                bool state = false;

                #ifdef _TMR1
                    if constexpr (timer_ == TMRTimer::timer1) {
                        state = IEC0bits.T1IE;
                        IEC0bits.T1IE = 1;
                    }
                #endif
                #ifdef _TMR2
                    if constexpr (timer_ == TMRTimer::timer2) {
                        state = IEC0bits.T2IE;
                        IEC0bits.T2IE = 1;
                    }
                #endif
                #ifdef _TMR3
                    if constexpr (timer_ == TMRTimer::timer3) {
                        state = IEC0bits.T3IE;
                        IEC0bits.T3IE = 1;
                    }
                #endif
                #ifdef _TMR4
                    if constexpr (timer_ == TMRTimer::timer4) {
                        state = IEC0bits.T4IE;
                        IEC0bits.T4IE = 1;
                    }
                #endif
                #ifdef _TMR5
                    if constexpr (timer_ == TMRTimer::timer5) {
                        state = IEC0bits.T5IE;
                        IEC0bits.T5IE = 1;
                    }
                #endif

                return state;
            }

            inline static bool getInterruptFlag(TMREvent event) {
                #ifdef _TMR1
                    if constexpr (timer_ == TMRTimer::timer1)
                        return IFS0bits.T1IF;
                #endif
                #ifdef _TMR2
                    if constexpr (timer_ == TMRTimer::timer2)
                        return IFS0bits.T2IF;
                #endif
                #ifdef _TMR3
                    if constexpr (timer_ == TMRTimer::timer3)
                        return IFS0bits.T3IF;
                #endif
                #ifdef _TMR4
                    if constexpr (timer_ == TMRTimer::timer4)
                        return IFS0bits.T4IF;
                #endif
                #ifdef _TMR5
                    if constexpr (timer_ == TMRTimer::timer5)
                        return IFS0bits.T5IF;
                #endif
            }

            inline static void clearInterruptFlag(TMREvent event) {
                #ifdef _TMR1
                    if constexpr (timer_ == TMRTimer::timer1)
                        IFS0bits.T1IF = 0;
                #endif
                #ifdef _TMR2
                    if constexpr (timer_ == TMRTimer::timer2)
                        IFS0bits.T2IF = 0;
                #endif
                #ifdef _TMR3
                    if constexpr (timer_ == TMRTimer::timer3)
                        IFS0bits.T3IF = 0;
                #endif
                #ifdef _TMR4
                    if constexpr (timer_ == TMRTimer::timer4)
                        IFS0bits.T4IF = 0;
                #endif
                #ifdef _TMR5
                    if constexpr (timer_ == TMRTimer::timer5)
                        IFS0bits.T5IF = 0;
                #endif
            }

            static void setInterruptFunction(TMRInterruptFunction function, TMRInterruptParam param = nullptr) {
                _isrFunction = function;
                _isrParam = param;
            }

            static void interruptHandler(TMREvent event) {
                if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }

            static void start() {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    regs->T1xCON.ON = 1;
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->T2xCON.ON = 1;
                }
            }

            static void stop() {
                if constexpr (_isT1) {
                    RegistersT1 *regs = reinterpret_cast<RegistersT1*>(_addr);
                    regs->T1xCON.ON = 0;
                }
                else {
                    RegistersT2 *regs = reinterpret_cast<RegistersT2*>(_addr);
                    regs->T2xCON.ON = 0;
                }
            }
    };

    template <TMRTimer timer_> TMRInterruptFunction TMR_x<timer_>::_isrFunction = nullptr;
    template <TMRTimer timer_> TMRInterruptParam TMR_x<timer_>::_isrParam = nullptr;


    #ifdef _TMR1
        using TMR_1 = TMR_x<TMRTimer::timer1>;
    #endif
    #ifdef _TMR2
        using TMR_2 = TMR_x<TMRTimer::timer2>;
    #endif
    #ifdef _TMR3
        using TMR_3 = TMR_x<TMRTimer::timer3>;
    #endif
    #ifdef _TMR4
        using TMR_4 = TMR_x<TMRTimer::timer4>;
    #endif
    #ifdef _TMR5
        using TMR_5 = TMR_x<TMRTimer::timer5>;
    #endif


    #ifdef _TMR1
        template <>
        struct TMRInfo<TMRTimer::timer1> {
            constexpr static const uint32_t addr = _TMR1_BASE_ADDRESS;
            constexpr static const bool isT1 = true;
        };
    #endif

    #ifdef _TMR2
        template <>
        struct TMRInfo<TMRTimer::timer2> {
            constexpr static const uint32_t addr = _TMR2_BASE_ADDRESS;
            constexpr static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR3
        template <>
        struct TMRInfo<TMRTimer::timer3> {
            constexpr static const uint32_t addr = _TMR3_BASE_ADDRESS;
            constexpr static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR4
        template <>
        struct TMRInfo<TMRTimer::timer4> {
            constexpr static const uint32_t addr = _TMR4_BASE_ADDRESS;
            constexpr static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR5
        template <>
        struct TMRInfo<TMRTimer::timer5> {
            constexpr static const uint32_t addr = _TMR5_BASE_ADDRESS;
            constexpr static const bool isT1 = false;
        };
    #endif
}


#endif // __PIC32_htlTMR__

