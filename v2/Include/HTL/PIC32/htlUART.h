#pragma once
#ifndef __PIC32_htlUART__
#define __PIC32_htlUART__


// EOS includes
//
#include "eos.h"
#include "HTL/PIC32/htlGPIO.h"


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

    enum class UARTStop {
        s1,
        s2
    };

    enum class UARTLength {
        l8,
        l9
    };

    enum class UARTBaud {
        b110,
        b300,
        b1200,
        b2400,
        b4800,
        b9600,
        b19200,
        b38400,
        b56800,
    };

    enum class UARTEvent {
        error,
        transmit,
        receive
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
    using UARTInterruptFunction = void (*)(UARTEvent, UARTInterruptParam);

    void UART_init(UARTRegisters*, UARTBaud, UARTLength, UARTParity, UARTStop, UARTMode);
    void UART_deInit(UARTRegisters*);

    template <UARTChannel channel_>
    struct UARTInfo {
        static const uint32_t addr;
    };

	template <UARTChannel channel_>
	class UART_x {
        private:
            using Info = UARTInfo<channel_>;

		public:
			constexpr static const UARTChannel channel = channel_;

        private:
            constexpr static const uint32_t _addr = Info::addr;

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
			static void init(
                UARTBaud baud,
                UARTLength length,
                UARTParity parity,
                UARTStop stop,
                UARTMode mode = UARTMode::bidirectional) {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_init(regs, baud, length, parity, stop, mode);
			}

			static void deInit() {

                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                UART_deInit(regs);
			}

			template <typename gpio_>
			inline static void setTXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					gpio_::initOutput(
						GPIOSpeed::fast,
						GPIODriver::pushPull);
			}

			template <typename gpio_>
			inline static void setRXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					gpio_::initInput();
			}

			inline static void send(uint8_t data) {
                UARTRegisters *regs = reinterpret_cast<UARTRegisters*>(_addr);
                regs->UxTXREG = data;
			}

            static void enableInterrupt(UARTEvent event) {
                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch (event) {
                            case UARTEvent::error:
                                IEC0bits.U1EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                IEC0bits.U1TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                IEC0bits.U1RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch (event) {
                            case UARTEvent::error:
                                IEC1bits.U2EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                IEC1bits.U2TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                IEC1bits.U2RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch (event) {
                            case UARTEvent::error:
                                IEC1bits.U3EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                IEC1bits.U3TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                IEC1bits.U3RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch (event) {
                            case UARTEvent::error:
                                IEC2bits.U4EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                IEC2bits.U4TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                IEC2bits.U4RXIE = 1;
                                break;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch (event) {
                            case UARTEvent::error:
                                IEC2bits.U5EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                IEC2bits.U5TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                IEC2bits.U5RXIE = 1;
                                break;
                        }
                #endif
            }

            static bool disableInterrupt(UARTEvent event) {

                bool state = false;

                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC0bits.U1EIE;
                                IEC0bits.U1EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                state = IEC0bits.U1TXIE;
                                IEC0bits.U1TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                state = IEC0bits.U1RXIE;
                                IEC0bits.U1RXIE = 1;
                                break;
                        }
                    }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC1bits.U2EIE;
                                IEC1bits.U2EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                state = IEC1bits.U2TXIE;
                                IEC1bits.U2TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                state = IEC1bits.U2RXIE;
                                IEC1bits.U2RXIE = 1;
                                break;
                        }
                    }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC1bits.U3EIE;
                                IEC1bits.U3EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                state = IEC1bits.U3TXIE;
                                IEC1bits.U3TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                state = IEC1bits.U3RXIE;
                                IEC1bits.U3RXIE = 1;
                                break;
                        }
                    }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC2bits.U4EIE;
                                IEC2bits.U4EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                state = IEC2bits.U4TXIE;
                                IEC2bits.U4TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                state = IEC2bits.U4RXIE;
                                IEC2bits.U4RXIE = 1;
                                break;
                        }
                    }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5) {
                        switch (event) {
                            case UARTEvent::error:
                                state = IEC2bits.U5EIE;
                                IEC2bits.U5EIE = 1;
                                break;

                            case UARTEvent::transmit:
                                state = IEC2bits.U5TXIE;
                                IEC2bits.U5TXIE = 1;
                                break;

                            case UARTEvent::receive:
                                state = IEC2bits.U5RXIE;
                                IEC2bits.U5RXIE = 1;
                                break;
                        }
                    }
                #endif

                return state;
            }

            inline static bool getInterruptFlag(UARTEvent event) {
                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch(event) {
                            case UARTEvent::error:
                                return IFS0bits.U1EIF;

                            case UARTEvent::transmit:
                                return IFS0bits.U1TXIF;

                            case UARTEvent::receive:
                                return IFS0bits.U1RXIF;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch(event) {
                            case UARTEvent::error:
                                return IFS1bits.U2EIF;

                            case UARTEvent::transmit:
                                return IFS1bits.U2TXIF;

                            case UARTEvent::receive:
                                return IFS1bits.U2RXIF;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch(event) {
                            case UARTEvent::error:
                                return IFS1bits.U3EIF;

                            case UARTEvent::transmit:
                                return IFS1bits.U3TXIF;

                            case UARTEvent::receive:
                                return IFS1bits.U3RXIF;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch(event) {
                            case UARTEvent::error:
                                return IFS2bits.U4EIF;

                            case UARTEvent::transmit:
                                return IFS2bits.U4TXIF;

                            case UARTEvent::receive:
                                return IFS2bits.U4RXIF;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch(event) {
                            case UARTEvent::error:
                                return IFS2bits.U5EIF;

                            case UARTEvent::transmit:
                                return IFS2bits.U5TXIF;

                            case UARTEvent::receive:
                                return IFS2bits.U5RXIF;
                        }
                #endif
            }

            inline static void clearInterruptFlag(UARTEvent event) {
                #ifdef _UART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        switch(event) {
                            case UARTEvent::error:
                                IFS0bits.U1EIF = 0;

                            case UARTEvent::transmit:
                                IFS0bits.U1TXIF = 0;

                            case UARTEvent::receive:
                                IFS0bits.U1RXIF = 0;
                        }
                #endif
                #ifdef _UART2
                    if constexpr (channel_ == UARTChannel::channel2)
                        switch(event) {
                            case UARTEvent::error:
                                IFS1bits.U2EIF = 0;

                            case UARTEvent::transmit:
                                IFS1bits.U2TXIF = 0;

                            case UARTEvent::receive:
                                IFS1bits.U2RXIF = 0;
                        }
                #endif
                #ifdef _UART3
                    if constexpr (channel_ == UARTChannel::channel3)
                        switch(event) {
                            case UARTEvent::error:
                                IFS1bits.U3EIF = 0;

                            case UARTEvent::transmit:
                                IFS1bits.U3TXIF = 0;

                            case UARTEvent::receive:
                                IFS1bits.U3RXIF = 0;
                        }
                #endif
                #ifdef _UART4
                    if constexpr (channel_ == UARTChannel::channel4)
                        switch(event) {
                            case UARTEvent::error:
                                IFS2bits.U4EIF = 0;

                            case UARTEvent::transmit:
                                IFS2bits.U4TXIF = 0;

                            case UARTEvent::receive:
                                IFS2bits.U4RXIF = 0;
                        }
                #endif
                #ifdef _UART5
                    if constexpr (channel_ == UARTChannel::channel5)
                        switch(event) {
                            case UARTEvent::error:
                                IFS2bits.U5EIF = 0;

                            case UARTEvent::transmit:
                                IFS2bits.U5TXIF = 0;

                            case UARTEvent::receive:
                                IFS2bits.U5RXIF = 0;
                        }
                #endif
            }

            static void setInterruptFunction(UARTInterruptFunction function, UARTInterruptParam param = nullptr) {
                _isrFunction = function;
                _isrParam = param;
            }

            static void interruptHandler(UARTEvent event) {
                if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
	};

    #ifdef _UART1
        template <>
        struct UARTInfo<UARTChannel::channel1> {
            constexpr static const uint32_t addr = _UART1_BASE_ADDRESS;
        };
    #endif
    #ifdef _UART2
        template <>
        struct UARTInfo<UARTChannel::channel2> {
            constexpr static const uint32_t addr = _UART2_BASE_ADDRESS;
        };
    #endif
    #ifdef _UART3
        template <>
        struct UARTInfo<UARTChannel::channel3> {
            constexpr static const uint32_t addr = _UART3_BASE_ADDRESS;
        };
    #endif
    #ifdef _UART4
        template <>
        struct UARTInfo<UARTChannel::channel4> {
            constexpr static const uint32_t addr = _UART4_BASE_ADDRESS;
        };
    #endif
    #ifdef _UART5
        template <>
        struct UARTInfo<UARTChannel::channel5> {
            constexpr static const uint32_t addr = _UART5_BASE_ADDRESS;
        };
    #endif
    #ifdef _UART6
        template <>
        struct UARTInfo<UARTChannel::channel6> {
            constexpr static const uint32_t addr = _UART6_BASE_ADDRESS;
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


#endif // __PIC32_halUARTTpl__

