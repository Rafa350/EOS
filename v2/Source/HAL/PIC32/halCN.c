#include "hal/halCN_PIC32.h"
#include "hal/halGPIO_PIC32.h"
#include <xc.h>
#include <sys/attribs.h>
#include <peripheral/ports/plib_ports.h>
#include <peripheral/int//plib_int.h>


typedef struct {
    GPIOPort port;
    GPIOPin pin;
} CNPortInfo;


static CNPortInfo portInfo[] = {
#if defined(__32MX440F128L) || defined(__32MX460F265L) || defined(__32MX460F512L)
    { 0xFF, 0 },
    { HAL_GPIO_PORT_C, HAL_GPIO_PIN_13 },  
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_0  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_1  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_2  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_3  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_4  },
    { HAL_GPIO_PORT_B, HAL_GPIO_PIN_5  },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { HAL_GPIO_PORT_D, HAL_GPIO_PIN_13 },
    { 0xFF, 0 },
    { 0xFF, 0 },
    { 0xFF, 0 },
#endif    
};


static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

extern void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SOFT) isrCNWrapper(void);


void halCNInitialize(
    CNInput input, 
    CNOptions options) {

    if (input < sizeof(portInfo) / sizeof(portInfo[0])) {
        CNPortInfo *pi = &portInfo[input];
        if (pi->port != 0xFF) {
            unsigned mask = 1 << input;
            if ((options & HAL_CN_ENABLE_MASK) == HAL_CN_ENABLE_ON) {
                
                // Inicialitza el pin com a entrada digital
                //
                halGPIOInitializePinInput(pi->port, pi->pin);
                
                // Activa interrupcio en el pin
                //
                CNENSET = mask;
                
                // Activa pullup
                //
                switch (options & HAL_CN_PULLUP_MASK) {
                    case HAL_CN_PULLUP_OFF:
                       CNPUECLR = mask;
                       break;
                        
                    case HAL_CN_PULLUP_UP:
                       CNPUESET = mask;
                       break;
                }
                
                PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
                PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, intPriority);
                PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, intSubPriority);    
                
            }
            else
                CNENCLR = mask;
        }
    }
}


void isrCNHandler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_CHANGE_NOTICE)) {
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    }    
}