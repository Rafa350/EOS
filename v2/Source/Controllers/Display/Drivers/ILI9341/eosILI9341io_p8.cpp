#include "eos.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "Hal/halGPIO.h"
#include "Hal/halTMR.h"


#define __concat2(a, b)      a ## b
#define __concat3(a, b, c)   a ## b ## c
#define concat2(a, b)        __concat2(a, b)
#define concat3(a, b, c)     __concat3(a, b, c)


#if defined(ILI9341_INTERFACE_MODE_DIRECT)

#define __setPin(base, port, pin) concat3(base, port, SET) = 1 << pin
#define __clrPin(base, port, pin) concat3(base, port, CLR) = 1 << pin
#define __invPin(base, port, pin) concat3(base, port, INV) = 1 << pin
#define __getPin(base, port, pin) concat2(base, port) & ~(1 << pin) != 0)

#define __setPort(base, port, mask) concat3(base, port, SET) = mask
#define __clrPort(base, port, mask) concat3(base, port, CLR) = mask
#define __invPort(base, port, mask) concat3(base, port, INV) = mask
#define __wrPort(base, port, data) concat2(base, port) = data
#define __rdPort(base, port) concat2(base, port)

// Control del pin RST
//
#define initRST()  __clrPin(LAT, ILI9341_RSTPort, ILI9341_RSTPin); \
                   __clrPin(TRIS, ILI9341_RSTPort, ILI9341_RSTPin)
#define setRST()   __setPin(LAT, ILI9341_RSTPort, ILI9341_RSTPin)
#define clrRST()   __clrPin(LAT, ILI9341_RSTPort, ILI9341_RSTPin)

// Control del pin CS
//
#define initCS()   __setPin(LAT, ILI9341_CSPort, ILI9341_CSPin); \
                   __clrPin(TRIS, ILI9341_CSPort, ILI9341_CSPin)
#define setCS()    __setPin(LAT, ILI9341_CSPort, ILI9341_CSPin)
#define clrCS()    __clrPin(LAT, ILI9341_CSPort, ILI9341_CSPin)

// Control del pin RS
//
#define initRS()   __clrPin(LAT, ILI9341_RSPort, ILI9341_RSPin); \
                   __clrPin(TRIS, ILI9341_RSPort, ILI9341_RSPin)
#define setRS()    __setPin(LAT, ILI9341_RSPort, ILI9341_RSPin)
#define clrRS()    __clrPin(LAT, ILI9341_RSPort, ILI9341_RSPin)

// Control el pin WR
//
#define initWR()   __setPin(LAT, ILI9341_WRPort, ILI9341_WRPin); \
                   __clrPin(TRIS, ILI9341_WRPort, ILI9341_WRPin)
#define setWR()    __setPin(LAT, ILI9341_WRPort, ILI9341_WRPin)
#define clrWR()    __clrPin(LAT, ILI9341_WRPort, ILI9341_WRPin)

// Control del pin RD
//
#ifndef ILI9341_INTERFACE_WRITEONLY
#define initRD()   __setPin(LAT, ILI9341_RDPort, ILI9341_RDPin); \
                   __clrPin(TRIS, ILI9341_RDPort, ILI9341_RDPin)
#define setRD()    __setPin(LAT, ILI9341_RDPort, ILI9341_RDPin)
#define clrRD()    __clrPin(LAT, ILI9341_RDPort, ILI9341_RDPin)
#endif

// Control del port DATA
//
#define initDATA()   __setPort(TRIS, ILI9341_DATAPort, 0xFF)
#define hizDATA()    __setPort(TRIS, ILI9341_DATAPort, 0xFF)
#define wrDATA(data) __clrPort(TRIS, ILI9341_DATAPort, 0xFF); \
                     __wrPort(LAT, ILI9341_DATAPort, data)
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA()     __rdPort(PORT, ILI9341_DATAPort)
#endif

#elif defined(ILI9341_INTERFACE_MODE_HAL)

// Control del pin RST
//
#define RSTPort    concat2(gpioPort, ILI9341_RSTPort)
#define RSTPin     ILI9341_RSTPin

#define initRST()  halGPIOClearPin(RSTPort, RSTPin); \
                   halGPIOInitializePin(RSTPort, RSTPin, pinOutput)
#define setRST()   halGPIOSetPin(RSTPort, RSTPin)
#define clrRST()   halGPIOClearPin(RSTPort, RSTPin)

// Control del pin CS
//
#define CSPort     concat2(gpioPort, ILI9341_CSPort)
#define CSPin      ILI9341_CSPin

#define initCS()   halGPIOSetPin(CSPort, CSPin); \
                   halGPIOInitializePin(CSPort, CSPin, pinOutput)
#define setCS()    halGPIOSetPin(CSPort, CSPin)
#define clrCS()    halGPIOClearPin(CSPort, CSPin)

// Control del pin RS
//
#define RSPort     concat2(gpioPort, ILI9341_RSPort)
#define RSPin      ILI9341_RSPin

#define initRS()   halGPIOClearPin(RSPort, RSPin); \
                   halGPIOInitializePin(RSPort, RSPin, pinOutput)
#define setRS()    halGPIOSetPin(RSPort, RSPin)
#define clrRS()    halGPIOClearPin(RSPort, RSPin)

// Control el pin WR
//
#define WRPort     concat2(gpioPort, ILI9341_WRPort)
#define WRPin      ILI9341_WRPin

#define initWR()   halGPIOSetPin(WRPort, WRPin); \
                   halGPIOInitializePin(WRPort, WRPin, pinOutput)
#define setWR()    halGPIOSetPin(WRPort, WRPin)
#define clrWR()    halGPIOClearPin(WRPort, WRPin)

// Control del pin RD
//
#ifndef ILI9341_INTERFACE_WRITEONLY
#define RDPort     concat2(gpioPort, ILI9341_RDPort)
#define RDPin      ILI9341_RDPin

#define initRD()   halGPIOSetPin(RDPort, RDPin); \
                   halGPIOInitializePin(RDPort, RDPin, pinOutput)
#define setRD()    halGPIOSetPin(RDPort, RDPin)
#define clrRD()    halGPIOClearPin(RDPort, RDPin)
#endif

// Control del port DATA
//
#define DATAPort     concat2(gpioPort, ILI9341_DATAPort)

#define initDATA()   halGPIOInitializePort(DATAPort, portInput)
#define hizDATA()    halGPIOInitializePort(DATAPort, portInput)
#define wrDATA(data) halGPIOInitializePort(DATAPort, portOutput); \
                     halGPIOWritePort(DATAPort, data)
#ifndef ILI9341_INTERFACE_WRITEONLY
#define rdDATA()     halGPIOReadPort(DATAPort)
#endif

#endif

// Control de les interrupcions
//
#define enableInterrupts()   __builtin_enable_interrupts()
#define disableInterrupts()  __builtin_disable_interrupts()


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

    initRST();
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
    
    disableInterrupts();
    clrCS();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_IO::end() {
   
    setCS();
    enableInterrupts();
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
    hizDATA();
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
    hizDATA();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
#ifndef ILI9342_INTERFACE_WRITEONLY
uint8_t ILI9341_IO::rdData() {
    
    uint8_t data;
    
    setRS();
    clrRD();
    data = rdDATA() & 0x000000FF;
    setRD();
    
    return data;    
}
#endif
