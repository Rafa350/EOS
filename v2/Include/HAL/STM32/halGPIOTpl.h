#ifndef __STM32_halGPIOTpl__
#define __STM32_halGPIOTpl__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/STM32/halGPIO.h"


namespace eos {

	enum class GPIOPort: halGPIOPort {
		portA = HAL_GPIO_PORT_A,
		portB = HAL_GPIO_PORT_B,
		portC = HAL_GPIO_PORT_C,
		portD = HAL_GPIO_PORT_D,
		portE = HAL_GPIO_PORT_E,
		portF = HAL_GPIO_PORT_F,
		portG = HAL_GPIO_PORT_G,
		portH = HAL_GPIO_PORT_H,
		portI = HAL_GPIO_PORT_I,
		portJ = HAL_GPIO_PORT_J,
		portK = HAL_GPIO_PORT_K
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

	template <GPIOPort port, GPIOPin pin>
	struct GPIOPinInfo {
		enum class GPIOAlt: halGPIOAlt {
		};
	};

	enum class GPIODriver {
		pushPull,
		openDrain
	};

	enum class GPIOSpeed: halGPIOOptions {
		low    = HAL_GPIO_SPEED_LOW,
		medium = HAL_GPIO_SPEED_MEDIUM,
		high   = HAL_GPIO_SPEED_HIGH,
		fast   = HAL_GPIO_SPEED_FAST
	};

	enum class GPIOPull: halGPIOOptions {
		none = HAL_GPIO_PULL_NONE,
		up   = HAL_GPIO_PULL_UP,
		down = HAL_GPIO_PULL_DOWN
	};

	enum class GPIOState: halGPIOOptions {
		noChange = HAL_GPIO_INIT_NOCHANGE,
		set = HAL_GPIO_INIT_SET,
		clr = HAL_GPIO_INIT_CLR
	};

	template <GPIOPort port, GPIOPin pin>
	class GPIOPinAdapter {
		public:
			using GPIOAlt = typename GPIOPinInfo<port, pin>::GPIOAlt;

