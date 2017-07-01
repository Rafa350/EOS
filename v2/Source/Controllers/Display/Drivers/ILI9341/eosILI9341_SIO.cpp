#include "eos.h"


#ifdef ILI9341_IO_TYPE_SIO

#if !defined(ILI9341_IO_SUBTYPE_SIO_HAL) && \
	!defined(ILI9341_IO_SUBTYPE_SIO_DIRECT)
#error No se especifico ILI9341_IO_SUBTYPE_SIO_xxx.
#endif

#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"

#ifdef ILI9341_IO_SUBTYPE_SIO_HAL
#include "Hal/halGPIO.h"
#endif


// Control dels pins a traves del modul HAL GPIO
//
#if defined(ILI9341_IO_SUBTYPE_SIO_HAL)

// Control del pin RST
//
#ifdef ILI9341_RST_PORT
#define initRST()  halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN); \
                   halGPIOInitialize(ILI9341_RST_PORT, ILI9341_RST_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH)
#define setRST()   halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define clrRST()   halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN); \
                   halGPIOInitialize(ILI9341_CS_PORT, ILI9341_CS_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setCS()    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define clrCS()    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN); \
                   halGPIOInitialize(ILI9341_RS_PORT, ILI9341_RS_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setRS()    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN)
#define clrRS()    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN)

// Control del pin CLK
//
#define initCLK()  halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN); \
                   halGPIOInitialize(ILI9341_CLK_PORT, ILI9341_CLK_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setCLK()   halGPIOSetPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)
#define clrCLK()   halGPIOClearPin(ILI9341_CLK_PORT, ILI9341_CLK_PIN)

// Control del pin MOSI
//
#define initMOSI() halGPIOClearPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN); \
                   halGPIOInitialize(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setMOSI()  halGPIOSetPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN)
#define clrMOSI()  halGPIOClearPin(ILI9341_MOSI_PORT, ILI9341_MOSI_PIN)


// Control dels pins de forma directa per PIC32MX
//
#elif defined(ILI9341_IO_SUBTYPE_SIO_DIRECT) && defined(EOS_PIC32MX)

// Control dels pins de forma directa per STM32F4
//
#elif defined(ILI9341_IO_SUBTYPE_SIO_DIRECT) && defined(EOS_STM32F4)

#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_Driver::lcdInitialize() {

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
void ILI9341_Driver::lcdReset() {

#ifdef ILI9341_RST_PORT
    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
#endif
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdOpen() {

	clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdClose() {

    setCS();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda.
/// \param d: El byte a escriure.
///
void ILI9341_Driver::lcdWriteCommand(
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
void ILI9341_Driver::lcdWriteData(
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
uint8_t ILI9341_Driver::lcdReadData() {

#ifdef ILI9341_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = 0;

    return data;

#endif
}


#endif

