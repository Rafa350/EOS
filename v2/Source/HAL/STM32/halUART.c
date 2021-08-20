/// \file     halUART.c
/// \author   Rafael Serrano (rsr.openware@gmail.com)
/// \brief    Gestio de la UART
///
#include "HAL/hal.h"
#include "HAL/STM32/halUART.h"
#include "HAL/STM32/halSYS.h"

#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


#define __VERIFY_CHANNEL(channel) eosAssert((channel >= HAL_UART_CHANNEL_1) && (channel <= HAL_UART_CHANNEL_8))
#define __VERIFY_DEVICE(device)   eosAssert(IS_UART_INSTANCE(device))
#define __VERIFY_HANDLER(handler) eosAssert(handler != NULL)


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: El identificador del dispositiu.
/// \return   El dispositiu.
///
static inline USART_TypeDef* getDevice(
	halUARTChannel channel) {

	__VERIFY_CHANNEL(channel);

	static USART_TypeDef* const devices[] = {
		USART1,
		USART2,
		USART3,
		UART4,
		UART5,
		USART6,
		UART7,
		UART8
	};

	return devices[channel];
}


/// ----------------------------------------------------------------------
/// \brief    Activa clock del dispositiu.
/// \param    device: El dispositiu.
///
static void enableDeviceClock(
	USART_TypeDef* device) {

	__VERIFY_DEVICE(device);

    switch ((uint32_t) device) {
    	case USART1_BASE:
    		__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
			break;

    	case USART2_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
    		break;

    	case USART3_BASE:
    		__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_USART3EN);
    		break;

    	case UART4_BASE:
    		__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_UART4EN);
    		break;

    	case UART5_BASE:
    		__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_UART5EN);
    		break;

    	case USART6_BASE:
    		__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_USART6EN);
			break;

    	case UART7_BASE:
    		__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_UART7EN);
			break;

    	case UART8_BASE:
    		__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_UART8EN);
			break;
    }

    __DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el clock del dispositiu.
