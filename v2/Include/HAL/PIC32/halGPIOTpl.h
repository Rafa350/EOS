#ifndef __PIC32_halGPIOTpl__
#define __PIC32_halGPIOTpl__


// EOS includes
//
#include "eos.h"
#include "hal/halGPIO.h"


namespace eos {

	template <uint32_t tris, uint32_t port, uint32_t lat>
    class GPIOPortAdapter {
    	public:
    		inline static void initialize(GPIOOptions options) {
    		}

    		inline static void set(uint32_t mask) {
    			(uint32_t*)(lat + 4) = mask;
    		}

    		inline static void clear(uint32_t mask) {
                (uint32_t*)(lat + 0) = mask;
    		}

    		inline static void toggle(uint32_t mask) {
    			(uint32_t*)(lat + 8) = mask;
    		}
            
            inline static void write(uint32_t value) {
                (uint32_t*)(port) = value;
            }

    		inline static uint32_t read() {
    			return (uint32_t*)(port);
    		}
    };
    
    typedef GPIOPortAdapter<TRISA, PORTA, LATA> PortA;
    typedef GPIOPortAdapter<TRISB, PORTB, LATB> PortB;
    typedef GPIOPortAdapter<TRISC, PORTC, LATC> PortC;
    typedef GPIOPortAdapter<TRISD, PORTD, LATD> PortD;
    typedef GPIOPortAdapter<TRISE, PORTE, LATE> PortE;

}


#endif // __PIC32_halGPIOTpl__
