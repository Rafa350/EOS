#ifndef __STM32_halGPIOTpl__
#define __STM32_halGPIOTpl__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/STM32/halGPIO.h"


namespace eos {

	enum class GpioPort: GPIOPort {
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

	enum class GpioPin: GPIOPin {
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

	template <GpioPort port, GpioPin pin>
	struct GpioPinInfo {
		enum class GpioAlt: GPIOAlt {
		};
	};

	enum class GpioDriver {
		pushPull,
		openDrain
	};

	enum class GpioSpeed: GPIOOptions {
		low    = HAL_GPIO_SPEED_LOW,
		medium = HAL_GPIO_SPEED_MEDIUM,
		high   = HAL_GPIO_SPEED_HIGH,
		fast   = HAL_GPIO_SPEED_FAST
	};

	enum class GpioPull: GPIOOptions {
		none = HAL_GPIO_PULL_NONE,
		up   = HAL_GPIO_PULL_UP,
		down = HAL_GPIO_PULL_DOWN
	};

	enum class GpioState: GPIOOptions {
		noChange = HAL_GPIO_INIT_NOCHANGE,
		set = HAL_GPIO_INIT_SET,
		clr = HAL_GPIO_INIT_CLR
	};

	template <GpioPort port, GpioPin pin>
	class GpioPinAdapter {
		public:
			using GpioAlt = typename GpioPinInfo<port, pin>::GpioAlt;

		public:
			inline static void initInput(GpioSpeed speed, GpioPull pull) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					GPIOOptions(pull);
				halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initOutput(GpioSpeed speed, GpioDriver driver, GpioState state) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					GPIOOptions(state) |
					(driver == GpioDriver::pushPull ? HAL_GPIO_MODE_OUTPUT_PP : HAL_GPIO_MODE_OUTPUT_OD);
				halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initAlt(GpioSpeed speed, GpioDriver driver, GpioAlt alt) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					(driver == GpioDriver::pushPull ? HAL_GPIO_MODE_ALT_PP : HAL_GPIO_MODE_ALT_OD);
				halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, GPIOAlt(alt));
			}

			inline static void initialize(GPIOOptions options) {
				halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, HAL_GPIO_AF_NONE);
			}

			inline static void initialize(GPIOOptions options, GPIOAlt alt) {
				halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, alt);
			}

			inline static void set() {
				halGPIOSetPin(GPIOPort(port), GPIOPin(pin));
			}

			inline static void clear() {
				halGPIOClearPin(GPIOPort(port), GPIOPin(pin));
			}

			inline static void toggle() {
				halGPIOTogglePin(GPIOPort(port), GPIOPin(pin));
			}

			inline static bool read() {
				return halGPIOReadPin(GPIOPort(port), GPIOPin(pin));
			}

			inline static void write(bool b) {
				halGPIOWritePin(GPIOPort(port), GPIOPin(pin), b);
			}

			inline static GpioPort getPort() {
				return port;
			}

			inline static GpioPin getPin() {
				return pin;
			}

			inline GpioPinAdapter& operator = (bool b) {
				halGPIOWritePin(GPIOPort(port), GPIOPin(pin), b);
				return *this;
			}
	};


#ifdef HAL_GPIO_PORT_A
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin0> PA0;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin1> PA1;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin2> PA2;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin3> PA3;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin4> PA4;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin5> PA5;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin6> PA6;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin7> PA7;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin8> PA8;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin9> PA9;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin10> PA10;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin11> PA11;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin12> PA12;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin13> PA13;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin14> PA14;
	typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin15> PA15;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin0> PB0;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin1> PB1;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin2> PB2;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin3> PB3;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin4> PB4;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin5> PB5;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin6> PB6;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin7> PB7;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin8> PB8;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin9> PB9;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin10> PB10;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin11> PB11;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin12> PB12;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin13> PB13;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin14> PB14;
	typedef GpioPinAdapter<GpioPort::portB, GpioPin::pin15> PB15;
#endif

#ifdef HAL_GPIO_PORT_C
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin0> PC0;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin1> PC1;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin2> PC2;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin3> PC3;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin4> PC4;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin5> PC5;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin6> PC6;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin7> PC7;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin8> PC8;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin9> PC9;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin10> PC10;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin11> PC11;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin12> PC12;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin13> PC13;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin14> PC14;
	typedef GpioPinAdapter<GpioPort::portC, GpioPin::pin15> PC15;
