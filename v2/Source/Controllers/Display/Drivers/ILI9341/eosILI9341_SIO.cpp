#include "eos.h"


#ifdef DISPLAY_IO_TYPE_SIO

#if !defined(DISPLAY_IO_SUBTYPE_SIO_HAL) && \
	!defined(DISPLAY_IO_SUBTYPE_SIO_DIRECT)
#error No se especifico DISPLAY_IO_SUBTYPE_SIO_xxx.
#endif

#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"

#ifdef DISPLAY_IO_SUBTYPE_SIO_HAL
#include "Hal/halGPIO.h"
#endif


// Control dels pins a traves del modul HAL GPIO
//
#if defined(DISPLAY_IO_SUBTYPE_SIO_HAL)

// Control del pin RST
//
#ifdef DISPLAY_RST_PORT
#define initRST()  halGPIOClearPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN); \
                   halGPIOInitialize(DISPLAY_RST_PORT, DISPLAY_RST_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH)
#define setRST()   halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN)
#define clrRST()   halGPIOClearPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN); \
                   halGPIOInitialize(DISPLAY_CS_PORT, DISPLAY_CS_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setCS()    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN)
#define clrCS()    halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN); \
                   halGPIOInitialize(DISPLAY_RS_PORT, DISPLAY_RS_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setRS()    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN)
#define clrRS()    halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN)

// Control del pin CLK
//
#define initCLK()  halGPIOClearPin(DISPLAY_CLK_PORT, DISPLAY_CLK_PIN); \
                   halGPIOInitialize(DISPLAY_CLK_PORT, DISPLAY_CLK_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setCLK()   halGPIOSetPin(DISPLAY_CLK_PORT, DISPLAY_CLK_PIN)
#define clrCLK()   halGPIOClearPin(DISPLAY_CLK_PORT, DISPLAY_CLK_PIN)

// Control del pin MOSI
//
#define initMOSI() halGPIOClearPin(DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN); \
                   halGPIOInitialize(DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN, HAL_GPIO_MODE_OUTPUT | HAL_GPIO_SPEED_HIGH, 0)
#define setMOSI()  halGPIOSetPin(DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN)
#define clrMOSI()  halGPIOClearPin(DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN)


// Control dels pins de forma directa per PIC32MX
//
#elif defined(DISPLAY_IO_SUBTYPE_SIO_DIRECT) && defined(EOS_PIC32MX)

// Control dels pins de forma directa per STM32F4
//
#elif defined(DISPLAY_IO_SUBTYPE_SIO_DIRECT) && defined(EOS_STM32F4)
#error SIO_DIRECT no soportado en STM32
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_Driver::lcdInitialize() {

#ifdef DISPLAY_RST_PORT
    initRST();
#endif
    initCS();
    initRS();
    initCLK();
    initMOSI();
#ifndef DISPLAY_INTERFACE_WRITEONLY
    initSI();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_Driver::lcdReset() {

#ifdef DISPLAY_RST_PORT
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
    uint8_t cmd) {

    halINTDisableInterrupts();

    clrRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((cmd & mask) != 0)
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
    uint8_t data) {

    halINTDisableInterrupts();

    setRS();

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        clrCLK();
        if ((data & mask) != 0)
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

#ifdef DISPLAY_INTERFACE_WRITEONLY

	return 0;

#else

    uint8_t data = 0;

    return data;

#endif
}


#endif

