#ifndef __STM32_hal2GPIO__
#define	__STM32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


#define HAL_GPIO_PORT_A      eos::GPIOPort::portA
#define HAL_GPIO_PORT_B      eos::GPIOPort::portB
#define HAL_GPIO_PORT_C      eos::GPIOPort::portC
#define HAL_GPIO_PORT_D      eos::GPIOPort::portD
#define HAL_GPIO_PORT_E      eos::GPIOPort::portE
#define HAL_GPIO_PORT_F      eos::GPIOPort::portF
#define HAL_GPIO_PORT_G      eos::GPIOPort::portG
#define HAL_GPIO_PORT_H      eos::GPIOPort::portH
#define HAL_GPIO_PORT_I      eos::GPIOPort::portI
#define HAL_GPIO_PORT_J      eos::GPIOPort::portJ
#define HAL_GPIO_PORT_K      eos::GPIOPort::portK

#define HAL_GPIO_PIN_0       eos::GPIOPin::pin0
#define HAL_GPIO_PIN_1       eos::GPIOPin::pin1
#define HAL_GPIO_PIN_2       eos::GPIOPin::pin2
#define HAL_GPIO_PIN_3       eos::GPIOPin::pin3
#define HAL_GPIO_PIN_4       eos::GPIOPin::pin4
#define HAL_GPIO_PIN_5       eos::GPIOPin::pin5
#define HAL_GPIO_PIN_6       eos::GPIOPin::pin6
#define HAL_GPIO_PIN_7       eos::GPIOPin::pin7
#define HAL_GPIO_PIN_8       eos::GPIOPin::pin8
#define HAL_GPIO_PIN_9       eos::GPIOPin::pin9
#define HAL_GPIO_PIN_10      eos::GPIOPin::pin10
#define HAL_GPIO_PIN_11      eos::GPIOPin::pin11
#define HAL_GPIO_PIN_12      eos::GPIOPin::pin12
#define HAL_GPIO_PIN_13      eos::GPIOPin::pin13
#define HAL_GPIO_PIN_14      eos::GPIOPin::pin14
#define HAL_GPIO_PIN_15      eos::GPIOPin::pin15


namespace eos {

    enum class GPIOPort {
        portA, portB, portC, portD, portE, portF, portG, portH,
        portI, portJ, portK
    };

    enum class GPIOPin {
    	pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
		pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
    };

    enum class GPIOMode {
        input,
        input_PU,
        input_PD,
        output,
        output_OD,
		alt,
		alt_OD,
		analog
    };
    
	enum class GPIOSpeed {
		low,
		medium,
		high,
		fast,
	};

	class GPIO {
		private:
			GPIO_TypeDef *_regs;
            uint32_t _pinNumber;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

            static GPIO_TypeDef* getRegister(GPIOPort port);
            static uint32_t getPinNumber(GPIOPin pin);
            static void enableClock(GPIOPort port);

		public:
			GPIO(GPIOPort port, GPIOPin pin);
            GPIO(const GPIO &gpio);

            void initialize(GPIOMode mode);

            void setSpeed(GPIOSpeed speed);
            void setAlt(uint32_t alt);

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

