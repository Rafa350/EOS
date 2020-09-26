#include "eos.h"
#include "HAL/PIC32/halINT.h"


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions.
/// \param    source: El identificador de la interrupcio.
///
void halINTEnableInterrupt(
    INTSource source) {
    
    volatile uint32_t* IECx = (volatile uint32_t*) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t* IECxSET = (volatile uint32_t *)(IECx + 2);
    *IECxSET = 1 << (source & 0x1f);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions.
/// \param    source: El identificador de la interrupcio.
/// \return   El estat per restaurar la interrupcio.
///
bool halINTDisableInterrupt(
    INTSource source) {

    volatile uint32_t* IECx = (volatile uint32_t*) (&IEC0 + ((0x10 * (source / 32)) / 4));
    bool state = (bool) ((*IECx >> (source & 0x1f)) & 0x01);
    if (state != 0) {
        volatile uint32_t* IECxCLR = (volatile uint32_t*)(IECx + 1);
        *IECxCLR = 1 << (source & 0x1f);
    }
    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Restaura les interrupcions.
/// \param    source: El identificador de la interrupcio.
/// \param    state: L'estat per restaurar.
///
void halINTRestoreInterrupt(
    INTSource source,
    bool state) {
    
    if (state)
        halINTEnableInterrupt(source);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del flag d'interrupcio.
/// \param    source: El identificador de la interrupcio.
///
bool halINTGetInterruptFlag(
    INTSource source) {
        
    volatile uint32_t* IFSx = (volatile uint32_t*)(&IFS0 + ((0x10 * (source / 32)) / 4));
    return (bool)((*IFSx >> (source & 0x1f)) & 0x1);
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag d'interrupcio.
/// \param    source: El identificador de la interrupcio.
///
void halINTClearInterruptFlag(
    INTSource source) {

    volatile uint32_t* IFSx = (volatile uint32_t*)(&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t* IFSxCLR = (volatile uint32_t*)(IFSx + 1);
    *IFSxCLR = 1 << (source & 0x1f);
    *IFSxCLR;   
}
