#include "eos.h"
#include "HAL/PIC32/halINT.h"


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritat al vector.
/// \param    vector: El vector.
///
void halINTSetInterruptVectorPriority(
    uint32_t vector,
    uint32_t priority,
    uint32_t subPriority) {

    uint32_t mask;
    uint32_t position;
    
    volatile uint32_t* IPCx = (volatile uint32_t*)(&IPC0 + ((0x10 * (vector >> 2)) >> 2));
        
    mask = 0x07 << ((vector & 0x03) * 8 + 2);
    position = (vector & 0x03) * 8 + 2;
    *IPCx &= ~mask;
    *IPCx |= (priority << position) & mask;

    mask = 0x03 << ((vector & 0x03) * 8);
    position = (vector & 0x03) * 8;
    *IPCx &= ~mask; 
    *IPCx |= (subPriority << position) & mask; 
}


/// ----------------------------------------------------------------------
/// \brief    Activa la font d'interrupcions.
/// \param    source: El identificador de la font.
///
void halINTEnableInterruptSource(
    uint32_t source) {
    
    volatile uint32_t* IECx = (volatile uint32_t*) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t* IECxSET = (volatile uint32_t *)(IECx + 2);
    *IECxSET = 1 << (source & 0x1f);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva la font d'interrupcions.
/// \param    source: El identificador de la font
/// \return   El estat previ. Util per si cal restaurar l'estat.
///
bool halINTDisableInterruptSource(
    uint32_t source) {

    volatile uint32_t* IECx = (volatile uint32_t*) (&IEC0 + ((0x10 * (source / 32)) / 4));
    bool state = (bool) ((*IECx >> (source & 0x1f)) & 0x01);
    if (!state) {
        volatile uint32_t* IECxCLR = (volatile uint32_t*)(IECx + 1);
        *IECxCLR = 1 << (source & 0x1f);
    }
    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Restaura la font interrupcions.
/// \param    source: El identificador de la font.
/// \param    state: L'estat per restaurar.
///
void halINTRestoreInterruptSource(
    uint32_t source,
    bool state) {
    
    if (state)
        halINTEnableInterruptSource(source);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del flag d'interrupcio.
/// \param    source: El identificador de la interrupcio.
///
bool halINTGetInterruptSourceFlag(
    uint32_t source) {
        
    volatile uint32_t* IFSx = (volatile uint32_t*)(&IFS0 + ((0x10 * (source / 32)) / 4));
    return (bool)((*IFSx >> (source & 0x1f)) & 0x1);
}


/// ----------------------------------------------------------------------
/// \brief    Borra el flag d'interrupcio.
/// \param    source: El identificador de la interrupcio.
///  
void halINTClearInterruptSourceFlag(
    uint32_t source) {

    volatile uint32_t* IFSx = (volatile uint32_t*)(&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t* IFSxCLR = (volatile uint32_t*)(IFSx + 1);
    *IFSxCLR = 1 << (source & 0x1f);  
}
