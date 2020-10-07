#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halUART.h"



/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \param    data: Buffer de dades.
/// \param    info: Parametres d'inicialitzacio..
///
UARTHandler halUARTInitialize(
    UARTData* data,
    const UARTInitializeInfo *info) {

    UARTHandler handler = data;

    switch (info->channel) {
    	case HAL_UART_CHANNEL_1:
    		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    		handler->regs = USART1;
			break;

    	case HAL_UART_CHANNEL_2:
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			handler->regs = USART2;
    		break;

    	case HAL_UART_CHANNEL_3:
    		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    		handler->regs = USART3;
    		break;

    	case HAL_UART_CHANNEL_4:
    		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    		handler->regs = UART4;
    		break;

    	case HAL_UART_CHANNEL_5:
    		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    		handler->regs = UART5;
    		break;

    	case HAL_UART_CHANNEL_6:
    		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    		handler->regs = USART6;
			break;

    	case HAL_UART_CHANNEL_7:
    		RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
    		handler->regs = UART7;
			break;

    	case HAL_UART_CHANNEL_8:
    		RCC->APB1ENR |= RCC_APB1ENR_UART8EN;
    		handler->regs = UART8;
			break;
    }

    handler->regs->CR1 &= ~USART_CR1_UE;

    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Assigna la funcio d'interrupcio.
/// \params   function: La funcio.
/// \params   params: Els parametres.
///
void halUARTSetInterruptFunction(
	UARTHandler handler,
	UARTInterruptFunction function,
	void* params) {

	eosAssert(handler != NULL);

	handler->isrFunction = function;
	handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio.
/// \param    handler: Handler del canal.
///
void halUARTInterruptHandler(
	UARTHandler handler) {

}
