#include "HTL/htl.h"
#include "HAL/halSYS.h"
#include "HTL/STM32/htlUART.h"
#include "stm32f0xx_hal.h"


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
		#ifdef HTL_UART1_EXIST
			case USART1_BASE:
				#if defined(EOS_PLATFORM_STM32F0)
					sclk = (RCC->CFGR3 & RCC_CFGR3_USART1SW) >> RCC_CFGR3_USART1SW_Pos;
				#else
					sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART1SEL) >> RCC_DCKCFGR2_USART1SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART2_EXIST
			case USART2_BASE:
				#if defined(EOS_PLATFORM_STM32F0)
					sclk = 0;
				#else
					sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART2SEL) >> RCC_DCKCFGR2_USART2SEL_Pos;
				#endif
				break;
		#endif

		#ifdef HTL_UART3_EXIST
			case USART3_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART3SEL) >> RCC_DCKCFGR2_USART3SEL_Pos;
				break;
		#endif

		#ifdef HTL_UART4_EXIST
			case UART4_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART4SEL) >> RCC_DCKCFGR2_UART4SEL_Pos;
				break;
		#endif

		#ifdef HTL_UART5_EXIST
			case UART5_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART5SEL) >> RCC_DCKCFGR2_UART5SEL_Pos;
				break;
		#endif

		#ifdef HTL_UART6_EXIST
			case USART6_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_USART6SEL) >> RCC_DCKCFGR2_USART6SEL_Pos;
				break;
		#endif

		#ifdef HTL_UART7_EXIST
			case UART7_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART7SEL) >> RCC_DCKCFGR2_UART7SEL_Pos;
				break;
		#endif

		#ifdef HTL_UART8_EXIST
			case UART8_BASE:
				sclk = (RCC->DCKCFGR2 & RCC_DCKCFGR2_UART8SEL) >> RCC_DCKCFGR2_UART8SEL_Pos;
				break;
		#endif
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
/// \param    wordBits: Lers opcions de paraula.
/// \param    parity: Les opcions de paritat.
/// \param    stopBits: Les opcions de parada.
///
void UARTBase_x::setProtocol(
	USART_TypeDef *regs,
	UARTWordBits wordBits,
	UARTParity parity,
	UARTStopBits stopBits,
	UARTHandsake handsake) {

	uint32_t tmp;

	// Configura el registre CR1 (Control Register 1)
	// -Tamany de paraula
	// -Paritat
	//
	tmp = regs->CR1;

	switch (7 + uint32_t(wordBits) + (parity == UARTParity::none ? 0 : 1)) {
		#if HTL_UART_7BIT_SUPPORT == 1
			case 7:
				tmp |= USART_CR1_M1;
				tmp &= ~USART_CR1_M0;
				break;
		#endif

		case 8:
			#if HTL_UART_7BIT_SUPPORT == 1
				tmp &= ~USART_CR1_M1;
				tmp &= ~USART_CR1_M0;
			#else
				tmp &= ~USART_CR1_M;
			#endif
			break;

		case 9:
			#if HTL_UART_7BIT_SUPPORT == 1
				tmp &= ~USART_CR1_M1;
				tmp |= USART_CR1_M0;
			#else
				tmp |= USART_CR1_M;
			#endif
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
	// -Habilita del timeout en recepcio
	//
	tmp = regs->CR2;
    switch (stopBits) {
    	case UARTStopBits::_0p5:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case UARTStopBits::_1:
    		tmp &= ~USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;

    	case UARTStopBits::_1p5:
    		tmp |= USART_CR2_STOP_1;
    		tmp |= USART_CR2_STOP_0;
    		break;

    	case UARTStopBits::_2:
    		tmp |= USART_CR2_STOP_1;
    		tmp &= ~USART_CR2_STOP_0;
    		break;
    }
	tmp |= USART_CR2_RTOEN;
    regs->CR2 = tmp;

    // Configura el registre CR3
    // -Opcions CTS
    // -Opcions RST
    //
    tmp = regs->CR3;
    switch (handsake) {
		case UARTHandsake::none:
			tmp &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
			break;

		case UARTHandsake::ctsrts:
			tmp |= (USART_CR3_RTSE | USART_CR3_CTSE);
			break;
	}
    regs->CR3 = tmp;

    // El timeout en recepcio
    //
    regs->RTOR = 11 * 100;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna els valor de temporitzacio
/// \param    regs: El bloc de registres.
/// \param    baudMode: Les opcions del baud rate
/// \param    clockSource: Les opcions de clocking.
/// \param    rate: El valor de velocitat.
/// \param    overSampling: Tipus de mostreig
///
void UARTBase_x::setTimming(
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
			#if defined(STM32F4) || defined(STM32F7)
    		if ((uint32_t(regs) == USART1_BASE) ||
    			(uint32_t(regs) == USART6_BASE))
    			fclk = halSYSGetPeripheralClock2Frequency();
    		else
			#endif
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
