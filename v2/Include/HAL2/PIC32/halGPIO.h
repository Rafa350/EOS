#ifndef __PIC32_hal2GPIO__
#define	__PIC32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


#ifdef _PORTA
#define HAL_GPIO_PORT_A      hal::GPIOPort::portA
#endif
#ifdef _PORTB
#define HAL_GPIO_PORT_B      hal::GPIOPort::portB
#endif
#ifdef _PORTC
#define HAL_GPIO_PORT_C      hal::GPIOPort::portC
#endif
#ifdef _PORTD
#define HAL_GPIO_PORT_D      hal::GPIOPort::portD
#endif
#ifdef _PORTE
#define HAL_GPIO_PORT_E      hal::GPIOPort::portE
#endif
#ifdef _PORTF
#define HAL_GPIO_PORT_F      hal::GPIOPort::portF
#endif
#ifdef _PORTG
#define HAL_GPIO_PORT_G      hal::GPIOPort::portG
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
        #ifdef _PORTA
            portA = 0,
        #endif
        #ifdef _PORTB
            portB = 1,
        #endif
        #ifdef _PORTC
            portC = 2,
        #endif
        #ifdef _PORTD
            portD = 3,
        #endif
        #ifdef _PORTE
            portE = 4,
        #endif
        #ifdef _PORTF
            portF = 5,
        #endif
        #ifdef _PORTG
            portG = 6,
        #endif
        portNone = -1
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

    enum class GPIOPull {
        none,
        up
    };

    enum class GPIODriver {
        pushPull,
        openDrain
    };

    enum class GPIOSpeed {
        fastest,
        fast,
        slow,
        slowest
    };

    class GPIO {
		private:
			uint32_t _addr;
            uint32_t _mask;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

		public:
			GPIO(GPIOPort port, GPIOPin pin);
            GPIO(const GPIO &gpio);

            void initInput(GPIOPull pull = GPIOPull::none);
            void initOutput(GPIODriver driver = GPIODriver::pushPull, GPIOSpeed speed = GPIOSpeed::slow);

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


#endif // __PIC32_hal2GPIO__

