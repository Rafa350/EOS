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

	template <uint32_t base>
    class GPIOPortAdapter {
        private:
            const GPIO_TypeDef *addr = (GPIO_TypeDef*) &base;
            
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
            
            inline static operator = (uint32_t value) {
                
            }
    };
    
    template <uint32_t base, uint8_t pin>
    class GPIOPinAdapter {
        private:
            const GPIO_TypeDef *addr = (GPIO_TypeDef*) &base;
              
        public:
            inline static void set() {
    			addr->LATSET = 1 << pin;                
            }

            inline static void clear() {
    			addr->LATCLR = 1 << pin;                
            }

            inline static void toggle() {
    			addr->LATINV = 1 << pin;                
            }
    };
    
    typedef GPIOPortAdapter<TRISA> PA;
    typedef GPIOPortAdapter<TRISB> PB;
    typedef GPIOPortAdapter<TRISC> PC;
    typedef GPIOPortAdapter<TRISD> PD;
    typedef GPIOPortAdapter<TRISE> PE;
    typedef GPIOPortAdapter<TRISF> PF;
    typedef GPIOPortAdapter<TRISG> PG;
    
    typedef GPIOPinAdapter<TRISA, 0> PA0;
    typedef GPIOPinAdapter<TRISA, 1> PA1;
    typedef GPIOPinAdapter<TRISA, 2> PA2;
    typedef GPIOPinAdapter<TRISA, 3> PA3;
    typedef GPIOPinAdapter<TRISA, 4> PA4;
    typedef GPIOPinAdapter<TRISA, 5> PA5;
    typedef GPIOPinAdapter<TRISA, 6> PA6;
    typedef GPIOPinAdapter<TRISA, 7> PA7;
    typedef GPIOPinAdapter<TRISA, 8> PA8;
    typedef GPIOPinAdapter<TRISA, 9> PA9;
    typedef GPIOPinAdapter<TRISA, 10> PA10;
    typedef GPIOPinAdapter<TRISA, 11> PA11;
    typedef GPIOPinAdapter<TRISA, 12> PA12;
    typedef GPIOPinAdapter<TRISA, 13> PA13;
    typedef GPIOPinAdapter<TRISA, 14> PA14;
    typedef GPIOPinAdapter<TRISA, 15> PA15;

}


#endif // __PIC32_halGPIOTpl__
