#ifndef __STM32_hal2GPIO__
#define	__STM32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


#ifdef GPIOA_BASE
#define HAL_GPIO_PORT_A      hal::GPIOPort::portA
#endif
#ifdef GPIOB_BASE
#define HAL_GPIO_PORT_B      hal::GPIOPort::portB
#endif
#ifdef GPIOC_BASE
#define HAL_GPIO_PORT_C      hal::GPIOPort::portC
#endif
#ifdef GPIOD_BASE
#define HAL_GPIO_PORT_D      hal::GPIOPort::portD
#endif
#ifdef GPIOE_BASE
#define HAL_GPIO_PORT_E      hal::GPIOPort::portE
#endif
#ifdef GPIOF_BASE
#define HAL_GPIO_PORT_F      hal::GPIOPort::portF
#endif
#ifdef GPIOG_BASE
#define HAL_GPIO_PORT_G      hal::GPIOPort::portG
#endif
#ifdef GPIOH_BASE
#define HAL_GPIO_PORT_H      hal::GPIOPort::portH
#endif
#ifdef GPIOI_BASE
#define HAL_GPIO_PORT_I      hal::GPIOPort::portI
#endif
#ifdef GPIOJ_BASE
#define HAL_GPIO_PORT_J      hal::GPIOPort::portJ
#endif
#ifdef GPIOK_BASE
#define HAL_GPIO_PORT_K      hal::GPIOPort::portK
#endif


#define HAL_GPIO_PIN_0       hal::GPIOPin::pin0
#define HAL_GPIO_PIN_1       hal::GPIOPin::pin1
#define HAL_GPIO_PIN_2       hal::GPIOPin::pin2
#define HAL_GPIO_PIN_3       hal::GPIOPin::pin3
#define HAL_GPIO_PIN_4       hal::GPIOPin::pin4
#define HAL_GPIO_PIN_5       hal::GPIOPin::pin5
#define HAL_GPIO_PIN_6       hal::GPIOPin::pin6
#define HAL_GPIO_PIN_7       hal::GPIOPin::pin7
#define HAL_GPIO_PIN_8       hal::GPIOPin::pin8
#define HAL_GPIO_PIN_9       hal::GPIOPin::pin9
#define HAL_GPIO_PIN_10      hal::GPIOPin::pin10
#define HAL_GPIO_PIN_11      hal::GPIOPin::pin11
#define HAL_GPIO_PIN_12      hal::GPIOPin::pin12
#define HAL_GPIO_PIN_13      hal::GPIOPin::pin13
#define HAL_GPIO_PIN_14      hal::GPIOPin::pin14
#define HAL_GPIO_PIN_15      hal::GPIOPin::pin15


namespace hal {

	enum class GPIOPort {
		portA,
		portB,
		portC,
		portD,
		portE,
		portF,
		portG,
		portH,
		portI,
		portJ,
		portK
	};

	enum class GPIOPin {
		pin0 = 0,
		pin1,
		pin2,
		pin3,
		pin4,
		pin5,
		pin6,
		pin7,
		pin8,
		pin9,
		pin10,
		pin11,
		pin12,
		pin13,
		pin14,
		pin15,
		pinNone = -1
	};

	class GPIO {
		public:
			enum class InpMode {
				input,
				input_PU,
				input_PD,
				analog
			};

			enum class OutMode {
				output,
				output_OD,
				output_OD_PU
			};

			enum class Alt {
				alt0, alt1, alt2, alt3, alt4, alt5, alt6, alt7,
				alt8, alt9, alt10, alt11, alt12, alt13, alt14, alt15,
				altNone
			};

			enum class Speed {
				low,
				medium,
				high,
				fast
			};

		private:
			uint32_t _base;
            unsigned _pnum;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

		public:
			GPIO(GPIOPort port, GPIOPin pin);
            GPIO(const GPIO &gpio);

            void setMode(InpMode mode);
            void setMode(OutMode mode, Alt alt = Alt::altNone);

            void setSpeed(Speed speed);

			void set() const;
			void clear() const;
			void toggle() const;

			void write(bool s) const;
			bool read() const;

			GPIO & operator = (const GPIO &gpio);

			inline GPIO & operator = (bool s) { write(s); return *this; }
            inline operator bool() const { return read(); }
	};
}


#endif // __STM32_hal2GPIO__

