#include "eos.h"

 
#ifdef ILI9341_INTERFACE_TYPE_SERIAL_8BIT

#if !defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_STM32_GPIO) && \
	!defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#error No se especifico ILI9341_INTERFACE_MODE_xxx adecuadamente.
#endif

#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && defined(EOS_PIC32MX)
#include "xc.h"
#elif defined(ILI9341_INTERFACE_MODE_STM32_GPIO) && defined(EOS_STM32F4)
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
                   halGPIOInitializePin(ILI9341_RST_PORT, ILI9341_RST_PIN, HAL_GPIO_MODE_OUTPUT)
#define setRST()   halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define clrRST()   halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN); \
                   halGPIOInitializePin(ILI9341_CS_PORT, ILI9341_CS_PIN, HAL_GPIO_MODE_OUTPUT)
#define setCS()    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define clrCS()    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN); \
                   halGPIOInitializePin(ILI9341_RS_PORT, ILI9341_RS_PIN, HAL_GPIO_MODE_OUTPUT)
#define setRS()    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN)
#define clrRS()    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN)

// Control del pin CLK
//
#define initCLK()  halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN); \
                   halGPIOInitializePin(ILI9341_CLK_PORT, ILI9341_CLK_PIN, HAL_GPIO_MODE_OUTPUT)
#define setCLK()   halGPIOSetPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)
#define clrCLK()   halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)

// Control del pin MOSI
//
#define initMOSI() halGPIOClearPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN); \
                   halGPIOInitializePinOutput(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN)
#define setMOSI()  halGPIOSetPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN)
#define clrMOSI()  halGPIOClearPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN)

#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ioInitialize() {

#ifdef ILI9341_RST_PORT
    initRST();
#endif
    initCS();
    initRS();
    initCLK();
    initMOSI();
#ifndef ILI9341_INTERFACE_WRITEONLY
    initSI();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ioReset() {

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ioBegin() {

	clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ioEnd() {

    setCS();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param d: El byte a escriure.
///
void ioWriteCommand(
    uint8_t d) {

    halINTDisableInterrupts();

    clrRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((d & mask) != 0)
            setMOSI();
        else
            clrMOSI();
        setCLK();
    }

    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades.
/// \param d: El byte a escriure.
///
void ioWriteData(
    uint8_t d) {

    halINTDisableInterrupts();

    setRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((d & mask) != 0)
            setMOSI();
        else
            clrMOSI();
        setCLK();
    }

    halINTEnableInterrupts();
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte de dades.
/// \return El byte lleigit.
///
uint8_t ioReadData() {

#ifdef ILI9341_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = 0;

    return data;

#endif
}


#endif
