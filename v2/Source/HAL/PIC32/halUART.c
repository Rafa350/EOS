#include "eos.h"
#include "HAL/PIC32/halSYS.h"
#include "HAL/PIC32/halUART.h"

#include "peripheral/int/plib_int.h"
#include "Peripheral/usart/plib_usart.h"


/// ----------------------------------------------------------------------
/// \brief    Obte el identificador del modul.
/// \param    module: El modul UART.
/// \return   El identificador 'Harmony' del modul.
///
static USART_MODULE_ID getHarmonyID(
    UARTModule module) {
    
    static const USART_MODULE_ID idTable[] = {
        USART_ID_1,
#ifdef _UART2        
        USART_ID_2,
#else
        0,        
#endif        
#ifdef _UART3
        USART_ID_3,
#else
        0,        
#endif        
#ifdef _UART4        
        USART_ID_4,
#else
        0,        
#endif        
#ifdef _UART5        
        USART_ID_5,
#else
        0,        
#endif        
#ifdef _UART6        
        USART_ID_6
#else
        0
#endif        
    };
    
    return idTable[module];
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \param    info: Parametres d'inicialitzacio..
///
void halUARTInitialize(
    const UARTInitializeInfo *info) {
    
    USART_MODULE_ID id = getHarmonyID(info->module);
    
    PLIB_USART_BaudRateSet(id, halSYSGetSystemClockFrequency(), info->baudRate);
    //PLIB_USART_SyncModeSelect(id, USART_ASYNC_MODE);
    PLIB_USART_LineControlModeSelect(id, USART_8N1);
    PLIB_USART_Enable(id);
}