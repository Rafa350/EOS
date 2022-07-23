#include "eos.h"
#include "HAL/halSYS.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Selecciona el protocol de comunicacio.
/// \param    regs: El bloc de registres.
/// \param    word: Lers opcions de paraula.
/// \param    parity: Les opcions de paritat.
/// \param    stop: Les opcions de parada.
///
void htl::UART_setProtocol(
	USART_TypeDef *regs,
	UARTWord word,
	UARTParity parity,
	UARTStop stop) {

	uint32_t temp;

	// Desactiva el modul
	//
	regs->CR1 &= ~USART_CR1_UE;

	// Configura el registre CR1 (Control Register 1)
	// -Tamany de paraula
	// -Paritat
	//
	temp = regs->CR1;

	unsigned ws = 7 + unsigned(word);
	if (parity != UARTParity::none)
		ws++;
	switch (ws) {
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

	// Configura el registre CR2 (Control Register 2)
	// -Bits de parada
	//
	temp = regs->CR2;
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

    // Configura el registre CR3 (Control Register 3)
    //
    regs->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
}


/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio
/// \param    regs: El bloc de registres.
/// \param    baudMode: Les opcions del baud rate
/// \param    clockMode: Les opcions de clocking.
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
///
void htl::UART_setTimming(
	USART_TypeDef *regs,
	UARTBaudMode baudMode,
	UARTClockMode clockMode,
	unsigned rate,
	UARTOverSampling overSampling) {

	switch (baudMode) {
    	case UARTBaudMode::b1200:
    		rate = 1200;
    		break;

    	case UARTBaudMode::b2400:
    		rate = 2400;
    		break;

    	case UARTBaudMode::b4800:
    		rate = 4800;
    		break;

    	case UARTBaudMode::b9600:
    		rate = 9600;
    		break;

    	case UARTBaudMode::b19200:
    		rate = 19200;
    		break;

    	case UARTBaudMode::b38400:
    		rate = 38400;
    		break;

    	case UARTBaudMode::b57600:
    		rate = 57600;
    		break;

    	case UARTBaudMode::b115200:
    		rate = 115200;
    		break;

    	default:
    		break;
    }

    uint32_t fclk;
    switch (clockMode) {
    	default:
    	case UARTClockMode::pclk:
    		if ((uint32_t(regs) == USART1_BASE) ||
    			(uint32_t(regs) == USART6_BASE))
    			fclk = halSYSGetPeripheralClock2Frequency();
    		else
    			fclk = halSYSGetPeripheralClock1Frequency();
    		break;

    	case UARTClockMode::sysclk:
    		fclk = halSYSGetSystemClockFrequency();
    		break;

    	case UARTClockMode::hsi:
    		fclk = HSI_VALUE;
    		break;

    	case UARTClockMode::lse:
    		fclk = LSE_VALUE;
    		break;
    }

    uint32_t div;
    if (baudMode == UARTBaudMode::div)
    	div = rate;
    else {
        if (overSampling == UARTOverSampling::os8)
        	div = (fclk + fclk + (rate / 2)) / rate;
        else
           	div = (fclk + (rate / 2)) / rate;
    }

    if (overSampling == UARTOverSampling::os8) {
        uint32_t temp = (uint16_t)(div & 0xFFF0U);
        temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
        regs->BRR = temp;
    }
    else
    	regs->BRR = div;

}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions.
/// \param    regs: El bnloc de registres.
/// \param    event: El event.
///
void htl::UART_enableInterrupt(
	USART_TypeDef *regs,
	UARTEvent event) {

	switch (event) {
		case UARTEvent::cts:
			regs->CR3 |= USART_CR3_CTSIE;
			break;

		case UARTEvent::brk:
			regs->CR2 |= USART_CR2_LBDIE;
			break;

		case UARTEvent::idle:
			regs->CR1 |= USART_CR1_IDLEIE;
			break;

		case UARTEvent::txEmpty:
			regs->CR1 |= USART_CR1_TXEIE;
			break;

		case UARTEvent::txComplete:
			regs->CR1 |= USART_CR1_TCIE;
			break;

		case UARTEvent::rxFull:
			regs->CR1 |= USART_CR1_RXNEIE;
			break;

		case UARTEvent::parity:
			regs->CR1 |= USART_CR1_PEIE;
			break;

		case UARTEvent::framming:
			break;

		case UARTEvent::error:
			regs->CR3 |= USART_CR3_EIE;
			break;
	}
}


bool htl::UART_disableInterrupt(
	USART_TypeDef *regs,
	UARTEvent event) {

	bool state = false;

	switch (event) {
		case UARTEvent::cts:
			state = regs->CR3 & USART_CR3_CTSIE;
			regs->CR3 &= ~USART_CR3_CTSIE;
			break;

		case UARTEvent::brk:
			state = regs->CR2 & USART_CR2_LBDIE;
			regs->CR2 &= ~USART_CR2_LBDIE;
			break;

		case UARTEvent::idle:
			state = regs->CR1 & USART_CR1_IDLEIE;
			regs->CR1 &= ~USART_CR1_IDLEIE;
			break;

		case UARTEvent::txEmpty:
			state = regs->CR1 & USART_CR1_TXEIE;
			regs->CR1 &= ~USART_CR1_TXEIE;
			break;

		case UARTEvent::txComplete:
			state = regs->CR1 & USART_CR1_TCIE;
			regs->CR1 &= ~USART_CR1_TCIE;
			break;

		case UARTEvent::rxFull:
			state = regs->CR1 & USART_CR1_RXNEIE;
			regs->CR1 &= ~USART_CR1_RXNEIE;
			break;

		case UARTEvent::parity:
			state = regs->CR1 & USART_CR1_PEIE;
			regs->CR1 &= ~USART_CR1_PEIE;
			break;

		case UARTEvent::framming:
			break;

		case UARTEvent::error:
			state = regs->CR3 & USART_CR3_EIE;
			regs->CR3 &= ~USART_CR3_EIE;
			break;
	}

	return state;
}

