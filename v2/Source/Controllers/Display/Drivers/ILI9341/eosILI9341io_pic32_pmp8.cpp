#include "eos.hpp"


#ifdef ILI9341_INTERFACE_TYPE_PIC32_PMP8

#include "eosMacros.h"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO)
#include <xc.h>
#elif defined(ILI9341_INTERFACE_MODE_STM32_GPIO)
#elif defined(ILI9341_INTERFACE_MODE_HAL_GPIO)
#include "Hal/halGPIO.h"
#endif


#if defined(ILI9341_INTERFACE_MODE_PIC32_GPIO)

// Control del pin RST
//
#define initRST()  concat3(LAT, ILI9341_RSTPort, CLR) = 1 << ILI9341_RSTPin; \
                   concat3(TRIS, ILI9341_RSTPort, CLR) = 1 << ILI9341_RSTPin
#define setRST()   concat3(LAT, ILI9341_RSTPort, SET) = 1 << ILI9341_RSTPin
#define clrRST()   concat3(LAT, ILI9341_RSTPort, CLR) = 1 << ILI9341_RSTPin

// Control del pin CS
//
#define initCS()   concat3(LAT, ILI9341_CSPort, SET) = 1 << ILI9341_CSPin; \
                   concat3(TRIS, ILI9341_CSPort, CLR) = 1 << ILI9341_CSPin
#define setCS()    concat3(LAT, ILI9341_CSPort, SET) = 1 << ILI9341_CSPin
#define clrCS()    concat3(LAT, ILI9341_CSPort, CLR) = 1 << ILI9341_CSPin

// Control del pin RS
//
#define initRS()   concat3(LAT, ILI9341_RSPort, CLR) = 1 << ILI9341_RSPin; \
                   concat3(TRIS, ILI9341_RSPort, CLR) = 1 << ILI9341_RSPin
#define setRS()    concat3(LAT, ILI9341_RSPort, SET) = 1 << ILI9341_RSPin
#define clrRS()    concat3(LAT, ILI9341_RSPort, CLR) = 1 << ILI9341_RSPin

// Control el pin WR
//
#define initWR()   concat3(LAT, ILI9341_WRPort, SET) = 1 << ILI9341_WRPin; \
                   concat3(TRIS, ILI9341_WRPort, CLR) = 1 << ILI9341_WRPin
#define setWR()    concat3(LAT, ILI9341_WRPort, SET) = 1 << ILI9341_WRPin
#define clrWR()    concat3(LAT, ILI9341_WRPort, CLR) = 1 << ILI9341_WRPin

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
#define initDATA()   concat3(TRIS, ILI9341_DATAPort, SET) = 0x00FF
#define hizDATA()    concat3(TRIS, ILI9341_DATAPort, SET) = 0x00FF
#define wrDATA(data) concat3(TRIS, ILI9341_DATAPort, CLR) = 0x00FF; \
                     concat2(LAT, ILI9341_DATAPort) =  data
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA()     concat2(PORT, ILI9341_DATAPort)
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
    initWR();
#ifndef ILI9341_INTERFACE_WRITEONLY
    initRD();
#endif
    initDATA();
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_IO::reset() {

    halTMRDelay(10);
    setRST();
    halTMRDelay(120);
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
/// \brief Escriu un byte en el registre de comandes.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrCommand(
    uint8_t data) {

    clrRS();
    clrWR();
    wrDATA(data);
    setWR();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param data: El byte a escriure.
///
void ILI9341_IO::wrData(
    uint8_t data) {

    setRS();
    clrWR();
    wrDATA(data);
    setWR();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ILI9341_IO::rdData() {

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
