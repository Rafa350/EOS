#include "eos.hpp"


#ifdef ILI9341_INTERFACE_TYPE_SERIAL_8BIT

#if !defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_STM32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#error No se especifico ILI9341_INTERFACE_MODE_xxx adecuadamente.
#endif

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
#ifdef ILI9341_RST_PORT
#define initRST()  halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN); \
                   halGPIOInitializePin(ILI9341_RST_PORT, ILI9341_RST_PIN, HAL_GPIO_DIRECTION_OUTPUT)
#define setRST()   halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define clrRST()   halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN); \
                   halGPIOInitializePin(ILI9341_CS_PORT, ILI9341_CS_PIN, HAL_GPIO_DIRECTION_OUTPUT)
#define setCS()    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define clrCS()    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN); \
                   halGPIOInitializePin(ILI9341_RS_PORT, ILI9341_RS_PIN, HAL_GPIO_DIRECTION_OUTPUT)
#define setRS()    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN)
#define clrRS()    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN)

// Control del pin CLK
//
#define initCLK()  halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN); \
                   halGPIOInitializePin(ILI9341_CLK_PORT, ILI9341_CLK_PIN, HAL_GPIO_DIRECTION_OUTPUT)
#define setCLK()   halGPIOSetPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)
#define clrCLK()   halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)

// Control del pin SO
//
#define initSO()   halGPIOClearPin(ILI9341_SO_PORT, ILI9341_SO_PIN); \
                   halGPIOInitializePinOutput(ILI9341_SO_PORT, ILI9341_SO_PIN)
#define setSO()    halGPIOSetPin(ILI9341_SO_PORT, ILI9341_SO_PIN)
#define clrSO()    halGPIOClearPin(ILI9341_SO_PORT, ILI9341_SO_PIN)

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

#ifdef ILI9341_RST_PORT
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

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_IO::begin() {

	clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_IO::end() {

    setCS();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrCommand(
    uint8_t data) {

    halINTDisableInterrupts();

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

    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrData(
    uint8_t data) {

    halINTDisableInterrupts();

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

    halINTEnableInterrupts();
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ILI9341_IO::rdData() {

#ifdef ILI9341_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = 0;

    return data;

#endif
}


#endif

