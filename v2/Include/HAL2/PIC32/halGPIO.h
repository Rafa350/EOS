#ifndef __PIC32_hal2GPIO__
#define	__PIC32_hal2GPIO__


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

    enum class GPIOPort: uint32_t {
        portA, portB, portC, portD, portE, portF
    };

    enum class GPIOPin: uint32_t {
        pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7,
        pin8, pin9, pin10, pin11, pin12, pin13, pin14, pin15
    };

    enum class GPIOMode {
        input,
        input_PU,
        input_PD,
        output,
        output_OD
    };

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

		private:
			Registers *_regs;
            uint32_t _mask;

			GPIO(const GPIO &&) = delete;
			GPIO & operator = (const GPIO &&) = delete;

            static Registers* getRegister(GPIOPort port);
            static uint32_t getMask(GPIOPin pin);

		public:
			GPIO(GPIOPort port, GPIOPin pin);
            GPIO(const GPIO &gpio);

            void initialize(GPIOMode mode);

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

