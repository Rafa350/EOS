#include "eos.h"
 

#ifdef ILI9341_INTERFACE_TYPE_PARALEL_8BIT

#include "eosMacros.h"
#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && defined(EOS_PIC32MX)
#include <xc.h>
#elif defined(ILI9341_INTERFACE_MODE_STM32_GPIO) && defined(EOS_STM32F4)
#elif defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#include "Hal/halGPIO.h"
#endif


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO) && defined(EOS_PIC32MX)

#if defined(PORTA)
#define HAL_GPIO_PORT_A      A
#endif
#if defined(PORTB)
#define HAL_GPIO_PORT_B      B
#endif
#if defined(PORTC)
#define HAL_GPIO_PORT_C      C
#endif
#if defined(PORTD)
#define HAL_GPIO_PORT_D      D
#endif
#if defined(PORTE)
#define HAL_GPIO_PORT_E      E
#endif
#if defined(PORTF)
#define HAL_GPIO_PORT_F      F
#endif
#if defined(PORTG)
#define HAL_GPIO_PORT_G      G
#endif

#define HAL_GPIO_PIN_0       0
#define HAL_GPIO_PIN_1       1
#define HAL_GPIO_PIN_2       2
#define HAL_GPIO_PIN_3       3
#define HAL_GPIO_PIN_4       4
#define HAL_GPIO_PIN_5       5
#define HAL_GPIO_PIN_6       6
#define HAL_GPIO_PIN_7       7
#define HAL_GPIO_PIN_8       8
#define HAL_GPIO_PIN_9       9
#define HAL_GPIO_PIN_10      10
#define HAL_GPIO_PIN_11      11
#define HAL_GPIO_PIN_12      12
#define HAL_GPIO_PIN_13      13
#define HAL_GPIO_PIN_14      14
#define HAL_GPIO_PIN_15      15

// Control del pin RST
//
#define initRST()  concat3(LAT, ILI9341_RST_PORT, CLR) = 1 << ILI9341_RST_PIN; \
                   concat3(TRIS, ILI9341_RST_PORT, CLR) = 1 << ILI9341_RST_PIN
#define setRST()   concat3(LAT, ILI9341_RST_PORT, SET) = 1 << ILI9341_RST_PIN
#define clrRST()   concat3(LAT, ILI9341_RST_PORT, CLR) = 1 << ILI9341_RST_PIN

// Control del pin CS
//
#define initCS()   concat3(LAT, ILI9341_CS_PORT, SET) = 1 << ILI9341_CS_PIN; \
                   concat3(TRIS, ILI9341_CS_PORT, CLR) = 1 << ILI9341_CS_PIN
#define setCS()    concat3(LAT, ILI9341_CS_PORT, SET) = 1 << ILI9341_CS_PIN
#define clrCS()    concat3(LAT, ILI9341_CS_PORT, CLR) = 1 << ILI9341_CS_PIN

// Control del pin RS
//
#define initRS()   concat3(LAT, ILI9341_RS_PORT, CLR) = 1 << ILI9341_RS_PIN; \
                   concat3(TRIS, ILI9341_RS_PORT, CLR) = 1 << ILI9341_RS_PIN
#define setRS()    concat3(LAT, ILI9341_RS_PORT, SET) = 1 << ILI9341_RS_PIN
#define clrRS()    concat3(LAT, ILI9341_RS_PORT, CLR) = 1 << ILI9341_RS_PIN

// Control el pin WR
//
#define initWR()   concat3(LAT, ILI9341_WR_PORT, SET) = 1 << ILI9341_WR_PIN; \
                   concat3(TRIS, ILI9341_WR_PORT, CLR) = 1 << ILI9341_WR_PIN
#define setWR()    concat3(LAT, ILI9341_WR_PORT, SET) = 1 << ILI9341_WR_PIN
#define clrWR()    concat3(LAT, ILI9341_WR_PORT, CLR) = 1 << ILI9341_WR_PIN

