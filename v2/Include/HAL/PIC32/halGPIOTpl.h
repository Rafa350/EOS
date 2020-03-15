#ifndef __PIC32_halGPIOTpl__
#define __PIC32_halGPIOTpl__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"


namespace eos {
    
    typedef struct {
        volatile uint32_t TRIS;
        volatile uint32_t TRISCLR;
        volatile uint32_t TRISSET;
        volatile uint32_t TRISINV;
        volatile uint32_t PORT;
        volatile uint32_t PORTCLR;
        volatile uint32_t PORTSET;
        volatile uint32_t PORTINV;
        volatile uint32_t LAT;
        volatile uint32_t LATCLR;
        volatile uint32_t LATSET;
        volatile uint32_t LATINV;
        volatile uint32_t ODC;
        volatile uint32_t ODCCLR;
        volatile uint32_t ODCSET;
        volatile uint32_t ODCINV;
    } GPIO_TypeDef;

    /*
	template <uint32_t base>
    class GPIOPortAdapter {           
        private:        
            constexpr static GPIO_TypeDef *addr = reinterpret_cast<GPIO_TypeDef*>(base);
    	public:
    		static void initialize(uint32_t mask, GPIOOptions options) {
                               
                if (((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_PP) ||
                    ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)) {

                    // Selecciona el valor inicial del port
                    //
                    switch (options & HAL_GPIO_INIT_MASK) {
                        case HAL_GPIO_INIT_SET:
                            addr->LATSET = mask;
                            break;

                        case HAL_GPIO_INIT_CLR:
                            addr->LATCLR = mask;
                            break;
                    }

                    // El configura com sortida
                    //
                    addr->TRISCLR = mask; 

                    // Configura com OPEN-DRAIN o PUSH-PULL
                    //
                    if ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)
                        addr->ODCSET = mask;
                    else
                        addr->ODCCLR = mask;        
                }  

                else if ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_INPUT) {

                    // El configura com entrada
                    //
                    addr->TRISSET = mask;
                }
    		}

    		inline static void set(uint32_t mask) {
    			addr->LATSET = mask;
    		}

    		inline static void clear(uint32_t mask) {
    			addr->LATCLR = mask;
    		}

    		inline static void toggle(uint32_t mask) {
    			addr->LATINV = mask;
    		}
            
            inline static void write(uint32_t value) {
    			addr->PORT = value;
            }

    		inline static uint32_t read() {
    			return addr->PORT;
    		}
    };
    */
    
    template <GPIOPort port, GPIOPin pin>
    class GPIOPinAdapter {
        private:
            inline static GPIO_TypeDef *getAddr() {           
                return nullptr;
            }
            
            inline static uint32_t getMask() {
                return 1ul << pin;
            }
            
        public:
            inline static void initialize(GPIOOptions options) {
                halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
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
            
            inline static void write(bool value) {               
                if (value)
                    halGPIOSetPin(port, pin);
                else
                    halGPIOClearPin(port, pin);
            }
    };
    
    //typedef GPIOPortAdapter<&TRISA> PA;
    //typedef GPIOPortAdapter<&TRISB> PB;
    //typedef GPIOPortAdapter<&TRISC> PC;
    //typedef GPIOPortAdapter<(uint32_t)&TRISD> PD;
    //typedef GPIOPortAdapter<&TRISE> PE;
    //typedef GPIOPortAdapter<&TRISF> PF;
    //typedef GPIOPortAdapter<&TRISG> PG;
    
#ifdef HAL_GPIO_PORT_A    
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_0> PA0;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_1> PA1;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_2> PA2;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_3> PA3;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_4> PA4;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_5> PA5;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_6> PA6;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_7> PA7;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_8> PA8;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_9> PA9;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_10> PA10;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_11> PA11;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_12> PA12;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_13> PA13;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_14> PA14;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_15> PA15;
#endif
    
#ifdef HAL_GPIO_PORT_B    
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_0> PB0;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_1> PB1;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_2> PB2;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_3> PB3;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_4> PB4;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_5> PB5;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_6> PB6;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_7> PB7;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_8> PB8;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_9> PB9;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_10> PB10;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_11> PB11;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_12> PB12;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_13> PB13;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_14> PB14;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_15> PB15;
#endif    
}


#endif // __PIC32_halGPIOTpl__