		public:
			inline static void initInput(GPIOSpeed speed, GPIOPull pull) {
				halGPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					halGPIOOptions(speed) |
					halGPIOOptions(pull);
				halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initOutput(GPIOSpeed speed, GPIODriver driver, GPIOState state) {
				halGPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					halGPIOOptions(speed) |
					halGPIOOptions(state) |
					(driver == GPIODriver::pushPull ? HAL_GPIO_MODE_OUTPUT_PP : HAL_GPIO_MODE_OUTPUT_OD);
				halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initAlt(GPIOSpeed speed, GPIODriver driver, GPIOAlt alt) {
				halGPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					halGPIOOptions(speed) |
					(driver == GPIODriver::pushPull ? HAL_GPIO_MODE_ALT_PP : HAL_GPIO_MODE_ALT_OD);
				halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, halGPIOAlt(alt));
			}

			inline static void initialize(halGPIOOptions options) {
				halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initialize(halGPIOOptions options, halGPIOAlt alt) {
				halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, alt);
			}

			inline static void set() {
				halGPIOSetPin(halGPIOPort(port), halGPIOPin(pin));
			}

			inline static void clear() {
				halGPIOClearPin(halGPIOPort(port), halGPIOPin(pin));
			}

			inline static void toggle() {
				halGPIOTogglePin(halGPIOPort(port), halGPIOPin(pin));
			}

			inline static bool read() {
				return halGPIOReadPin(halGPIOPort(port), halGPIOPin(pin));
			}

			inline static void write(bool b) {
				halGPIOWritePin(halGPIOPort(port), halGPIOPin(pin), b);
			}

			inline static GPIOPort getPort() {
				return port;
			}

			inline static GPIOPin getPin() {
				return pin;
			}

			inline GPIOPinAdapter& operator = (bool b) {
				halGPIOWritePin(halGPIOPort(port), halGPIOPin(pin), b);
				return *this;
			}
	};


#ifdef HAL_GPIO_PORT_A
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin0> PIN_A0;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin1> PIN_A1;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin2> PIN_A2;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin3> PIN_A3;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin4> PIN_A4;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin5> PIN_A5;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin6> PIN_A6;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin7> PIN_A7;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin8> PIN_A8;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin9> PIN_A9;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin10> PIN_A10;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin11> PIN_A11;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin12> PIN_A12;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin13> PIN_A13;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin14> PIN_A14;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin15> PIN_A15;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin0> PIN_B0;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin1> PIN_B1;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin2> PIN_B2;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin3> PIN_B3;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin4> PIN_B4;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin5> PIN_B5;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin6> PIN_B6;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin7> PIN_B7;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin8> PIN_B8;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin9> PIN_B9;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin10> PIN_B10;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin11> PIN_B11;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin12> PIN_B12;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin13> PIN_B13;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin14> PIN_B14;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin15> PIN_B15;
#endif

#ifdef HAL_GPIO_PORT_C
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin0> PIN_C0;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin1> PIN_C1;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin2> PIN_C2;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin3> PIN_C3;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin4> PIN_C4;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin5> PIN_C5;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin6> PIN_C6;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin7> PIN_C7;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin8> PIN_C8;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin9> PIN_C9;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin10> PIN_C10;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin11> PIN_C11;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin12> PIN_C12;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin13> PIN_C13;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin14> PIN_C14;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin15> PIN_C15;
#endif

#ifdef HAL_GPIO_PORT_D
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin0> PIN_D0;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin1> PIN_D1;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin2> PIN_D2;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin3> PIN_D3;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin4> PIN_D4;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin5> PIN_D5;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin6> PIN_D6;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin7> PIN_D7;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin8> PIN_D8;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin9> PIN_D9;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin10> PIN_D10;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin11> PIN_D11;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin12> PIN_D12;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin13> PIN_D13;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin14> PIN_D14;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin15> PIN_D15;
#endif

#ifdef HAL_GPIO_PORT_E
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin0> PIN_E0;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin1> PIN_E1;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin2> PIN_E2;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin3> PIN_E3;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin4> PIN_E4;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin5> PIN_E5;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin6> PIN_E6;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin7> PIN_E7;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin8> PIN_E8;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin9> PIN_E9;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin10> PIN_E10;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin11> PIN_E11;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin12> PIN_E12;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin13> PIN_E13;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin14> PIN_E14;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin15> PIN_E15;
#endif


#ifdef EOS_STM32F7

