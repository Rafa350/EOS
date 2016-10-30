#include "eos.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"


#if !defined(ILI9341_INTERFACE_P8)
#error "No se especifico ILI9341_INTERFACE_P8"
#endif


#define __makePort2(base, port) base ## port
#define __makePort3(base, port, suffix) base ## port ## suffix

#define __setPin(base, port, pin) __makePort3(base, port, SET) = 1 << pin
#define __clrPin(base, port, pin) __makePort3(base, port, CLR) = 1 << pin
#define __invPin(base, port, pin) __makePort3(base, port, INV) = 1 << pin
#define __getPin(base, port, pin) __makePort2(base, port) & ~(1 << pin) != 0)

#define __setPort(base, port, mask) __makePort3(base, port, SET) = mask
#define __clrPort(base, port, mask) __makePort3(base, port, CLR) = mask
#define __invPort(base, port, mask) __makePort3(base, port, INV) = mask
#define __wrPort(base, port, data) __makePort2(base, port) = data
#define __rdPort(base, port) __makePort2(base, port)


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
#if defined(ILI9341_INTERFACE_P8)
#define initWR()   __setPin(LAT, ILI9341_WRPort, ILI9341_WRPin); \
                   __clrPin(TRIS, ILI9341_WRPort, ILI9341_WRPin)
#define setWR()    __setPin(LAT, ILI9341_WRPort, ILI9341_WRPin)
#define clrWR()    __clrPin(LAT, ILI9341_WRPort, ILI9341_WRPin)
#endif

// Control del pin RD
//
#if !defined(ILI9341_READONLY)    
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
#if !defined(ILI9341_INTERFACE_READONLY)
#define rdDATA()     __rdPort(PORT, ILI9341_DATAPort)
#endif

// Control de les interrupcions
//
#define enableInterrupts()   __builtin_enable_interrupts()
#define disableInterrupts()  __builtin_disable_interrupts()


using namespace eos;


static void delay(unsigned ms);


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
#if !defined(ILI9341_READONLY)    
    initRD();
#endif    
    initDATA();    
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_IO::reset() {

    delay(10);
    setRST();
    delay(120);
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
/// \brief Selecciona l'adressa de lectura/escriptura del driver.
/// \param addr: L'adressa a seleccionar.
///
void ILI9341_IO::address(
    uint8_t addr) {
    
    if (addr)
        setRS();
    else
        clrRS();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en l'adresa seleccionada del driver.
/// \param data: El byte a escriure.
///
void ILI9341_IO::write(
    uint8_t data) {

    clrWR();
    wrDATA(data);
    setWR();
    hizDATA();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ILI9341_IO::read() {
    
    uint8_t data;
    
    clrRD();
    data = rdDATA() & 0x000000FF;
    setRD();
    
    return data;    
}


/// ----------------------------------------------------------------------
/// \brief Retard.
/// \params ms: Temps de retard en ms.
///
static void delay(unsigned ms) {
    
/*    unsigned startTime = ReadCT();
    while (((ReadCT() - startTime) * 1000) < ms)
        continue;
 */
    for (unsigned i = 0, ii = 10000 * ms; i < ii; i++)
        Nop();
}

