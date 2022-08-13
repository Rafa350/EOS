#include "HTL/htl.h"
#include "HAL/halSYS.h"
#include "HTL/STM32/htlUART.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Obte el rellotge asignat al generador de bauds.
/// \param    regs: El bloc de registres
/// \return   La opcio corresponent al rellotge.
///
static UARTClockSource getClockSource(
	USART_TypeDef *regs) {

	uint8_t sclk = 0;
    switch ((uint32_t)regs) {
    	case USART1_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART1SEL) >> RCC_DCKCFGR2_USART1SEL_Pos;
			break;

    	case USART2_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART2SEL) >> RCC_DCKCFGR2_USART2SEL_Pos;
    		break;

    	case USART3_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART3SEL) >> RCC_DCKCFGR2_USART3SEL_Pos;
    		break;

    	case UART4_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART4SEL) >> RCC_DCKCFGR2_UART4SEL_Pos;
    		break;

    	case UART5_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART5SEL) >> RCC_DCKCFGR2_UART5SEL_Pos;
    		break;

    	case USART6_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART6SEL) >> RCC_DCKCFGR2_USART6SEL_Pos;
			break;

    	case UART7_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART7SEL) >> RCC_DCKCFGR2_UART7SEL_Pos;
			break;

    	case UART8_BASE:
    		sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART8SEL) >> RCC_DCKCFGR2_UART8SEL_Pos;
			break;
    }

    switch (sclk & 0x03) {
    	default:
    	case 0: return UARTClockSource::pclk;
    	case 1: return UARTClockSource::sysclk;
    	case 2: return UARTClockSource::hsi;
    	case 3: return UARTClockSource::lse;
    }
}


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

	uint32_t tmp;

	// Configura el registre CR1 (Control Register 1)
	// -Tamany de paraula
	// -Paritat
	//
	tmp = regs->CR1;

	unsigned ws = 7 + unsigned(word);
	if (parity != UARTParity::none)
		ws++;
	switch (ws) {
		case 7:
			tmp |= USART_CR1_M1;
			tmp &= ~USART_CR1_M0;
			break;

		case 8:
			tmp &= ~USART_CR1_M1;
			tmp &= ~USART_CR1_M0;
			break;

		case 9:
			tmp &= ~USART_CR1_M1;
			tmp |= USART_CR1_M0;
			break;
	}

    switch (parity) {
    	case UARTParity::none:
    		tmp &= ~USART_CR1_PCE;
    		break;

    	case UARTParity::even:
    		tmp |= USART_CR1_PCE;
    		tmp &= ~USART_CR1_PS;
    		break;

    	case UARTParity::odd:
    		tmp |= USART_CR1_PCE;
    		tmp |= USART_CR1_PS;
    		break;
    }
	regs->CR1 = tmp;

	// Configura el registre CR2 (Control Register 2)
	// -Bits de parada
	//
	tmp = regs->CR2;
    switch (stop) {
    	case UARTStop::_0p5:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case UARTStop::_1:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;

    	case UARTStop::_1p5:
    		tmp |= USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case UARTStop::_2:
    		tmp |= USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;
    }
    regs->CR2 = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio
/// \param    regs: El bloc de registres.
/// \param    baudMode: Les opcions del baud rate
/// \param    clockSource: Les opcions de clocking.
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
///
void htl::UART_setTimming(
	USART_TypeDef *regs,
	UARTBaudMode baudMode,
	UARTClockSource clockSource,
	unsigned rate,
	UARTOverSampling overSampling) {

	switch (baudMode) {
    	case UARTBaudMode::_1200:
    		rate = 1200;
    		break;

    	case UARTBaudMode::_2400:
    		rate = 2400;
    		break;

    	case UARTBaudMode::_4800:
    		rate = 4800;
    		break;

    	case UARTBaudMode::_9600:
    		rate = 9600;
    		break;

    	case UARTBaudMode::_19200:
    		rate = 19200;
    		break;

    	case UARTBaudMode::_38400:
    		rate = 38400;
    		break;

    	case UARTBaudMode::_57600:
    		rate = 57600;
    		break;

    	case UARTBaudMode::_115200:
    		rate = 115200;
    		break;

    	default:
    		break;
    }

    uint32_t fclk;
    if (clockSource == UARTClockSource::automatic)
    	clockSource = getClockSource(regs);
    switch (clockSource) {
    	default:
    	case UARTClockSource::pclk:
    		if ((uint32_t(regs) == USART1_BASE) ||
    			(uint32_t(regs) == USART6_BASE))
    			fclk = halSYSGetPeripheralClock2Frequency();
    		else
    			fclk = halSYSGetPeripheralClock1Frequency();
    		break;

    	case UARTClockSource::sysclk:
    		fclk = halSYSGetSystemClockFrequency();
    		break;

    	case UARTClockSource::hsi:
    		fclk = HSI_VALUE;
    		break;

    	case UARTClockSource::lse:
    		fclk = LSE_VALUE;
    		break;
    }

    uint32_t div;
    if (baudMode == UARTBaudMode::div)
    	div = rate;
    else {
        if (overSampling == UARTOverSampling::_8)
        	div = (fclk + fclk + (rate / 2)) / rate;
        else
           	div = (fclk + (rate / 2)) / rate;
    }

    if (overSampling == UARTOverSampling::_8) {
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

		case UARTEvent::rxNotEmpty:
			regs->CR1 |= USART_CR1_RXNEIE;
			break;

		case UARTEvent::parity:
			regs->CR1 |= USART_CR1_PEIE;
			break;

		case UARTEvent::noise:
		case UARTEvent::overrun:
		case UARTEvent::framming:
			regs->CR3 |= USART_CR3_EIE;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita les interrupcions
/// \param    regs: El bloc de registres.
/// \param    event: El event.
///
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

		case UARTEvent::rxNotEmpty:
			state = regs->CR1 & USART_CR1_RXNEIE;
			regs->CR1 &= ~USART_CR1_RXNEIE;
			break;

		case UARTEvent::parity:
			state = regs->CR1 & USART_CR1_PEIE;
			regs->CR1 &= ~USART_CR1_PEIE;
			break;

		case UARTEvent::framming:
			break;
	}

	return state;
}

