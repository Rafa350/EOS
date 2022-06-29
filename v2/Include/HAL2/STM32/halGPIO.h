#ifndef __STM32_hal2GPIO__
#define	__STM32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

    enum class GPIOPort {
        portA, portB, portC, portD, portE, portF, portG, portH,
        portI, portJ, portK
    };

    enum class GPIOPin {
    	pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
		pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
    };

    enum class GPIOInputMode {
        input,
        input_PU,
        input_PD,
		analog
    };

    enum class GPIOOutputMode {
        output,
        output_OD,
		alt,
		alt_OD
    };

	enum class GPIOSpeed {
		low,
		medium,
		high,
		fast
	};

	enum class GPIOAlt {
		alt0, alt1, alt2, alt3, alt4, alt5, alt6, alt7,
		alt8, alt9, alt10, alt11, alt12, alt13, alt14, alt15
	};

	class GPIO {
		public:
			enum class Port {
				portA, portB, portC, portD, portE, portF, portG, portH,
				portI, portJ, portK
			};

			enum class Pin {
				pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
				pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
			};

			enum class InputMode {
				input,
				input_PU,
				input_PD,
				analog
			};

			enum class OutputMode {
				output,
				output_OD,
				alt,
				alt_OD
			};

			enum class Speed {
				low,
				medium,
				high,
				fast
			};

			enum class Alt {
				alt0, alt1, alt2, alt3, alt4, alt5, alt6, alt7,
				alt8, alt9, alt10, alt11, alt12, alt13, alt14, alt15
			};

		private:
			GPIO_TypeDef *_regs;
            uint32_t _pinNumber;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

            static GPIO_TypeDef* getRegister(Port port);
            static uint32_t getPinNumber(Pin pin);
            static void enableClock(Port port);

		public:
			GPIO(Port port, Pin pin);
            GPIO(const GPIO &gpio);

            void initInput(InputMode mode);
            void initOutput(OutputMode mode);

            void setSpeed(Speed speed);
            void setAlt(Alt alt);

			void set() const;
			void clear() const;
			void toggle() const;

			void write(bool s) const;
			bool read() const;

			GPIO & operator = (const GPIO &gpio);
            GPIO & operator = (bool s);
			operator bool() const;
	};
}


#endif // __STM32_hal2GPIO__

