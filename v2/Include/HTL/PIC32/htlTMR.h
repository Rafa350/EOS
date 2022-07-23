#pragma once
#ifndef __PIC32_htlTMR__
#define __PIC32_htlTMR__


// EOS includes
//
#include "eos.h"
#include "htlRegisters.h"


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
        update
    };

    struct  __attribute__((packed , aligned(4))) TMRRegistersT1 {
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

    struct  __attribute__((packed , aligned(4))) TMRRegistersT2 {
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

    using TMRInterruptParam = void*;
    using TMRInterruptFunction = void (*)(TMREvent event, TMRInterruptParam param);

    template <TMRTimer timer_>
    struct TMRTimerTrait {
    };

    template <TMRTimer timer_>
    class TMR_x {
        private:
            using TimerTrait = TMRTimerTrait<timer_>;
            using IF = typename TimerTrait::IF;
            using IE = typename TimerTrait::IE;

        private:
            constexpr static const uint32_t _addr = TimerTrait::addr;
            constexpr static const bool _isT1 = TimerTrait::isT1;
            constexpr static const bool _isT2 = !TimerTrait::isT1;
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
            /// \brief Inicialitza i activa el modul
            ///
            static void init() {
                stop();
            }

            /// \brief Desinicialitza i desactiva el modul
            ///
            static void deInit() {
                stop();
            }

            /// \brief Asigna el divisor de la base de temps.
            /// \param divider: Opcions del divisor
            ///
            static void setClockDivider(
                TMRClockDivider divider) {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
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
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
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

            /// \brief Asigna l'origen de la base de temps.
            /// \param source: L'origen la base de temps.
            ///
            static void setClockSource(
                TMRClockSource source) {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
                    regs->T1xCON.TCS = 0;
                }
                else {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->T2xCON.TCS = 0;
                }
            }

            /// \brief Asigna la resolucio.
            /// \param resolution: Les opcions de resolucio.
            ///
            static void setResolution(
                TMRResolution resolution) {

                if constexpr (_isT2) {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->T2xCON.T32 = resolution == TMRResolution::res32;
                }
            }

            /// \brief Asigna el valor del contador.
            /// \param counter: El valor del contador.
            ///
            static void setCounter(
                uint32_t counter) {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
                    regs->TMRx = counter & 0xFFFF;
                }
                else {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->TMRx = counter & 0xFFFF;
                    if (regs->T2xCON.T32 == 1) {
                        TMRRegistersT2 *regs32 = reinterpret_cast<TMRRegistersT2*>(_addr + 0x200);
                        regs32->TMRx = (counter >> 16) & 0xFFFF;
                    }
                }
            }

            /// \brief Asigna el valor del periode.
            /// \param period: El valor del periode.
            ///
            static void setPeriod(
                uint32_t period) {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
                    regs->PRx = period & 0xFFFF;
                }
                else {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->PRx = period & 0xFFFF;
                    if (regs->T2xCON.T32 == 1) {
                        TMRRegistersT2 *regs32 = reinterpret_cast<TMRRegistersT2*>(_addr + 0x200);
                        regs32->PRx = (period >> 16) & 0xFFFF;
                    }
                }
            }

            /// \brief Activa el contador.
            ///
            static void start() {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
                    regs->T1xCON.ON = 1;
                }
                else {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->T2xCON.ON = 1;
                }
            }

            /// \brief Desactiva el contador.
            ///
            static void stop() {

                if constexpr (_isT1) {
                    TMRRegistersT1 *regs = reinterpret_cast<TMRRegistersT1*>(_addr);
                    regs->T1xCON.ON = 0;
                }
                else {
                    TMRRegistersT2 *regs = reinterpret_cast<TMRRegistersT2*>(_addr);
                    regs->T2xCON.ON = 0;
                }
            }

            static void enableInterrupt(
                TMREvent event) {

                IE::set();
            }

            static bool disableInterrupt(
                TMREvent event) {

                bool state = IE::value();
                IE::clr();
                return state;
            }

            inline static bool getInterruptFlag(
                TMREvent event) {

                return IF::value();
            }

            inline static void clearInterruptFlag(
                TMREvent event) {

                IF::clr();
            }

            static void setInterruptFunction(
                TMRInterruptFunction function,
                TMRInterruptParam param = nullptr) {

                _isrFunction = function;
                _isrParam = param;
            }

            /// \brief Invoca la funcio d'interrupcio
            /// \param event: L'event.
            ///
            static void interruptHandler(
                TMREvent event) {

                if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
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
        struct TMRTimerTrait<TMRTimer::timer1> {
            using IF = FLAG_CSI<uint32_t, &IFS0, _IFS0_T1IF_POSITION>;
            using IE = FLAG_CSI<uint32_t, &IEC0, _IEC0_T1IE_POSITION>;
            static const uint32_t addr = _TMR1_BASE_ADDRESS;
            static const bool isT1 = true;
        };
    #endif

    #ifdef _TMR2
        template <>
        struct TMRTimerTrait<TMRTimer::timer2> {
            using IF = FLAG_CSI<uint32_t, &IFS0, _IFS0_T2IF_POSITION>;
            using IE = FLAG_CSI<uint32_t, &IEC0, _IEC0_T2IE_POSITION>;
            static const uint32_t addr = _TMR2_BASE_ADDRESS;
            static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR3
        template <>
        struct TMRTimerTrait<TMRTimer::timer3> {
            using IF = FLAG_CSI<uint32_t, &IFS0, _IFS0_T3IF_POSITION>;
            using IE = FLAG_CSI<uint32_t, &IEC0, _IEC0_T3IE_POSITION>;
            static const uint32_t addr = _TMR3_BASE_ADDRESS;
            static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR4
        template <>
        struct TMRTimerTrait<TMRTimer::timer4> {
            using IF = FLAG_CSI<uint32_t, &IFS0, _IFS0_T4IF_POSITION>;
            using IE = FLAG_CSI<uint32_t, &IEC0, _IEC0_T4IE_POSITION>;
            static const uint32_t addr = _TMR4_BASE_ADDRESS;
            static const bool isT1 = false;
        };
    #endif

    #ifdef _TMR5
        template <>
        struct TMRTimerTrait<TMRTimer::timer5> {
            using IF = FLAG_CSI<uint32_t, &IFS0, _IFS0_T5IF_POSITION>;
            using IE = FLAG_CSI<uint32_t, &IEC0, _IEC0_T5IE_POSITION>;
            static const uint32_t addr = _TMR5_BASE_ADDRESS;
            static const bool isT1 = false;
        };
    #endif
}


#endif // __PIC32_htlTMR__

