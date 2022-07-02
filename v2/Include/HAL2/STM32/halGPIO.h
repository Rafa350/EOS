#ifndef __STM32_hal2GPIO__
#define	__STM32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

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
            uint32_t _pnum;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

		public:
			GPIO(Port port, Pin pin);
            GPIO(const GPIO &gpio);

            void setMode(InputMode mode);
            void setMode(OutputMode mode, Alt alt = Alt::altNone);

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

