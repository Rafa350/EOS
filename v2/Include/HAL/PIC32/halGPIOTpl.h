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

	template <uint32_t tris>
    class GPIOPortAdapter {
        private:
            const uint32_t addr = &tris;
    	public:
    		static void initialize(uint32_t mask, GPIOOptions options) {
                
                if (((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_PP) ||
                    ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)) {

                    // Selecciona el valor inicial del port
                    //
                    switch (options & HAL_GPIO_INIT_MASK) {
                        case HAL_GPIO_INIT_SET:
                            ((GPIO_TypeDef*)(&tris))->LATSET = mask;
                            break;

                        case HAL_GPIO_INIT_CLR:
                            ((GPIO_TypeDef*)(&tris))->LATCLR = mask;
                            break;
                    }

                    // El configura com sortida
                    //
                    ((GPIO_TypeDef*)(&tris))->TRISCLR = mask; 

                    // Configura com OPEN-DRAIN o PUSH-PULL
                    //
                    if ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT_OD)
                        ((GPIO_TypeDef*)(&tris))->ODCSET = mask;
                    else
                        ((GPIO_TypeDef*)(&tris))->ODCCLR = mask;        
                }  

                else if ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_INPUT) {

                    // El configura com entrada
                    //
                    ((GPIO_TypeDef*)(&tris))->TRISSET = mask;
                }
    		}

    		inline static void set(uint32_t mask) {
    			((GPIO_TypeDef*)(&tris))->LATSET = mask;
    		}

    		inline static void clear(uint32_t mask) {
    			((GPIO_TypeDef*)(&tris))->LATCLR = mask;
    		}

    		inline static void toggle(uint32_t mask) {
    			((GPIO_TypeDef*)(&tris))->LATINV = mask;
    		}
            
            inline static void write(uint32_t value) {
    			((GPIO_TypeDef*)(&tris))->PORT = value;
            }

    		inline static uint32_t read() {
    			return ((GPIO_TypeDef*)(&tris))->PORT;
    		}
    };
    
    typedef GPIOPortAdapter<TRISA> PortA;
    typedef GPIOPortAdapter<TRISB> PortB;
    typedef GPIOPortAdapter<TRISC> PortC;
    typedef GPIOPortAdapter<TRISD> PortD;
    typedef GPIOPortAdapter<TRISE> PortE;
    typedef GPIOPortAdapter<TRISF> PortF;
    typedef GPIOPortAdapter<TRISG> PortG;

}


#endif // __PIC32_halGPIOTpl__
