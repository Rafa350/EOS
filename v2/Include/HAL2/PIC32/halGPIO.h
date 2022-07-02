#ifndef __PIC32_hal2GPIO__
#define	__PIC32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

	class GPIO {
        public:
            enum class Port {
                portA,
                #ifdef _PORTB
                    portB,
                #endif
                #ifdef _PORTC
                    portC,
                #endif
                #ifdef _PORTD
                    portD,
                #endif
                #ifdef _PORTE
                    portE,
                #endif
                #ifdef _PORTF
                    portF
                #endif
            };

            enum class Pin {
                pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
                pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
            };

            enum class InputMode {
                input,
                input_PU,
                input_PD
            };

            enum class OutputMode {
                output,
                output_OD
            };

		private:
			uint32_t _base;
            uint32_t _mask;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

		public:
			GPIO(Port port, Pin pin);
            GPIO(const GPIO &gpio);

            void setMode(InputMode mode);
            void setMode(OutputMode mode);

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

