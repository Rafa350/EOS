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
            portF = 5
        #endif
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

    enum class CNLine {
        cn0 = 0,
        cn1,
        cn2,
        cn3,
        cn4,
        cn5,
        cn6,
        cn7,
        cn8,
        cn9,
        cn10,
        cn11,
        cn12,
        cn13,
        cn14,
        cn15,
        cn16,
        cn17,
        cn18,
        cn19,
        cn20,
        cn21,
        lineNone = -1
    };

    enum class ANALine {
        an0 = 0,
        an1,
        anNone = -1
    };


    template <GPIOPort port_, GPIOPin pin_>
    struct GPIOPinInfo {
        static const GPIOPort port;
        static const GPIOPin pin;
        static const CNLine cn;
    };

    class GPIO {
        public:
            enum class InpMode {
                input,
            };

            enum class OutMode {
                output,
                output_OD
            };

		private:
			uint32_t _addr;
            uint32_t _mask;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

		public:
			GPIO(GPIOPort port, GPIOPin pin);
            template <typename Info_> GPIO(Info_ info);
            GPIO(const GPIO &gpio);

            void setMode(InpMode mode);
            void setMode(OutMode mode);

			void set() const;
			void clear() const;
			void toggle() const;

			void write(bool s) const;
			bool read() const;

			GPIO & operator = (const GPIO &gpio);
            inline GPIO & operator = (bool s) { write(s); return *this; }
			inline operator bool() const { return read(); }
	};


    template <>
    struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin13> {
        enum class OutMapping {
            none = 0
        };
        static const GPIOPort port =  GPIOPort::portC;
        static const GPIOPin pin = GPIOPin::pin13;
        static const CNLine cn = CNLine::cn1;
    };

    template <>
    struct GPIOPinInfo<GPIOPort::portC, GPIOPin::pin14> {
        enum class OutMapping {
            none = 0
        };
        static const GPIOPort port =  GPIOPort::portC;
        static const GPIOPin pin = GPIOPin::pin14;
        static const CNLine cn = CNLine::cn0;
    };

    template <>
    struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin6> {
        enum class OutMapping {
            none = 0
        };
        static const GPIOPort port =  GPIOPort::portD;
        static const GPIOPin pin = GPIOPin::pin6;
        static const CNLine cn = CNLine::cn5;
    };

    template <>
    struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin7> {
        enum class OutMapping {
            none = 0
        };
        static const GPIOPort port =  GPIOPort::portD;
        static const GPIOPin pin = GPIOPin::pin7;
        static const CNLine cn = CNLine::cn16;
    };

    template <>
    struct GPIOPinInfo<GPIOPort::portD, GPIOPin::pin13> {
        enum class OutMapping {
            none = 0
        };
        static const GPIOPort port =  GPIOPort::portD;
        static const GPIOPin pin = GPIOPin::pin13;
        static const CNLine cn = CNLine::cn19;
    };


    template <typename Info_>
    GPIO::GPIO(Info_ info) :
       GPIO(info.port, info.pin) {
    }

}


#endif // __PIC32_hal2GPIO__