#endif

#ifdef HAL_GPIO_PORT_D
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin0> PD0;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin1> PD1;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin2> PD2;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin3> PD3;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin4> PD4;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin5> PD5;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin6> PD6;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin7> PD7;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin8> PD8;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin9> PD9;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin10> PD10;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin11> PD11;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin12> PD12;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin13> PD13;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin14> PD14;
	typedef GpioPinAdapter<GpioPort::portD, GpioPin::pin15> PD15;
#endif


#ifdef EOS_STM32F7

	// PORT A ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portA, GpioPin::pin0> {
		enum class GpioAlt: GPIOAlt {
			tim2_CH1 = HAL_GPIO_AF_1,
			tim2_ETR = HAL_GPIO_AF_1,
			tim5_CH1 = HAL_GPIO_AF_2,
			tim8_ETR = HAL_GPIO_AF_3,
			usart2_CTS = HAL_GPIO_AF_7,
			uart4_TX = HAL_GPIO_AF_8,
		};
		constexpr static const GpioPort port = GpioPort::portA;
		constexpr static const GpioPin pin = GpioPin::pin0;
	};

	template <>
	struct GpioPinInfo<GpioPort::portA, GpioPin::pin1> {
		enum class GpioAlt: GPIOAlt {
			usart2_RTS = HAL_GPIO_AF_7,
			uart4_RX = HAL_GPIO_AF_8
		};
		constexpr static const GpioPort port = GpioPort::portA;
		constexpr static const GpioPin pin = GpioPin::pin1;
	};

	template <>
	struct GpioPinInfo<GpioPort::portA, GpioPin::pin5> {
		enum class GpioAlt: GPIOAlt {
			i2s1_CL = HAL_GPIO_AF_5,
			spi1_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portA;
		constexpr static const GpioPin pin = GpioPin::pin5;
	};

	template <>
	struct GpioPinInfo<GpioPort::portA, GpioPin::pin6> {
		enum class GpioAlt: GPIOAlt {
			spi1_MISO = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portA;
		constexpr static const GpioPin pin = GpioPin::pin6;
	};

	template <>
	struct GpioPinInfo<GpioPort::portA, GpioPin::pin7> {
		enum class GpioAlt: GPIOAlt {
			i2s1_SD = HAL_GPIO_AF_5,
			spi1_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portA;
		constexpr static const GpioPin pin = GpioPin::pin7;
	};


	// PORT B ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portB, GpioPin::pin8> {
		enum class GpioAlt: GPIOAlt {
			i2c1_SCL = HAL_GPIO_AF_4,
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portB;
		constexpr static const GpioPin pin = GpioPin::pin8;
	};

	template <>
	struct GpioPinInfo<GpioPort::portB, GpioPin::pin9> {
		enum class GpioAlt: GPIOAlt {
			i2c1_SDA = HAL_GPIO_AF_4,
			ltdc_B7 = HAL_GPIO_AF_14,
			spi2_NSS = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portB;
		constexpr static const GpioPin pin = GpioPin::pin9;
	};

	template <>
	struct GpioPinInfo<GpioPort::portB, GpioPin::pin10> {
		enum class GpioAlt: GPIOAlt {
			i2c2_SCL = HAL_GPIO_AF_4,
			ltdc_G4 = HAL_GPIO_AF_14,
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portB;
		constexpr static const GpioPin pin = GpioPin::pin10;
	};

	template <>
	struct GpioPinInfo<GpioPort::portB, GpioPin::pin15> {
		enum class GpioAlt: GPIOAlt {
			spi2_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portB;
		constexpr static const GpioPin pin = GpioPin::pin15;
	};


	// PORT C ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portC, GpioPin::pin6> {
		enum class GpioAlt: GPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14,
			uart6_TX = HAL_CPIO_AF_8
		};
		constexpr static const GpioPort port = GpioPort::portC;
		constexpr static const GpioPin pin = GpioPin::pin6;
	};

	template <>
	struct GpioPinInfo<GpioPort::portC, GpioPin::pin7> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G6 = HAL_LTDC_AF_14,
			uart6_RX = HAL_CPIO_AF_8
		};
		constexpr static const GpioPort port = GpioPort::portC;
		constexpr static const GpioPin pin = GpioPin::pin7;
	};


	// PORT D ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portD, GpioPin::pin6> {
		enum class GpioAlt: GPIOAlt {
			spi3_SCK = HAL_GPIO_AF_5,
			i2s3_SD = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portD;
		constexpr static const GpioPin pin = GpioPin::pin6;
	};


	// PORT E ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portE, GpioPin::pin4> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B0 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portE;
		constexpr static const GpioPin pin = GpioPin::pin4;
	};


	// PORT G ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portG, GpioPin::pin12> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14,
			ltdc_B4 = HAL_GPIO_AF_9,
			spi6_MISO = HAL_GPIO_AF_5,
			usart6_RTS = HAL_GPIO_AF_8
		};
		constexpr static const GpioPort port = GpioPort::portG;
		constexpr static const GpioPin pin = GpioPin::pin12;
	};


	// PORT H ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portH, GpioPin::pin7> {
		enum class GpioAlt: GPIOAlt {
			i2c3_SCL = HAL_GPIO_AF_4
		};
		constexpr static const GpioPort port = GpioPort::portH;
		constexpr static const GpioPin pin = GpioPin::pin7;
	};

	template <>
	struct GpioPinInfo<GpioPort::portH, GpioPin::pin8> {
		enum class GpioAlt: GPIOAlt {
			i2c3_SDA = HAL_GPIO_AF_4,
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portH;
		constexpr static const GpioPin pin = GpioPin::pin8;
	};


	// PORT I ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portI, GpioPin::pin1> {
		enum class GpioAlt: GPIOAlt {
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const GpioPort port = GpioPort::portI;
		constexpr static const GpioPin pin = GpioPin::pin1;
	};

	template <>
	struct GpioPinInfo<GpioPort::portI, GpioPin::pin9> {
		enum class GpioAlt: GPIOAlt {
			ltdc_VSYNC = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portI;
		constexpr static const GpioPin pin = GpioPin::pin9;
	};

	template <>
	struct GpioPinInfo<GpioPort::portI, GpioPin::pin10> {
		enum class GpioAlt: GPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portI;
		constexpr static const GpioPin pin = GpioPin::pin10;
	};

	template <>
	struct GpioPinInfo<GpioPort::portI, GpioPin::pin14> {
		enum class GpioAlt: GPIOAlt {
			ltdc_DOTCLK = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portI;
		constexpr static const GpioPin pin = GpioPin::pin14;
	};

	template <>
	struct GpioPinInfo<GpioPort::portI, GpioPin::pin15> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R0 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portI;
		constexpr static const GpioPin pin = GpioPin::pin15;
	};


	// PORT J ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin0> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R1 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin0;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin1> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin1;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin2> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R3 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin2;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin3> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R4 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin3;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin4> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R5 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin4;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin5> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R6 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin5;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin6> {
		enum class GpioAlt: GPIOAlt {
			ltdc_R7 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin6;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin7> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G0 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin7;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin8> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G1 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin8;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin9> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G2 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin9;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin10> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G3 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin10;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin11> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G4 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin11;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin13> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin13;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin14> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B2 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin14;
	};

	template <>
	struct GpioPinInfo<GpioPort::portJ, GpioPin::pin15> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B3 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portJ;
		constexpr static const GpioPin pin = GpioPin::pin15;
	};


	// PORT K ------------------------------------------------------------
	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin0> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G5 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin0;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin1> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin1;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin2> {
		enum class GpioAlt: GPIOAlt {
			ltdc_G7 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin2;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin4> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B5 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin4;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin5> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin5;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin6> {
		enum class GpioAlt: GPIOAlt {
			ltdc_B7 = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin6;
	};

	template <>
	struct GpioPinInfo<GpioPort::portK, GpioPin::pin7> {
		enum class GpioAlt: GPIOAlt {
			ltdc_DE = HAL_GPIO_AF_14
		};
		constexpr static const GpioPort port = GpioPort::portK;
		constexpr static const GpioPin pin = GpioPin::pin7;
	};
#endif
}


#endif // __cplusplus

#endif // __STM32_halGPIOTpl__
