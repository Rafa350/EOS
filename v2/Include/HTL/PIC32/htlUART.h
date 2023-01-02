#pragma once
#ifndef __PIC32_htlUART__
#define __PIC32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/PIC32/htlGPIO.h"
#include "htlINT.h"


namespace htl {

	enum class UARTChannel {
        #ifdef _UART1
            channel1,
        #endif
        #ifdef _UART2
            channel2,
        #endif
        #ifdef _UART3
            channel3,
        #endif
        #ifdef _UART4
            channel4,
        #endif
        #ifdef _UART5
            channel5,
        #endif
        #ifdef _UART6
            channel6,
        #endif
	};

    enum class UARTMode {
        send,
        receive,
        bidirectional,
    };

    enum class UARTParity {
        none,
        even,
        odd
    };

    enum class UARTStopBits {
        _1,
        _2
    };

    enum class UARTWordBits {
        _8,
        _9
    };

    enum class UARTHandsake {
        none,
        ctsrts
    };

    enum class UARTBaudMode {
        _1200,
        _2400,
        _4800,
        _9600,
        _19200,
        _38400,
        _56800,
        _115200
    };

    enum class UARTFlag {
        txEmpty,
        rxNotEmpty,
        error
    };

    enum class UARTInterrupt {
        txEmpty,
        rxNotEmpty,
        error
    };

    struct __attribute__((packed , aligned(4))) UARTRegisters {
        __U1MODEbits_t    UxMODE;
        volatile uint32_t UxMODECLR;
        volatile uint32_t UxMODESET;
        volatile uint32_t UxMODEINV;
        __U1STAbits_t     UxSTA;
        volatile uint32_t UxSTACLR;
        volatile uint32_t UxSTASET;
        volatile uint32_t UxSTAINV;
        volatile uint32_t UxTXREG;
        volatile uint32_t offset1[3];
        volatile uint32_t UxRXREG;
        volatile uint32_t offset2[3];
        volatile uint32_t UxBRG;
    };

    using UARTInterruptParam = void*;
    using UARTInterruptFunction = void (*)(UARTInterruptParam);

    void UART_initialize(UARTRegisters*);
    void UART_deinitialize(UARTRegisters*);
    void UART_setTimming(UARTRegisters*, UARTBaudMode);
    void UART_setProtocol(UARTRegisters*, UARTWordBits, UARTParity, UARTStopBits, UARTHandsake);

    template <UARTChannel>
    struct UARTTrait {
    };

	template <UARTChannel channel_>
	class UART_x {
        private:
            using Trait = UARTTrait<channel_>;

		public:
			constexpr static const UARTChannel channel = channel_;

        private:
            constexpr static const uint32_t _addr = Trait::addr;

            static UARTInterruptFunction _isrFunction;
            static UARTInterruptParam _isrParam;

        private:
            UART_x() = delete;
            UART_x(const UART_x &) = delete;
            UART_x(const UART_x &&) = delete;
            ~UART_x() = delete;

            UART_x & operator = (const UART_x &) = delete;
            UART_x & operator = (const UART_x &&) = delete;

		public:
			static void initialize() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_initialize(regs);
			}