// Control del pin RD
//
#ifndef ILI9341_INTERFACE_WRITEONLY
#define initRD()   concat3(LAT, ILI9341_RD_PORT, SET) = 1 << ILI9341_RD_PIN; \
                   concat3(TRIS, ILI9341_RD_PORT, CLR) = 1 << ILI9341_RD_PIN
#define setRD()    concat3(LAT, ILI9341_RD_PORT, SET) = 1 << ILI9341_RD_PIN
#define clrRD()    concat3(LAT, ILI9341_RD_PORT, CLR) = 1 << ILI9341_RD_PIN
#endif

// Control del port DATA
//
#define initDATA()   concat3(TRIS, ILI9341_DATA_PORT, SET) = 0x00FF
#define hizDATA()    concat3(TRIS, ILI9341_DATA_POTT, SET) = 0x00FF
#define wrDATA(data) concat3(TRIS, ILI9341_DATA_PORT, CLR) = 0x00FF; \
                     concat2(LAT, ILI9341_DATA_PORT) =  data
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA(data) data = concat2(PORT, ILI9341_DATA_PORT)
#endif

#elif defined(ILI9341_INTERFACE_MODE_HAL_GPIO)

// Control del pin RST
//
#ifdef ILI9341_RST_PORT
#define initRST()  halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN); \
                   halGPIOInitializePinOutput(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define setRST()   halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define clrRST()   halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif

// Control del pin CS
//
#define initCS()   halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN); \
                   halGPIOInitializePinOutput(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define setCS()    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define clrCS()    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN)

// Control del pin RS
//
#define initRS()   halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN); \
                   halGPIOInitializePinOutput(ILI9341_RS_PORT, ILI9341_RS_PIN)
#define setRS()    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN)
#define clrRS()    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN)

// Control el pin WR
//
#define initWR()   halGPIOSetPin(ILI9341_WR_PORT, ILI9341_WR_PIN); \
                   halGPIOInitializePinOutput(ILI9341_WR_PORT, ILI9341_WR_PIN)
#define setWR()    halGPIOSetPin(ILI9341_WR_PORT, ILI9341_WR_PIN)
#define clrWR()    halGPIOClearPin(ILI9341_WR_PORT, ILI9341_WR_PIN)

// Control del pin RD
//
#ifndef ILI9341_INTERFACE_WRITEONLY
#define initRD()   halGPIOSetPin(ILI9341_RD_PORT, ILI9341_RD_PIN); \
                   halGPIOInitializePinOutput(ILI9341_RD_PORT, ILI9341_RD_PIN)
#define setRD()    halGPIOSetPin(ILI9341_RD_PORT, ILI9341_RD_PIN)
#define clrRD()    halGPIOClearPin(ILI9341_RD_PORT, ILI9341_RD_PIN)
#endif

// Control del port DATA
//
#define initDATA()   halGPIOInitializePortInput(ILI9341_DATA_PORT, 0x00FF)
#define wrDATA(data) halGPIOInitializePortOutput(ILI9341_DATA_PORT, 0x00FF); \
                     halGPIOWritePort(ILI9341_DATA_PORT, data)
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA(data) halGPIOInitializePortInput(ILI9341_DATA_PORT, 0x00FF); \
                     data = halGPIOReadPort(ILI9341_DATA_PORT)
#endif

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
    initWR();
#ifndef ILI9341_INTERFACE_WRITEONLY
    initRD();
#endif
    initDATA();
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ioReset() {

    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ioBegin() {

    halINTDisableInterrupts();
    clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ioEnd() {

    setCS();
    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de comandes.
/// \param d: El byte a escriure.
///
void ioWriteCommand(
    uint8_t d) {

    clrRS();
    clrWR();
    wrDATA(d);
    setWR();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param d: El byte a escriure.
///
void ioWriteData(
    uint8_t d) {

    setRS();
    clrWR();
    wrDATA(d);
    setWR();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ioReadData() {

#ifdef ILI9342_INTERFACE_WRITEONLY
    return 0;
    
#else
    uint8_t data;

    setRS();
    clrRD();
    rdDATA(data);
    setRD();

    return data;
#endif
}


#endif