	// PORT A ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			tim2_CH1 = HAL_GPIO_AF_1,
			tim2_ETR = HAL_GPIO_AF_1,
			tim5_CH1 = HAL_GPIO_AF_2,
			tim8_ETR = HAL_GPIO_AF_3,
			usart2_CTS = HAL_GPIO_AF_7,
			uart4_TX = HAL_GPIO_AF_8,
		};
		constexpr static const GPIOPort port = GPIOPort::portA;
		constexpr static const GPIOPin pin = GPIOPin::pin0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			usart2_RTS = HAL_GPIO_AF_7,
			uart4_RX = HAL_GPIO_AF_8
		};
		constexpr static const GPIOPort port = GPIOPort::portA;
		constexpr static const GPIOPin pin = GPIOPin::pin1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			i2s1_CL = HAL_GPIO_AF_5,
			spi1_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portA;
		constexpr static const GPIOPin pin = GPIOPin::pin5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			spi1_MISO = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portA;
		constexpr static const GPIOPin pin = GPIOPin::pin6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portA, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			i2s1_SD = HAL_GPIO_AF_5,
			spi1_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portA;
		constexpr static const GPIOPin pin = GPIOPin::pin7;
	};


	// PORT B ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			i2c1_SCL = HAL_GPIO_AF_4,
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portB;
		constexpr static const GPIOPin pin = GPIOPin::pin8;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			i2c1_SDA = HAL_GPIO_AF_4,
			ltdc_B7 = HAL_GPIO_AF_14,
			spi2_NSS = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portB;
		constexpr static const GPIOPin pin = GPIOPin::pin9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			i2c2_SCL = HAL_GPIO_AF_4,
			ltdc_G4 = HAL_GPIO_AF_14,
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portB;
		constexpr static const GPIOPin pin = GPIOPin::pin10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portB, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			spi2_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portB;
		constexpr static const GPIOPin pin = GPIOPin::pin15;
	};


	// PORT C ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14,
			uart6_TX = HAL_GPIO_AF_8
		};
		constexpr static const GPIOPort port = GPIOPort::portC;
		constexpr static const GPIOPin pin = GPIOPin::pin6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14,
			uart6_RX = HAL_GPIO_AF_8
		};
		constexpr static const GPIOPort port = GPIOPort::portC;
		constexpr static const GPIOPin pin = GPIOPin::pin7;
	};


	// PORT D ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			spi3_SCK = HAL_GPIO_AF_5,
			i2s3_SD = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portD;
		constexpr static const GPIOPin pin = GPIOPin::pin6;
	};


	// PORT E ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portE, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B0 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portE;
		constexpr static const GPIOPin pin = GPIOPin::pin4;
	};


	// PORT G ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portG, GPIOPin::pin12> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14,
			ltdc_B4 = HAL_GPIO_AF_9,
			spi6_MISO = HAL_GPIO_AF_5,
			usart6_RTS = HAL_GPIO_AF_8
		};
		constexpr static const GPIOPort port = GPIOPort::portG;
		constexpr static const GPIOPin pin = GPIOPin::pin12;
	};


	// PORT H ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			i2c3_SCL = HAL_GPIO_AF_4
		};
		constexpr static const GPIOPort port = GPIOPort::portH;
		constexpr static const GPIOPin pin = GPIOPin::pin7;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portH, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			i2c3_SDA = HAL_GPIO_AF_4,
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portH;
		constexpr static const GPIOPin pin = GPIOPin::pin8;
	};


	// PORT I ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GPIOPort port = GPIOPort::portI;
		constexpr static const GPIOPin pin = GPIOPin::pin1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_VSYNC = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portI;
		constexpr static const GPIOPin pin = GPIOPin::pin9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portI;
		constexpr static const GPIOPin pin = GPIOPin::pin10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin14> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_DOTCLK = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portI;
		constexpr static const GPIOPin pin = GPIOPin::pin14;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portI, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R0 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portI;
		constexpr static const GPIOPin pin = GPIOPin::pin15;
	};


	// PORT J ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R1 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin2> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R3 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin2;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin3> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R4 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin3;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R5 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R6 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_R7 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G0 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin7;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin8> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G1 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin8;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin9> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G2 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin9;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin10> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G3 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin10;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin11> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G4 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin11;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin13> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin13;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin14> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B2 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin14;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portJ, GPIOPin::pin15> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B3 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portJ;
		constexpr static const GPIOPin pin = GPIOPin::pin15;
	};


	// PORT K ------------------------------------------------------------
	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin0> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G5 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin0;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin1> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin1;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin2> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_G7 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin2;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin4> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B5 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin4;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin5> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin5;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin6> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_B7 = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin6;
	};

	template <>
	struct GPIOPinInfo<GPIOPort::portK, GPIOPin::pin7> {
		enum class GPIOAlt: halGPIOAlt {
			ltdc_DE = HAL_GPIO_AF_14
		};
		constexpr static const GPIOPort port = GPIOPort::portK;
		constexpr static const GPIOPin pin = GPIOPin::pin7;
	};
#endif
}


#endif // __cplusplus

#endif // __STM32_halGPIOTpl__
