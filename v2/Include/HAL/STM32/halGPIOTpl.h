#ifndef __STM32_halGPIOTpl__
#define __STM32_halGPIOTpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halGPIO.h"


namespace eos {

	template <GPIOPort port, GPIOPin pin>
	struct GpioFunction {
		enum class Value {
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
		noChange = 0,
		set = HAL_GPIO_INIT_SET,
		clr = HAL_GPIO_INIT_CLR
	};

	template <GPIOPort port, GPIOPin pin>
	class GpioPinAdapter {
		public:
			typedef typename GpioFunction<port, pin>::Value FunctionValue;

		public:
			static const GpioFunction<port, pin> Function;

		public:
			inline static void initInput(GpioSpeed speed, GpioPull pull) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					GPIOOptions(pull);
				halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
			}

			inline static void initOutput(GpioSpeed speed, GpioDriver driver, GpioState state) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					GPIOOptions(state) |
					(driver == GpioDriver::pushPull ? HAL_GPIO_MODE_OUTPUT_PP : HAL_GPIO_MODE_OUTPUT_OD);
				halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
			}

			inline static void initAlt(GpioSpeed speed, GpioDriver driver, FunctionValue fv) {
				GPIOOptions options =
					HAL_GPIO_MODE_INPUT |
					GPIOOptions(speed) |
					(driver == GpioDriver::pushPull ? HAL_GPIO_MODE_ALT_PP : HAL_GPIO_MODE_ALT_OD);
				halGPIOInitializePin(port, pin, options, GPIOAlt(fv));
			}

			inline static void initialize(GPIOOptions options) {
				halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
			}

			inline static void initialize(GPIOOptions options, GPIOAlt alt) {
				halGPIOInitializePin(port, pin, options, alt);
			}

			inline static void set() {
				halGPIOSetPin(port, pin);
			}

			inline static void clear() {
				halGPIOClearPin(port, pin);
			}

			inline static void toggle() {
				halGPIOTogglePin(port, pin);
			}

			inline static bool read() {
				return halGPIOReadPin(port, pin);
			}

			inline static GPIOPort getPort() {
				return port;
			}

			inline static GPIOPin getPin() {
				return port;
			}

			inline GpioPinAdapter& operator = (bool b) {
				halGPIOWritePin(port, pin, b);
				return *this;
			}
	};


	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_0> PA0;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_1> PA1;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_2> PA2;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_3> PA3;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_4> PA4;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_5> PA5;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_6> PA6;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_7> PA7;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_8> PA8;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_9> PA9;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_10> PA10;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_11> PA11;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_12> PA12;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_13> PA13;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_14> PA14;
	typedef GpioPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_15> PA15;