			static void deinitialize() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_deinitialize(regs);
			}

            static void enable() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxMODE.ON = 1;
            }

            static void enableTX() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxSTA.UTXEN = 1;
            }

            static void enableRX() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxSTA.URXEN = 1;
            }

            static void disable() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxMODE.ON = 0;
            }

            static void disableTX() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxSTA.UTXEN = 0;
            }

            static void disableRX() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxSTA.URXEN = 0;
            }

            static void setTimming(
                UARTBaudMode baudMode)  {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_setTimming(regs, baudMode);
            }

            static void setProtocol(
                UARTWordBits wordBits,
                UARTParity parity,
                UARTStopBits stopBits,
                UARTHandsake handsake = UARTHandsake::none) {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_setProtocol(regs, wordBits, parity, stopBits, handsake);
            }

			template <typename gpio_>
			static void initTXPin() {

                gpio_::initOutput(GPIODriver::pushPull,	GPIOSpeed::fast);
			}

			template <typename gpio_>
			static void initRXPin() {

				gpio_::initInput();
			}

			static void write(uint8_t data) {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxTXREG = data;
			}

            static uint8_t read() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                return regs->UxRXREG;
            }

            static void enableInterrupt(
                UARTInterrupt event) {

                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch (event) {
                            case UARTInterrupt::error:
                                IEC0bits.U1EIE = 1;
                                break;

                            case UARTInterrupt::txEmpty:
                                IEC0bits.U1TXIE = 1;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                IEC0bits.U1RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch (event) {
                            case UARTInterrupt::error:
                                IEC1bits.U2EIE = 1;
                                break;

                            case UARTInterrupt::txEmpty:
                                IEC1bits.U2TXIE = 1;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                IEC1bits.U2RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch (event) {
                            case UARTInterrupt::error:
                                IEC1bits.U3EIE = 1;
                                break;

                            case UARTInterrupt::txEmpty:
                                IEC1bits.U3TXIE = 1;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                IEC1bits.U3RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch (event) {
                            case UARTInterrupt::error:
                                IEC2bits.U4EIE = 1;
                                break;

                            case UARTInterrupt::txEmpty:
                                IEC2bits.U4TXIE = 1;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                IEC2bits.U4RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch (event) {
                            case UARTInterrupt::error:
                                IEC2bits.U5EIE = 1;
                                break;

                            case UARTInterrupt::txEmpty:
                                IEC2bits.U5TXIE = 1;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                IEC2bits.U5RXIE = 1;
                                break;
                        }
                #endif
            }

            static bool disableInterrupt(
                UARTInterrupt event) {

                bool state = false;

                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1) {
                        switch (event) {
                            case UARTInterrupt::error:
                                state = IEC0bits.U1EIE;
                                IEC0bits.U1EIE = 0;
                                break;

                            case UARTInterrupt::txEmpty:
                                state = IEC0bits.U1TXIE;
                                IEC0bits.U1TXIE = 0;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                state = IEC0bits.U1RXIE;
                                IEC0bits.U1RXIE = 0;
                                break;
                        }
                    }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2) {
                        switch (event) {
                            case UARTInterrupt::error:
                                state = IEC1bits.U2EIE;
                                IEC1bits.U2EIE = 0;
                                break;

                            case UARTInterrupt::txEmpty:
                                state = IEC1bits.U2TXIE;
                                IEC1bits.U2TXIE = 0;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                state = IEC1bits.U2RXIE;
                                IEC1bits.U2RXIE = 0;
                                break;
                        }
                    }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3) {
                        switch (event) {
                            case UARTInterrupt::error:
                                state = IEC1bits.U3EIE;
                                IEC1bits.U3EIE = 0;
                                break;

                            case UARTInterrupt::txEmpty:
                                state = IEC1bits.U3TXIE;
                                IEC1bits.U3TXIE = 0;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                state = IEC1bits.U3RXIE;
                                IEC1bits.U3RXIE = 0;
                                break;
                        }
                    }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4) {
                        switch (event) {
                            case UARTInterrupt::error:
                                state = IEC2bits.U4EIE;
                                IEC2bits.U4EIE = 0;
                                break;

                            case UARTInterrupt::txEmpty:
                                state = IEC2bits.U4TXIE;
                                IEC2bits.U4TXIE = 0;
                                break;

                            case UARTInterrupt::rxNotEmpty:
                                state = IEC2bits.U4RXIE;
                                IEC2bits.U4RXIE = 0;
                                break;
                        }
                    }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC2bits.U5EIE;
                                IEC2bits.U5EIE = 0;
                                break;

                            case UARTEvent::txEmpty:
                                state = IEC2bits.U5TXIE;
                                IEC2bits.U5TXIE = 0;
                                break;

                            case UARTEvent::rxNotEmpty:
                                state = IEC2bits.U5RXIE;
                                IEC2bits.U5RXIE = 0;
                                break;
                        }
                    }
                #endif

                return state;
            }

            /// \brief Deshabilita les interrupcions.
            ///
            static void disableInterrupts() {

                disableInterrupt(UARTInterrupt::txEmpty);
                disableInterrupt(UARTInterrupt::rxNotEmpty);
                disableInterrupt(UARTInterrupt::error);
            }

            static bool getFlag(
                UARTFlag flag) {

                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch(flag) {
                            case UARTFlag::error:
                                return IFS0bits.U1EIF;

                            case UARTFlag::txEmpty:
                                return IFS0bits.U1TXIF;

                            case UARTFlag::rxNotEmpty:
                                return IFS0bits.U1RXIF;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch(flag) {
                            case UARTFlag::error:
                                return IFS1bits.U2EIF;

                            case UARTFlag::txEmpty:
                                return IFS1bits.U2TXIF;

                            case UARTFlag::rxNotEmpty:
                                return IFS1bits.U2RXIF;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch(flag) {
                            case UARTFlah::error:
                                return IFS1bits.U3EIF;

                            case UARTFlag::txEmpty:
                                return IFS1bits.U3TXIF;

                            case UARTFlag::rxNotEmpty:
                                return IFS1bits.U3RXIF;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch(flag) {
                            case UARTFlag::error:
                                return IFS2bits.U4EIF;

                            case UARTFlag::txEmpty:
                                return IFS2bits.U4TXIF;

                            case UARTFlag::rxNotEmpty:
                                return IFS2bits.U4RXIF;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch(flag) {
                            case UARTFlag::error:
                                return IFS2bits.U5EIF;

                            case UARTFlag::txEmpty:
                                return IFS2bits.U5TXIF;

                            case UARTFlag::rxNotEmpty:
                                return IFS2bits.U5RXIF;
                        }
                #endif

                return false;
            }

            static void clearFlag(
                UARTFlag flag) {

                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch(flag) {
                            case UARTFlag::error:
                                IFS0bits.U1EIF = 0;
                                break;

                            case UARTFlag::txEmpty:
                                IFS0bits.U1TXIF = 0;
                                break;

                            case UARTFlag::rxNotEmpty:
                                IFS0bits.U1RXIF = 0;
                                break;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch(flag) {
                            case UARTFlag::error:
                                IFS1bits.U2EIF = 0;
                                break;

                            case UARTFlag::txEmpty:
                                IFS1bits.U2TXIF = 0;
                                break;

                            case UARTFlag::rxNotEmpty:
                                IFS1bits.U2RXIF = 0;
                                break;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch(flag) {
                            case UARTEvent::error:
                                IFS1bits.U3EIF = 0;
                                break;

                            case UARTEvent::txEmpty:
                                IFS1bits.U3TXIF = 0;
                                break;

                            case UARTEvent::rxNotEmpty:
                                IFS1bits.U3RXIF = 0;
                                break;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch(flag) {
                            case UARTEvent::error:
                                IFS2bits.U4EIF = 0;
                                break;

                            case UARTEvent::txEmpty:
                                IFS2bits.U4TXIF = 0;
                                break;

                            case UARTEvent::rxNotEmpty:
                                IFS2bits.U4RXIF = 0;
                                break;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch(flag) {
                            case UARTEvent::error:
                                IFS2bits.U5EIF = 0;
                                break;

                            case UARTEvent::txEmpty:
                                IFS2bits.U5TXIF = 0;
                                break;

                            case UARTEvent::rxNotEmpty:
                                IFS2bits.U5RXIF = 0;
                                break;
                        }
                #endif
            }

            static void clearFlags() {

                clearFlag(UARTFlag::txEmpty);
                clearFlag(UARTFlag::rxNotEmpty);
                clearFlag(UARTFlag::error);
            }

            static void setInterruptFunction(
                UARTInterruptFunction function,
                UARTInterruptParam param = nullptr) {

                _isrFunction = function;
                _isrParam = param;
            }

            static void interruptHandler() {

                if (_isrFunction != nullptr)
                    _isrFunction(_isrParam);
            }
	};

    template <UARTChannel channel_> UARTInterruptFunction UART_x<channel_>::_isrFunction = nullptr;
    template <UARTChannel channel_> UARTInterruptParam UART_x<channel_>::_isrParam = nullptr;

    #ifdef _UART1
        template <>
        struct UARTTrait<UARTChannel::channel1> {
            constexpr static const uint32_t addr = _UART1_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart1;
        };
    #endif
    #ifdef _UART2
        template <>
        struct UARTTrait<UARTChannel::channel2> {
            constexpr static const uint32_t addr = _UART2_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart2;
        };
    #endif
    #ifdef _UART3
        template <>
        struct UARTTrait<UARTChannel::channel3> {
            constexpr static const uint32_t addr = _UART3_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart3;
        };
    #endif
    #ifdef _UART4
        template <>
        struct UARTTrait<UARTChannel::channel4> {
            constexpr static const uint32_t addr = _UART4_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart3;
        };
    #endif
    #ifdef _UART5
        template <>
        struct UARTTrait<UARTChannel::channel5> {
            constexpr static const uint32_t addr = _UART5_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart5;
        };
    #endif
    #ifdef _UART6
        template <>
        struct UARTTrait<UARTChannel::channel6> {
            constexpr static const uint32_t addr = _UART6_BASE_ADDRESS;
            constexpr static const INTVector vector = INTVector::uart6;
        };
    #endif


    #ifdef _UART1
        using UART_1 = UART_x<UARTChannel::channel1>;
    #endif
    #ifdef _UART2
        using UART_2 = UART_x<UARTChannel::channel2>;
    #endif
    #ifdef _UART3
        using UART_3 = UART_x<UARTChannel::channel3>;
    #endif
    #ifdef _UART4
        using UART_4 = UART_x<UARTChannel::channel4>;
    #endif
    #ifdef _UART5
        using UART_5 = UART_x<UARTChannel::channel5>;
    #endif
    #ifdef _UART6
        using UART_6 = UART_x<UARTChannel::channel6>;
    #endif

}


#endif // __PIC32_htmUART__

