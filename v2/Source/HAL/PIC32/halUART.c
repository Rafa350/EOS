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
static inline USART_MODULE_ID getHarmonyID(
    halUARTChannel module) {

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
/// \param    data: Buffer de dades.
/// \param    info: Parametres d'inicialitzacio..
///
halUARTHandler halUARTInitialize(
    halUARTData* data,
    const halUARTSettings* settings) {

    halUARTHandler handler = data;

    USART_MODULE_ID id = getHarmonyID(settings->channel);

    PLIB_USART_BaudRateSet(id, halSYSGetSystemClockFrequency(), settings->baudRate);
    //PLIB_USART_SyncModeSelect(id, USART_ASYNC_MODE);
    PLIB_USART_LineControlModeSelect(id, USART_8N1);
    PLIB_USART_Enable(id);

    return handler;
}