#ifdef EOS_STM32F7

	// PORT A ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_A, HAL_GPIO_PIN_5> {
		enum class Value: GPIOAlt {
			i2s1_CL = HAL_GPIO_AF_5,
			spi1_SCK = HAL_GPIO_AF_5
		};
		constexpr static const Value i2s1_CL = Value::i2s1_CL;
		constexpr static const Value spi1_SCK = Value::spi1_SCK;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_A, HAL_GPIO_PIN_6> {
		enum class Value: GPIOAlt {
			spi1_MISO = HAL_GPIO_AF_5
		};
		constexpr static const Value spi1_MISO = Value::spi1_MISO;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_A, HAL_GPIO_PIN_7> {
		enum class Value: GPIOAlt {
			i2s1_SD = HAL_GPIO_AF_5,
			spi1_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const Value i2s1_SD = Value::i2s1_SD;
		constexpr static const Value spi1_MOSI = Value::spi1_MOSI;
	};


	// PORT B ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_B, HAL_GPIO_PIN_8> {
		enum class Value: GPIOAlt {
			i2c1_SCL = HAL_GPIO_AF_4,
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const Value i2c1_SCL = Value::i2c1_SCL;
		constexpr static const Value ltdc_B6 = Value::ltdc_B6;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_B, HAL_GPIO_PIN_9> {
		enum class Value: GPIOAlt {
			i2c1_SDA = HAL_GPIO_AF_4,
			ltdc_B7 = HAL_GPIO_AF_14,
			spi2_NSS = HAL_GPIO_AF_5
		};
		constexpr static const Value i2c1_SDA = Value::i2c1_SDA;
		constexpr static const Value ltdc_B7 = Value::ltdc_B7;
		constexpr static const Value spi2_NSS = Value::spi2_NSS;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_B, HAL_GPIO_PIN_10> {
		enum class Value: GPIOAlt {
			i2c2_SCL = HAL_GPIO_AF_4,
			ltdc_G4 = HAL_GPIO_AF_14,
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const Value i2c2_SCL = Value::i2c2_SCL;
		constexpr static const Value ltdc_G4 = Value::ltdc_G4;
		constexpr static const Value spi2_SCK = Value::spi2_SCK;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_B, HAL_GPIO_PIN_15> {
		enum class Value: GPIOAlt {
			spi2_MOSI = HAL_GPIO_AF_5
		};
		constexpr static const Value spi2_MOSI = Value::spi2_MOSI;
	};


	// PORT D ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_D, HAL_GPIO_PIN_6> {
		constexpr static const GPIOAlt spi3_SCK = HAL_GPIO_AF_5;
		constexpr static const GPIOAlt i2s3_SD = HAL_GPIO_AF_5;
	};


	// PORT E ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_E, HAL_GPIO_PIN_4> {
		constexpr static const GPIOAlt ltdc_B0 = HAL_GPIO_AF_14;
	};


	// PORT G ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_G, HAL_GPIO_PIN_12> {
		enum class Value {
			ltdc_B1 = HAL_GPIO_AF_14,
			ltdc_B4 = HAL_GPIO_AF_9,
			spi6_MISO = HAL_GPIO_AF_5,
			usart6_RTS = HAL_GPIO_AF_8
		};
		constexpr static const Value ltdc_B4 = Value::ltdc_B4;
		constexpr static const Value ltdc_B1 = Value::ltdc_B1;
		constexpr static const Value spi6_MISO = Value::spi6_MISO;
		constexpr static const Value usart6_RTS = Value::usart6_RTS;
	};


	// PORT I ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_I, HAL_GPIO_PIN_1> {
		enum class Value: GPIOAlt {
			spi2_SCK = HAL_GPIO_AF_5
		};
		constexpr static const Value spi2_SCK = Value::spi2_SCK;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_I, HAL_GPIO_PIN_9> {
		enum class Value: GPIOAlt {
			ltdc_VSYNC = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_VSYNC = Value::ltdc_VSYNC;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_I, HAL_GPIO_PIN_10> {
		enum class Value: GPIOAlt {
			ltdc_HSYNC = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_HSYNC = Value::ltdc_HSYNC;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_I, HAL_GPIO_PIN_14> {
		enum class Value: GPIOAlt {
			ltdc_DOTCLK = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_DOTCLK = Value::ltdc_DOTCLK;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_I, HAL_GPIO_PIN_15> {
		enum class Value: GPIOAlt {
			ltdc_R0 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R0 = Value::ltdc_R0;
	};


	// PORT J ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_0> {
		enum class Value: GPIOAlt {
			ltdc_R1 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R1 = Value::ltdc_R1;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_1> {
		enum class Value: GPIOAlt {
			ltdc_R2 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R2 = Value::ltdc_R2;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_2> {
		enum class Value: GPIOAlt {
			ltdc_R3 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R3 = Value::ltdc_R3;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_3> {
		enum class Value: GPIOAlt {
			ltdc_R4 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R4 = Value::ltdc_R4;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_4> {
		enum class Value: GPIOAlt {
			ltdc_R5 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R5 = Value::ltdc_R5;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_5> {
		enum class Value: GPIOAlt {
			ltdc_R6 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R6 = Value::ltdc_R6;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_6> {
		enum class Value: GPIOAlt {
			ltdc_R7 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_R7 = Value::ltdc_R7;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_7> {
		enum class Value: GPIOAlt {
			ltdc_G0 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G0 = Value::ltdc_G0;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_8> {
		enum class Value: GPIOAlt {
			ltdc_G1 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G1 = Value::ltdc_G1;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_9> {
		enum class Value: GPIOAlt {
			ltdc_G2 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G2 = Value::ltdc_G2;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_10> {
		enum class Value: GPIOAlt {
			ltdc_G3 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G3 = Value::ltdc_G3;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_11> {
		enum class Value: GPIOAlt {
			ltdc_G4 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G4 = Value::ltdc_G4;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_13> {
		enum class Value: GPIOAlt {
			ltdc_B1 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B1 = Value::ltdc_B1;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_14> {
		enum class Value: GPIOAlt {
			ltdc_B2 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B2 = Value::ltdc_B2;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_J, HAL_GPIO_PIN_15> {
		enum class Value: GPIOAlt {
			ltdc_B3 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B3 = Value::ltdc_B3;
	};


	// PORT K ------------------------------------------------------------
	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_0> {
		enum class Value: GPIOAlt {
			ltdc_G5 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G5 = Value::ltdc_G5;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_1> {
		enum class Value: GPIOAlt {
			ltdc_G6 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G6 = Value::ltdc_G6;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_2> {
		enum class Value: GPIOAlt {
			ltdc_G7 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_G7 = Value::ltdc_G7;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_4> {
		enum class Value: GPIOAlt {
			ltdc_R5 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B5 = Value::ltdc_R5;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_5> {
		enum class Value: GPIOAlt {
			ltdc_B6 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B6 = Value::ltdc_B6;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_6> {
		enum class Value: GPIOAlt {
			ltdc_B7 = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_B7 = Value::ltdc_B7;
	};

	template <>
	struct GpioFunction<HAL_GPIO_PORT_K, HAL_GPIO_PIN_7> {
		enum class Value: GPIOAlt {
			ltdc_DE = HAL_GPIO_AF_14
		};
		constexpr static const Value ltdc_DE = Value::ltdc_DE;
	};
#endif
}


#endif // __STM32_halGPIOTpl__
