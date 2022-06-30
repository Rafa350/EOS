#ifndef __PIC32_htlGPIO_ex__
#define __PIC32_htlGPIO_ex__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"


namespace htl {

    enum class GPIOPort: halGPIOPort {
        portA = HAL_GPIO_PORT_A,
        portB = HAL_GPIO_PORT_B,
        portC = HAL_GPIO_PORT_C,
        portD = HAL_GPIO_PORT_D,
        portE = HAL_GPIO_PORT_E,
        portF = HAL_GPIO_PORT_F,
        portG = HAL_GPIO_PORT_G
    };

    enum class GPIOPin: halGPIOPin {
        pin0 = HAL_GPIO_PIN_0,
        pin1 = HAL_GPIO_PIN_1,
        pin2 = HAL_GPIO_PIN_2,
        pin3 = HAL_GPIO_PIN_3,
        pin4 = HAL_GPIO_PIN_4,
        pin5 = HAL_GPIO_PIN_5,
        pin6 = HAL_GPIO_PIN_6,
        pin7 = HAL_GPIO_PIN_7,
        pin8 = HAL_GPIO_PIN_8,
        pin9 = HAL_GPIO_PIN_9,
        pin10 = HAL_GPIO_PIN_10,
        pin11 = HAL_GPIO_PIN_11,
        pin12 = HAL_GPIO_PIN_12,
        pin13 = HAL_GPIO_PIN_13,
        pin14 = HAL_GPIO_PIN_14,
        pin15 = HAL_GPIO_PIN_15
    };

    enum class GPIOSpeed: halGPIOOptions {
        low = HAL_GPIO_SPEED_LOW,
        medium = HAL_GPIO_SPEED_MEDIUM,
        high = HAL_GPIO_SPEED_HIGH,
        fast = HAL_GPIO_SPEED_FAST
    };

    enum class GPIODriver {
        pushPull,
        openDrain
    };

    enum class GPIOState: halGPIOOptions {
        set = HAL_GPIO_INIT_SET,
        clr = HAL_GPIO_INIT_CLR,
        noChange = HAL_GPIO_INIT_NOCHANGE
    };

    template <GPIOPort port_, GPIOPin pin_>
	struct GPIOPinInfo {
		static const uint32_t baseAddr;
		static const uint32_t pinNumber;
	};

    template <GPIOPort port_, GPIOPin pin_>
    class GPIOPinAdapter {
		public:
			constexpr static const GPIOPort port = port_;
			constexpr static const GPIOPin pin = pin_;

        private:
            constexpr static const uint32_t _baseAddr = GPIOPinInfo<port_, pin_>::baseAddr;
            constexpr static const uint32_t _pinNumber = GPIOPinInfo<port_, pin_>::pinNumber;

        public:
			GPIOPinAdapter() = default;
            GPIOPinAdapter(const GPIOPinAdapter &) = delete;
			GPIOPinAdapter(const GPIOPinAdapter &&) = delete;
			GPIOPinAdapter& operator = (const GPIOPinAdapter &) = delete;
			GPIOPinAdapter& operator = (const GPIOPinAdapter &&) = delete;

        public:
            /*inline static auto & instance() {
                static GPIOPinAdapter pinAdapter;
                return pinAdapter;
            }*/

            inline static void initOutput(GPIOSpeed speed, GPIODriver driver, GPIOState state) {
                halGPIOOptions options =
                    halGPIOOptions(speed) |
                    (driver == GPIODriver::openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
                    halGPIOOptions(state);
                halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, HAL_GPIO_AF_NONE);
            }

            inline static void initialize(halGPIOOptions options) {
                halGPIOInitializePin(halGPIOPort(port_), halGPIOPin(pin_), options, HAL_GPIO_AF_NONE);
            }

            inline static void set() {
                halGPIORegisters *regs = reinterpret_cast<halGPIORegisters*>(_baseAddr);
                regs->LATxSET = 1 << _pinNumber;
            }

            inline static void clear() {
                halGPIORegisters *regs = reinterpret_cast<halGPIORegisters*>(_baseAddr);
                regs->LATxCLR = 1 << _pinNumber;
            }

            inline static void toggle() {
                halGPIORegisters *regs = reinterpret_cast<halGPIORegisters*>(_baseAddr);
                regs->LATxINV = 1 << _pinNumber;
            }

            inline static bool read() {
                halGPIORegisters *regs = reinterpret_cast<halGPIORegisters*>(_baseAddr);
                return (regs->PORTx & (1 << _pinNumber)) != 0;
            }

            inline static void write(bool value) {
                if (value)
                    set();
                else
                    clear();
            }

