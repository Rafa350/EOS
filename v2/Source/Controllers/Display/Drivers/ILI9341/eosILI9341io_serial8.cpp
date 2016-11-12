#include "eos.hpp"


#ifdef ILI9341_INTERFACE_TYPE_SERIAL_8BIT

#if !defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_STM32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#error No se especifico ILI9341_INTERFACE_MODE_xxx adecuadamente.
#endif

#include "eosMacros.h"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO)

#elif defined(ILI9341_INTERFACE_MODE_STM32_GPIO)
#include "xc.h"
#elif defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#include "Hal/halGPIO.h"
#endif


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO)

#elif defined(ILI9341_INTERFACE_MODE_STM32_GPIO)

#elif defined(ILI9341_INTERFACE_MODE_HAL_GPIO)

// Control del pin RST
//
#ifdef ILI9341_RSTPort
#define RSTPort    concat2(GPIO_PORT_, ILI9341_RSTPort)
#define RSTPin     concat2(GPIO_PIN_, ILI9341_RSTPin)
#define initRST()  halGPIOClearPin(RSTPort, RSTPin); \
                   halGPIOInitializePinOutput(RSTPort, RSTPin)
#define setRST()   halGPIOSetPin(RSTPort, RSTPin)
#define clrRST()   halGPIOClearPin(RSTPort, RSTPin)
#endif

// Control del pin CS
//
#define CSPort     concat2(GPIO_PORT_, ILI9341_CSPort)
#define CSPin      concat2(GPIO_PIN_, ILI9341_CSPin)
#define initCS()   halGPIOSetPin(CSPort, CSPin); \
                   halGPIOInitializePinOutput(CSPort, CSPin)
#define setCS()    halGPIOSetPin(CSPort, CSPin)
#define clrCS()    halGPIOClearPin(CSPort, CSPin)

// Control del pin RS
//
#define RSPort     concat2(GPIO_PORT_, ILI9341_RSPort)
#define RSPin      concat2(GPIO_PIN_, ILI9341_RSPin)
#define initRS()   halGPIOClearPin(RSPort, RSPin); \
                   halGPIOInitializePinOutput(RSPort, RSPin)
#define setRS()    halGPIOSetPin(RSPort, RSPin)
#define clrRS()    halGPIOClearPin(RSPort, RSPin)

// Control del pin CLK
//
#define CLKPort    concat2(GPIO_PORT_, ILI9341_CLKPort)
#define CLKPin     concat2(GPIO_PIN_, ILI9341_CLKPin)
#define initCLK()  halGPIOClearPin(CLKPort, RSPin); \
                   halGPIOInitializePinOutput(CLKPort, CLKPin)
#define setCLK()   halGPIOSetPin(CLKPort, CLKPin)
#define clrCLK()   halGPIOClearPin(CLKPort, CLKPin)

// Control del pin SO
//
#define SOPort     concat2(GPIO_PORT_, ILI9341_SOPort)
#define SOPin      concat2(GPIO_PIN_, ILI9341_SOPin)
#define initSO()   halGPIOClearPin(SOPort, SOPin); \
                   halGPIOInitializePinOutput(SOPort, SOPin)
#define setSO()    halGPIOSetPin(SOPort, SOPin)
#define clrSO()    halGPIOClearPin(SOPort, SOPin)

#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
ILI9341_IO::ILI9341_IO() {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_IO::initialize() {

#ifdef ILI9341_RSTPort
    initRST();
#endif
    initCS();
    initRS();
    initCLK();
    initSO();
#ifndef ILI9341_INTERFACE_WRITEONLY
    initSI();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_IO::reset() {

#ifdef ILI9341_RSTPort
    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_IO::begin() {

    halINTDisableInterrupts();
    clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_IO::end() {

    setCS();
    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrCommand(
    uint8_t data) {

    clrRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((data & mask) != 0)
            setSO();
        else
            clrSO();
        setCLK();
    }
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrData(
    uint8_t data) {

    setRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((data & mask) != 0)
            setSO();
        else
            clrSO();
        setCLK();
    }
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341_IO::rdData() {

#ifdef ILI9341_INRERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = 0;

    return data;

#endif
}


#endif

