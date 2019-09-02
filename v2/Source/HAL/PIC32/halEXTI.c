#include "hal/PIC32/halEXTI.h"
#include "hal/PIC32/halGPIO.h"
#include "hal/PIC32/halADC.h"
#include "hal/PIC32/halINT.h"

#include <xc.h>
#include <sys/attribs.h>

#include <peripheral/int//plib_int.h>


typedef struct {
    ADCPin adcPin;
    uint8_t gpioPort;
    uint8_t gpioPin;
} CNPortInfo;

typedef struct {
    CNInterruptCallback callback;
    void *param;
    bool state;
} CNData;


#if defined(__32MX440F128L) || defined(__32MX460F265L) || defined(__32MX460F512L)

#define MAX_CNINPUTS    22

static const CNPortInfo portInfo[MAX_CNINPUTS] = {
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_C, HAL_GPIO_PIN_14 },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_C, HAL_GPIO_PIN_13 },  
    { HAL_ADC_PIN_0,    HAL_GPIO_PORT_B, HAL_GPIO_PIN_0  },
    { HAL_ADC_PIN_1,    HAL_GPIO_PORT_B, HAL_GPIO_PIN_1  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_B, HAL_GPIO_PIN_2  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_B, HAL_GPIO_PIN_3  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_B, HAL_GPIO_PIN_4  },
    { HAL_ADC_PIN_5,    HAL_GPIO_PORT_B, HAL_GPIO_PIN_5  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_G, HAL_GPIO_PIN_6  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_G, HAL_GPIO_PIN_7  },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_G, HAL_GPIO_PIN_8  },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, HAL_GPIO_PORT_D, HAL_GPIO_PIN_13 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 },
    { HAL_ADC_PIN_NONE, 0xFF, 0 }
};

#endif    


static CNData info[MAX_CNINPUTS];
static uint32_t portA;
static uint32_t portB;
static uint32_t portC;
static uint32_t portD;
static uint32_t portE;
static uint32_t portF;
static uint32_t portG;
static const INT_PRIORITY_LEVEL intPriority = INT_PRIORITY_LEVEL2;
static const INT_SUBPRIORITY_LEVEL intSubPriority = INT_SUBPRIORITY_LEVEL0;

extern void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SOFT) isrCNWrapper(void);


/// ----------------------------------------------------------------------
/// \brief Inicialitza una entrada CN.
/// \param pin: Identificador de l'entrada.
/// \param options: Opcions.
/// \param callback: Funcio callback.
/// \param param. Parametre de la funcio callback.
///
void halCNInitialize(
    CNPin pin, 
    CNOptions options,
    CNInterruptCallback callback,
    void *param) {

    if (pin < sizeof(portInfo) / sizeof(portInfo[0])) {
        
        const CNPortInfo *pi = &portInfo[pin];
        
        if ((options & HAL_CN_ENABLE_MASK) == HAL_CN_ENABLE_ON) {
                
            // Activa interrupcio en el pin
            //
            halGPIOInitializePinInput(pi->gpioPort, pi->gpioPin);
            if (pi->adcPin != HAL_ADC_PIN_NONE)
                AD1PCFGSET = 1 << pi->adcPin;
            
            CNENSET = 1 << pin;

            // Activa pullup
            //
            switch (options & HAL_CN_PULLUP_MASK) {
                case HAL_CN_PULLUP_OFF:
                   CNPUECLR = 1 << pin;
                   break;

                case HAL_CN_PULLUP_UP:
                   CNPUESET = 1 << pin;
                   break;
            }

            info[pin].state = halGPIOReadPin(pi->gpioPort, pi->gpioPin);
            info[pin].callback = callback;
            info[pin].param = param;
        }
        else
            CNENCLR = 1 << pin;
    }
}


void halCNEnable(void) {
    
    halINTDisableInterrupts();

    // Selecciona la prioritat de la interrupcio
    //
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, intPriority);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, intSubPriority);    

    // Activa la interrupcio CN
    //
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    
    // Llegeix l'estat dels ports
    //
    portB = halGPIOReadPort(HAL_GPIO_PORT_B);
    portG = halGPIOReadPort(HAL_GPIO_PORT_C);
    portD = halGPIOReadPort(HAL_GPIO_PORT_D);
    portE = halGPIOReadPort(HAL_GPIO_PORT_E);
    portF = halGPIOReadPort(HAL_GPIO_PORT_F);
    portG = halGPIOReadPort(HAL_GPIO_PORT_G);

    // Activa el modul CN
    //
    CNCONbits.ON = 1;

    halINTEnableInterrupts();
}


void halCNDisable(void) {

    halINTDisableInterrupts();

    // Desactiva el modul
    //
    CNCONbits.ON = 0;
    
    // Desactiva la interrupcio CN
    //
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    
    halINTEnableInterrupts();
}


void isrCNHandler(void) {

    if (PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_CHANGE_NOTICE)) {
        
        // Llegeix l'estat dels ports
        //
        uint32_t newPortA = halGPIOReadPort(HAL_GPIO_PORT_A);
        uint32_t newPortB = halGPIOReadPort(HAL_GPIO_PORT_B);
        uint32_t newPortC = halGPIOReadPort(HAL_GPIO_PORT_C);
        uint32_t newPortD = halGPIOReadPort(HAL_GPIO_PORT_D);
        uint32_t newPortE = halGPIOReadPort(HAL_GPIO_PORT_E);
        uint32_t newPortF = halGPIOReadPort(HAL_GPIO_PORT_F);
        uint32_t newPortG = halGPIOReadPort(HAL_GPIO_PORT_G);
        
        unsigned i;
        for (i = 0; i < MAX_CNINPUTS; i++) {

        }
        
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    }    
}