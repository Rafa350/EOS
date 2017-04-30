#include "hal/halEINT_PIC32.h"
#include "hal/halGPIO_PIC32.h"
#include <xc.h>


typedef struct {
    GPIOPort port;
    GPIOPin pin;
} EINTPortInfo;


static EINTPortInfo portInfo[] = {
#if defined(__32MX460F265L) || defined(__32MX460F512L)
    { 0xFF, 0 },
    { HAL_GPIO_PORT_C, HAL_GPIO_PIN_13 },  
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_0  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_1  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_2  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_3  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_4  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_5  },
#endif    
};


void halEINTInitialize(
    EINTInput input, 
    EINTOptions options) {

    if (input < sizeof(portInfo) / sizeof(portInfo[0])) {
        EINTPortInfo *pi = &portInfo[input];
        if (pi->port != 0xFF) {
            unsigned mask = 1 << input;
            if ((options & HAL_EINT_ENABLE_MASK) == HAL_EINT_ENABLE_ON) {
                
                // Inicialitza el pin com a entrada digital
                //
                halGPIOInitializePinInput(pi->port, pi->pin);
                
                // Activa interrupcio en el pin
                //
                CNENSET = mask;
                
                // Activa pullup
                //
                switch (options & HAL_EINT_PULLUP_MASK) {
                    case HAL_EINT_PULLUP_OFF:
                       CNPUECLR = mask;
                       break;
                        
                    case HAL_EINT_PULLUP_UP:
                       CNPUESET = mask;
                       break;
                }
            }
            else
                CNENCLR = mask;
        }
    }
}