/// \param    device: El dispositiu.
///
static void disableDeviceClock(
	USART_TypeDef* device) {

	__VERIFY_DEVICE(device);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el rellotge asignat al generador de bauds.
/// \param    device: El dispositiu.
/// \return   La opcio corresponent al rellotge.
///
uint32_t getClockSourceOption(
	USART_TypeDef* device) {

	__VERIFY_DEVICE(device);

	uint32_t sclk = 0;
    switch ((uint32_t)device) {
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

    static const uint32_t options[] = {
    	HAL_UART_CLOCK_PCLK,
		HAL_UART_CLOCK_SYSCLK,
		HAL_UART_CLOCK_HSI,
		HAL_UART_CLOCK_LSE
    };

    return options[sclk & 0x03];
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un dispositiu UART.
/// \param    device: El dispositiu.
/// \param    options: Opcions de configuracio.
/// \param    rate: Valor pel calcul de la velocitat
///
static void setupDevice(
	USART_TypeDef* device,
	halUARTOptions options,
	uint32_t baud) {

	__VERIFY_DEVICE(device);

	uint32_t temp;

	// Desactiva el modul, per poder configurar-lo
    //
    __clear_bit_msk(device->CR1, USART_CR1_UE);

    // Configura el registre CR1 (Control Register 1)
    //
    temp = device->CR1;

    if ((options & HAL_UART_OVERSAMPLING_mask) == HAL_UART_OVERSAMPLING_8)
    	__set_bit_msk(temp, USART_CR1_OVER8);
    else
    	__clear_bit_msk(temp, USART_CR1_OVER8);

    __set_bit_msk(temp, USART_CR1_RE);      // Habilita recepcio
    __set_bit_msk(temp, USART_CR1_TE);      // Habilita transmissio

    int len = 7 + ((options & HAL_UART_LEN_mask) >> HAL_UART_LEN_pos);
    if ((options & HAL_UART_PARITY_mask) != HAL_UART_PARITY_NONE)
    	len++;
    switch (len) {
    	case 7:
    		__set_bit_msk(temp, USART_CR1_M1);
    		__clear_bit_msk(temp, USART_CR1_M0);
    		break;

    	default:
    	case 8:
    		__clear_bit_msk(temp, USART_CR1_M1);
    		__clear_bit_msk(temp, USART_CR1_M0);
    		break;

    	case 9:
    		__clear_bit_msk(temp, USART_CR1_M1);
    		__set_bit_msk(temp, USART_CR1_M0);
    		break;
    }

    switch (options & HAL_UART_PARITY_mask) {
    	default:
    	case HAL_UART_PARITY_NONE:
    		__clear_bit_msk(temp, USART_CR1_PCE);
    		break;

    	case HAL_UART_PARITY_EVEN:
    		__set_bit_msk(temp, USART_CR1_PCE);
    		__clear_bit_msk(temp, USART_CR1_PS);
    		break;

    	case HAL_UART_PARITY_ODD:
    		__set_bit_msk(temp, USART_CR1_PCE);
    		__set_bit_msk(temp, USART_CR1_PS);
    		break;
    }

    device->CR1 = temp;

    // Configura el registre CR2 (Control Register 2)
    //
    __clear_bit_msk(device->CR2, USART_CR2_LINEN | USART_CR2_CLKEN);

    switch (options & HAL_UART_STOP_mask) {
    	case HAL_UART_STOP_HALF:
    		device->CR2 &= ~USART_CR2_STOP_1;
    		device->CR2 |= USART_CR2_STOP_0;
    		break;

    	default:
    	case HAL_UART_STOP_1:
    		device->CR2 &= ~USART_CR2_STOP_1;
    		device->CR2 &= ~USART_CR2_STOP_0;
    		break;

    	case HAL_UART_STOP_1HALF:
    		device->CR2 |= USART_CR2_STOP_1;
    		device->CR2 |= USART_CR2_STOP_0;
    		break;

    	case HAL_UART_STOP_2:
    		device->CR2 |= USART_CR2_STOP_1;
    		device->CR2 &= ~USART_CR2_STOP_0;
    		break;
    }

    // Configura el registre CR3 (Control Register 3)
    //
    __clear_bit_msk(device->CR3, USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

    // Configura el regisre BRR (Baud Rate Register)
    //
    switch (options & HAL_UART_BAUD_mask) {
    	case HAL_UART_BAUD_1200:
    		baud = 1200;
    		break;

    	case HAL_UART_BAUD_2400:
    		baud = 2400;
    		break;

    	case HAL_UART_BAUD_4800:
    		baud = 4800;
    		break;

    	case HAL_UART_BAUD_9600:
    		baud = 9600;
    		break;

    	case HAL_UART_BAUD_19200:
    		baud = 19200;
    		break;

    	case HAL_UART_BAUD_38400:
    		baud = 38400;
    		break;

    	case HAL_UART_BAUD_57600:
    		baud = 57600;
    		break;

    	case HAL_UART_BAUD_115200:
    		baud = 115200;
    		break;

    	default:
    	case HAL_UART_BAUD_RATE:
    		break;
    }

    uint32_t fclk;
    switch (options & HAL_UART_CLOCK_mask) {
    	default:
    	case HAL_UART_CLOCK_PCLK:
    		if ((device == USART1) || (device == USART6))
    			fclk = halSYSGetPeripheralClock2Frequency();
    		else
    			fclk = halSYSGetPeripheralClock1Frequency();
    		break;

    	case HAL_UART_CLOCK_SYSCLK:
    		fclk = halSYSGetSystemClockFrequency();
    		break;

    	case HAL_UART_CLOCK_HSI:
    		fclk = HSI_VALUE;
    		break;

    	case HAL_UART_CLOCK_LSE:
    		fclk = LSE_VALUE;
    		break;
    }

    uint32_t div;
    if ((options & HAL_UART_BAUD_mask) == HAL_UART_BAUD_DIV)
    	div = baud;
    else {
        if ((options & HAL_UART_OVERSAMPLING_mask) == HAL_UART_OVERSAMPLING_8)
        	div = (fclk + fclk + (baud / 2)) / baud;
        else
           	div = (fclk + (baud / 2)) / baud;
    }
    if ((options & HAL_UART_OVERSAMPLING_mask) == HAL_UART_OVERSAMPLING_8) {
        uint32_t temp = (uint16_t)(div & 0xFFF0U);
        temp |= (uint16_t)((div & (uint16_t)0x000FU) >> 1U);
        device->BRR = temp;
    }
    else
    	device->BRR = div;

    // Torna a activar el modul
    //
    __set_bit_msk(device->CR1, USART_CR1_UE);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \param    data: Buffer de dades.
/// \param    info: Parametres d'inicialitzacio.
///
halUARTHandler halUARTInitialize(
    halUARTData* data,
    const halUARTSettings* settings) {

	eosAssert(data != NULL);
	eosAssert(settings != NULL);

    USART_TypeDef* device = getDevice(settings->channel);

    enableDeviceClock(device);

    uint32_t options = settings->options;
    if ((options & HAL_UART_CLOCK_mask) == HAL_UART_CLOCK_AUTO) {
    	__clear_bit_msk(options, HAL_UART_CLOCK_mask);
    	__set_bit_msk(options, getClockSourceOption(device));
    }
    setupDevice(device, options, settings->baud);

    halUARTHandler handler = data;
    handler->device = device;
    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
/// \param    handler: El handler del dispositiu.
///
void halUARTDeinitialize(
	halUARTHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	USART_TypeDef* device = handler->device;

	__clear_bit_msk(device->CR1, USART_CR1_UE);
	disableDeviceClock(device);
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un byte.
/// \param    handler: El handler del dispositiu.
/// \param    data: El byte a transmetre.
///
void halUARTSend(
	halUARTHandler handler,
	uint8_t data) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	handler->device->TDR = data;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un byte
/// \param    handler: Handler del dispositiu.
/// \return   El byte lleigit.
///
uint8_t halUARTReceive(
	halUARTHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	return handler->device->RDR;
}


/// ----------------------------------------------------------------------
/// \brief    Assigna la funcio d'interrupcio.
/// \param    handler: Handler del dispositiu.
/// \param    function: La funcio.
/// \param    params: Els parametres.
///
void halUARTSetInterruptFunction(
	halUARTHandler handler,
	halUARTInterruptFunction function,
	void* params) {

	__VERIFY_HANDLER(handler);

	handler->isrFunction = function;
	handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les interrupcions.
/// \param    handler: Handler del dispositiu.
/// \param    events: Interrupcions a habilitar.
///
void halUARTEnableInterrupts(
	halUARTHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);

	USART_TypeDef* device = handler->device;

	if (__check_bit_msk(events, HAL_UART_EVENT_CTS))
		__set_bit_msk(device->CR3, USART_CR3_CTSIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_BREAK))
		__set_bit_msk(device->CR2, USART_CR2_LBDIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_IDLE))
		__set_bit_msk(device->CR1, USART_CR1_IDLEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_TXEMPTY))
		__set_bit_msk(device->CR1, USART_CR1_TXEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_TXCOMPLETE))
		__set_bit_msk(device->CR1, USART_CR1_TCIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_RXFULL)) {
		// Activa RXNE i PE
		//
		__set_bit_msk(device->CR1, USART_CR1_RXNEIE);
	}

	if (__check_bit_msk(events, HAL_UART_EVENT_PARITY))
		__set_bit_msk(device->CR1, USART_CR1_PEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_ERROR)) {
		// Activa les tres interrupcions d'error PE, ORE, FE i NE
		//
		__set_bit_msk(device->CR3, USART_CR3_EIE);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les interrupcions.
/// \param    handler: Handler del dispositiu.
/// \param    events: Interupcions a deshabilitar.
///
uint32_t halUARTDisableInterrupts(
	halUARTHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);

	USART_TypeDef* device = handler->device;

	uint32_t state = 0;

	if (__check_bit_msk(device->CR3, USART_CR3_CTSIE))
		__set_bit_msk(state, HAL_UART_EVENT_CTS);

	if (__check_bit_msk(device->CR2, USART_CR2_LBDIE))
		__set_bit_msk(state, HAL_UART_EVENT_BREAK);

	if (__check_bit_msk(device->CR1, USART_CR1_IDLEIE))
		__set_bit_msk(state, HAL_UART_EVENT_IDLE);

	if (__check_bit_msk(device->CR1, USART_CR1_TXEIE))
		__set_bit_msk(state, HAL_UART_EVENT_TXEMPTY);

	if (__check_bit_msk(device->CR1, USART_CR1_TCIE))
		__set_bit_msk(state, HAL_UART_EVENT_TXCOMPLETE);

	if (__check_bit_msk(device->CR1, USART_CR1_RXNEIE)) {
		// Desactiva RXNE i PE
		//
		__set_bit_msk(state, HAL_UART_EVENT_RXFULL);
	}

	if (__check_bit_msk(device->CR1, USART_CR1_PEIE))
		__set_bit_msk(state, HAL_UART_EVENT_PARITY);

	if (__check_bit_msk(device->CR3, USART_CR3_EIE)) {
		// Desactiva les tres interrupcions d'error PE, ORE, FE i NE
		//
		__set_bit_msk(state, HAL_UART_EVENT_ERROR);
	}

	if (__check_bit_msk(events, HAL_UART_EVENT_CTS))
		__clear_bit_msk(device->CR3, USART_CR3_CTSIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_BREAK))
		__clear_bit_msk(device->CR2, USART_CR2_LBDIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_IDLE))
		__clear_bit_msk(device->CR1, USART_CR1_IDLEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_TXEMPTY))
		__clear_bit_msk(device->CR1, USART_CR1_TXEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_TXCOMPLETE))
		__clear_bit_msk(device->CR1, USART_CR1_TCIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_RXFULL))
		__clear_bit_msk(device->CR1, USART_CR1_RXNEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_PARITY))
		__clear_bit_msk(device->CR1, USART_CR1_PEIE);

	if (__check_bit_msk(events, HAL_UART_EVENT_ERROR))
		__clear_bit_msk(device->CR3, USART_CR3_EIE);

	return state;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del flag d'interrupcio.