			inline GPIOPinAdapter& operator = (bool s) {
                write(s);
				return *this;
			}
    };


#ifdef HAL_GPIO_PORT_A
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin0> GPIO_A0;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin1> GPIO_A1;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin2> GPIO_A2;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin3> GPIO_A3;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin4> GPIO_A4;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin5> GPIO_A5;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin6> GPIO_A6;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin7> GPIO_A7;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin8> GPIO_A8;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin9> GPIO_A9;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin10> GPIO_A10;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin11> GPIO_A11;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin12> GPIO_A12;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin13> GPIO_A13;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin14> GPIO_A14;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin15> GPIO_A15;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin0> GPIO_B0;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin1> GPIO_B1;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin2> GPIO_B2;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin3> GPIO_B3;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin4> GPIO_B4;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin5> GPIO_B5;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin6> GPIO_B6;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin7> GPIO_B7;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin8> GPIO_B8;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin9> GPIO_B9;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin10> GPIO_B10;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin11> GPIO_B11;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin12> GPIO_B12;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin13> GPIO_B13;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin14> GPIO_B14;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin15> GPIO_B15;
#endif

#ifdef HAL_GPIO_PORT_C
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin0> GPIO_C0;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin1> GPIO_C1;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin2> GPIO_C2;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin3> GPIO_C3;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin4> GPIO_C4;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin5> GPIO_C5;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin6> GPIO_C6;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin7> GPIO_C7;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin8> GPIO_C8;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin9> GPIO_C9;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin10> GPIO_C10;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin11> GPIO_C11;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin12> GPIO_C12;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin13> GPIO_C13;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin14> GPIO_C14;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin15> GPIO_C15;
#endif

#ifdef HAL_GPIO_PORT_D
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin0> GPIO_D0;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin1> GPIO_D1;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin2> GPIO_D2;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin3> GPIO_D3;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin4> GPIO_D4;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin5> GPIO_D5;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin6> GPIO_D6;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin7> GPIO_D7;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin8> GPIO_D8;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin9> GPIO_D9;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin10> GPIO_D10;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin11> GPIO_D11;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin12> GPIO_D12;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin13> GPIO_D13;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin14> GPIO_D14;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin15> GPIO_D15;
#endif

#ifdef HAL_GPIO_PORT_E
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin0> GPIO_E0;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin1> GPIO_E1;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin2> GPIO_E2;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin3> GPIO_E3;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin4> GPIO_E4;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin5> GPIO_E5;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin6> GPIO_E6;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin7> GPIO_E7;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin8> GPIO_E8;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin9> GPIO_E9;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin10> GPIO_E10;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin11> GPIO_E11;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin12> GPIO_E12;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin13> GPIO_E13;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin14> GPIO_E14;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin15> GPIO_E15;
#endif

#ifdef HAL_GPIO_PORT_F
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin0> GPIO_F0;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin1> GPIO_F1;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin2> GPIO_F2;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin3> GPIO_F3;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin4> GPIO_F4;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin5> GPIO_F5;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin6> GPIO_F6;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin7> GPIO_F7;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin8> GPIO_F8;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin9> GPIO_F9;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin10> GPIO_F10;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin11> GPIO_F11;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin12> GPIO_F12;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin13> GPIO_F13;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin14> GPIO_F14;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin15> GPIO_F15;
#endif

#ifdef HAL_GPIO_PORT_G
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin0> GPIO_G0;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin1> GPIO_G1;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin2> GPIO_G2;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin3> GPIO_G3;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin4> GPIO_G4;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin5> GPIO_G5;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin6> GPIO_G6;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin7> GPIO_G7;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin8> GPIO_G8;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin9> GPIO_G9;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin10> GPIO_G10;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin11> GPIO_G11;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin12> GPIO_G12;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin13> GPIO_G13;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin14> GPIO_G14;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin15> GPIO_G15;
#endif


    // PORT A ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin0> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 0;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin1> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 1;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin2> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 2;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin3> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 3;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin4> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 4;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin5> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 5;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin6> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 6;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin7> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 7;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin8> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 8;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin9> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 9;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin10> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 10;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin11> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 11;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin12> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 12;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin13> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 13;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin14> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 14;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin15> {
		constexpr static const uint32_t baseAddr = _PORTA_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 15;
	};

    // PORT B ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin0> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 0;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin1> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 1;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin2> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 2;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin3> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 3;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin4> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 4;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin5> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 5;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin6> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 6;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin7> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 7;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin8> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 8;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin9> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 9;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin10> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 10;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin11> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 11;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin12> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 12;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin13> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 13;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin14> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 14;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin15> {
		constexpr static const uint32_t baseAddr = _PORTB_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 15;
	};

    // PORT D ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin0> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 0;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin1> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 1;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin2> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 2;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin3> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 3;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin4> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 4;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin5> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 5;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin6> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 6;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin7> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 7;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin8> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 8;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin9> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 9;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin10> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 10;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin11> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 11;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin12> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 12;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin13> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 13;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin14> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 14;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin15> {
		constexpr static const uint32_t baseAddr = _PORTD_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 15;
	};

    // PORT F ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin0> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 0;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin1> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 1;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin2> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 2;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin3> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 3;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin4> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 4;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin5> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 5;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin6> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 6;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin7> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 7;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin8> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 8;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin9> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 9;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin10> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 10;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin11> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 11;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin12> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 12;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin13> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 13;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin14> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 14;
	};
	template <>
	struct GPIOPinInfo<GPIOPort::portF, GPIOPin::pin15> {
		constexpr static const uint32_t baseAddr = _PORTF_BASE_ADDRESS - 0x10;
		constexpr static const uint32_t pinNumber = 15;
	};
}


#endif // __PIC32_htlGPIO__
