#ifndef __PIC32_hal2GPIO__
#define	__PIC32_hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


namespace hal {

	class GPIO {
        private:
            typedef struct __attribute__((packed , aligned(4))) {
                volatile uint32_t TRISx;
                volatile uint32_t TRISxCLR;
                volatile uint32_t TRISxSET;
                volatile uint32_t TRISxINV;
                volatile uint32_t PORTx;
                volatile uint32_t PORTxCLR;
                volatile uint32_t PORTxSET;
                volatile uint32_t PORTxINV;
                volatile uint32_t LATx;
                volatile uint32_t LATxCLR;
                volatile uint32_t LATxSET;
                volatile uint32_t LATxINV;
                volatile uint32_t ODCx;
                volatile uint32_t ODCxCLR;
                volatile uint32_t ODCxSET;
                volatile uint32_t ODCxINV;
            } Registers;

        public:
            enum class Port: uint32_t {
                portA,
                portB,
                portC,
                portD,
                portE,
                portF
            };

            enum class Pin: uint32_t {
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
			Registers *_regs;
            uint32_t _mask;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

            static Registers *getRegisterPtr(Port port);
            static uint32_t getMask(Pin pin);

		public:
			GPIO(Port port, Pin pin);
            GPIO(const GPIO &gpio);

            void initInput(InputMode mode);
            void initOutput(OutputMode mode);

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


#endif // __PIC32_hal2GPIO__