/// \param    handler: El handler del dispositiu.
/// \param    event: El flag.
/// \return   El valor del flag.
///
bool halDMAGetInterruptFlag(
	halUARTHandler handler,
	uint32_t event) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	USART_TypeDef* device = handler->device;

	switch (event) {
		case HAL_UART_EVENT_RXFULL:
			return __check_bit_msk(device->ISR, USART_ISR_RXNE);

		case HAL_UART_EVENT_TXEMPTY:
			return __check_bit_msk(device->ISR, USART_ISR_TXE);

		case HAL_UART_EVENT_TXCOMPLETE:
			return __check_bit_msk(device->ISR, USART_ISR_TC);

		case HAL_UART_EVENT_PARITY:
			return __check_bit_msk(device->ISR, USART_ISR_PE);

		case HAL_UART_EVENT_OVERRUN:
			return __check_bit_msk(device->ISR, USART_ISR_ORE);

		case HAL_UART_EVENT_FRAMING:
			return __check_bit_msk(device->ISR, USART_ISR_FE);

		case HAL_UART_EVENT_NOISE:
			return __check_bit_msk(device->ISR, USART_ISR_NE);

		default:
			return false;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Borra els flags d'interrupcio
/// \param    handler: Handler del dispositiu.
/// \param    events: Els flags a borrar
///
void halUARTClearInterruptFlags(
	halUARTHandler handler,
	uint32_t events) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	if (__check_bit_msk(events, HAL_UART_EVENT_TXCOMPLETE))
		handler->device->ICR = USART_ICR_TCCF;

	if (__check_bit_msk(events, HAL_UART_EVENT_PARITY))
		handler->device->ICR = USART_ICR_PECF;

	if (__check_bit_msk(events, HAL_UART_EVENT_OVERRUN))
		handler->device->ICR = USART_ICR_ORECF;

	if (__check_bit_msk(events, HAL_UART_EVENT_NOISE))
		handler->device->ICR = USART_ICR_NCF;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio.
/// \param    handler: Handler del dispositiu.
///
void halUARTInterruptHandler(
	halUARTHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	uint32_t isr = handler->device->ISR;
	uint32_t cr1 = handler->device->CR1;
	uint32_t cr3 = handler->device->CR3;

	// Comprova si es una interrupcio RXNE
	//
	if (__check_bit_msk(isr, USART_ISR_RXNE) &&
		__check_bit_msk(cr1, USART_CR1_RXNEIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_RXFULL);
		// El flag es borra automaticament al lleigir el registre RDR
	}

	// Comprova si es una interrupcio 'parity error'
	//
	if (__check_bit_msk(isr, USART_ISR_PE) &&
		__check_bit_msk(cr1, USART_CR1_PEIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_PARITY);
		handler->device->ICR = USART_ICR_PECF;
	}

	// Comprova si es una interrupcio 'overrun error'
	//
	if (__check_bit_msk(isr, USART_ISR_ORE) &&
		(__check_bit_msk(cr3, USART_CR3_EIE) || __check_bit_msk(cr1, USART_CR1_RXNEIE))) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_OVERRUN);
		handler->device->ICR = USART_ICR_ORECF;
	}

	// Comprova si es una interrupcio 'framing error'
	//
	if (__check_bit_msk(isr, USART_ISR_FE) &&
		__check_bit_msk(cr3, USART_CR3_EIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_FRAMING);
		handler->device->ICR = USART_ICR_FECF;
	}

	// Comprova si es una interrupcio 'noise error'
	//
	if (__check_bit_msk(isr, USART_ISR_NE) &&
		__check_bit_msk(cr3, USART_CR3_EIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_NOISE);
		handler->device->ICR = USART_ICR_NCF;
	}

	// Comprova si es una interrupcio TXE
	//
	if (__check_bit_msk(isr, USART_ISR_TXE) &&
		__check_bit_msk(cr1, USART_CR1_TXEIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_TXEMPTY);
		// El flag es borra automaticament al escriure el registre TDR
	}

	// Comprova si es una interrupcio TC
	//
	if (__check_bit_msk(isr, USART_ISR_TC) &&
		__check_bit_msk(cr1, USART_CR1_TCIE)) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams, HAL_UART_EVENT_TXCOMPLETE);
		handler->device->ICR = USART_ICR_TCCF;
	}
}
