#include "eos.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Selecciona la paritat.
/// \param    regs: El bloc de registres.
/// \param    parity: La paritat.
///
static void setParity(
	USART_TypeDef *regs,
	UARTParity parity) {

	uint32_t temp = regs->CR1;

    switch (parity) {
    	case UARTParity::none:
    		temp &= ~USART_CR1_PCE;
    		break;

    	case UARTParity::even:
    		temp |= USART_CR1_PCE;
    		temp &= ~USART_CR1_PS;
    		break;

    	case UARTParity::odd:
    		temp |= USART_CR1_PCE;
    		temp |= USART_CR1_PS;
    		break;
    }

    regs->CR1 = temp;
}


static void setWordSize(
	USART_TypeDef *regs,
	unsigned size) {

	uint32_t temp = regs->CR1;
	switch (size) {
		case 7:
			temp |= USART_CR1_M1;
			temp &= ~USART_CR1_M0;
			break;

		case 8:
			temp &= ~USART_CR1_M1;
			temp &= ~USART_CR1_M0;
			break;

		case 9:
			temp &= ~USART_CR1_M1;
			temp |= USART_CR1_M0;
			break;
	}
	regs->CR1 = temp;
}


static void setStop(
	USART_TypeDef *regs,
	UARTStop stop) {

	uint32_t temp = regs->CR2;
    switch (stop) {
    	case UARTStop::stop0_5:
    		temp &= ~USART_CR2_STOP_1;
    		temp |= USART_CR2_STOP_0;
    		break;

    	case UARTStop::stop1:
    		temp &= ~USART_CR2_STOP_1;
    		temp &= ~USART_CR2_STOP_0;
    		break;

    	case UARTStop::stop1_5:
    		temp |= USART_CR2_STOP_1;
    		temp |= USART_CR2_STOP_0;
    		break;

    	case UARTStop::stop2:
    		temp |= USART_CR2_STOP_1;
    		temp &= ~USART_CR2_STOP_0;
    		break;
    }
    regs->CR2 = temp;
}


void htl::UART_init(
	USART_TypeDef *regs,
	UARTWord word,
	UARTParity parity,
	UARTStop stop) {

	// Desactiva el modul
	//
	regs->CR1 &= ~USART_CR1_UE;

	// Asigna els bits de paraula
	//
	unsigned ws = 7 + unsigned(word);
	if (parity != UARTParity::none)
		ws++;
	setWordSize(regs, ws);

	// Asigna els bits del stop
	//
	setStop(regs, stop);

	// Asigna la paritat
	//
	setParity(regs, parity);

	// Activa el modul
	//
	regs->CR1 |= USART_CR1_UE;
}
