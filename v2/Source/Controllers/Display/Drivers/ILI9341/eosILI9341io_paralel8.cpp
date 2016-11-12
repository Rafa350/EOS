#include "eos.hpp"


#ifdef ILI9341_INTERFACE_TYPE_PARALEL_8BIT

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
#define initRD()   concat3(LAT, ILI9341_RDPort, SET) = 1 << ILI9341_RDPin; \
                   concat3(TRIS, ILI9341_RDPort, CLR) = 1 << ILI9341_RDPin
#define setRD()    concat3(LAT, ILI9341_RDPort, SET) = 1 << ILI9341_RDPin
#define clrRD()    concat3(LAT, ILI9341_RDPort, CLR) = 1 << ILI9341_RDPin
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

// Control el pin WR
//
#define WRPort     concat2(GPIO_PORT_, ILI9341_WRPort)
#define WRPin      concat2(GPIO_PIN_, ILI9341_WRPin)
#define initWR()   halGPIOSetPin(WRPort, WRPin); \
                   halGPIOInitializePinOutput(WRPort, WRPin)
#define setWR()    halGPIOSetPin(WRPort, WRPin)
#define clrWR()    halGPIOClearPin(WRPort, WRPin)

// Control del pin RD
//
#ifndef ILI9341_INTERFACE_WRITEONLY
#define RDPort     concat2(GPIO_PORT_, ILI9341_RDPort)
#define RDPin      concat2(GPIO_PIN_, ILI9341_RDPin)
#define initRD()   halGPIOSetPin(RDPort, RDPin); \
                   halGPIOInitializePinOutput(RDPort, RDPin)
#define setRD()    halGPIOSetPin(RDPort, RDPin)
#define clrRD()    halGPIOClearPin(RDPort, RDPin)
#endif

// Control del port DATA
//
#define DATAPort     concat2(GPIO_PORT_, ILI9341_DATAPort)
#define initDATA()   halGPIOInitializePortInput(DATAPort, 0x00FF)
#define wrDATA(data) halGPIOInitializePortOutput(DATAPort, 0x00FF); \
                     halGPIOWritePort(DATAPort, data)
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA(data) halGPIOInitializePortInput(DATAPort, 0x00FF); \
                     data = halGPIOReadPort(DATAPort)
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

#ifdef ILI9341_RSTPort
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
