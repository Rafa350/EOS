#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halUART.h"
#include "HAL/STM32/halSYS.h"


#define __VERIFY_CHANNEL(channel) eosAssert((channel >= HAL_UART_CHANNEL_1) && (channel <= HAL_UART_CHANNEL_8))
#define __VERIFY_DEVICE(device)   eosAssert(IS_UART_INSTANCE(device))


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: El identificador del dispositiu.
/// \return   El dispositiu.
///
static inline USART_TypeDef* getDevice(
	UARTChannel channel) {

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
    		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			__DSB();
			break;

    	case USART2_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			__DSB();
    		break;

    	case USART3_BASE:
    		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			__DSB();
    		break;

    	case UART4_BASE:
    		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
			__DSB();
    		break;

    	case UART5_BASE:
    		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
			__DSB();
    		break;

    	case USART6_BASE:
    		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
			__DSB();
			break;

    	case UART7_BASE:
    		RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
			__DSB();
			break;

    	case UART8_BASE:
    		RCC->APB1ENR |= RCC_APB1ENR_UART8EN;
			__DSB();
			break;
    }
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
	UARTOptions options,
	uint32_t baud) {

	__VERIFY_DEVICE(device);

	// Desactiva el modul, per poder configurar-lo
    //
    device->CR1 &= ~USART_CR1_UE;

    // Configura els valors inicials
    //
    device->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
    device->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

    // Configura el oversampling
    //
    if ((options & HAL_UART_OVERSAMPLING_mask) == HAL_UART_OVERSAMPLING_8)
    	device->CR1 |= USART_CR1_OVER8;
    else
    	device->CR1 &= ~USART_CR1_OVER8;

    // Configura la longitut de paraula
    //
    switch (options & HAL_UART_LEN_mask) {
    	case HAL_UART_LEN_7:
    		device->CR1 |= USART_CR1_M1;
    		device->CR1 &= ~USART_CR1_M0;
    		break;

    	default:
    	case HAL_UART_LEN_8:
    		device->CR1 &= ~USART_CR1_M1;
    		device->CR1 &= ~USART_CR1_M0;
    		break;

    	case HAL_UART_LEN_9:
    		device->CR1 &= ~USART_CR1_M1;
    		device->CR1 |= USART_CR1_M0;
    		break;
    }

    // Configura els bits de parada
    //
    switch (options & HAL_UART_STOP_mask) {
    	case HAL_UART_STOP_05:
    		device->CR2 &= ~USART_CR2_STOP_1;
    		device->CR2 |= USART_CR2_STOP_0;
    		break;

    	default:
    	case HAL_UART_STOP_10:
    		device->CR2 &= ~USART_CR2_STOP_1;
    		device->CR2 &= ~USART_CR2_STOP_0;
    		break;

    	case HAL_UART_STOP_15:
    		device->CR2 |= USART_CR2_STOP_1;
    		device->CR2 |= USART_CR2_STOP_0;
    		break;

    	case HAL_UART_STOP_20:
    		device->CR2 |= USART_CR2_STOP_1;
    		device->CR2 &= ~USART_CR2_STOP_0;
    		break;
    }

    // Configura la paritat
    //
    switch (options & HAL_UART_PARITY_mask) {
    	default:
    	case HAL_UART_PARITY_NONE:
    		device->CR1 &= ~USART_CR1_PCE;
    		break;

    	case HAL_UART_PARITY_EVEN:
    		device->CR1 |= USART_CR1_PCE;
    		device->CR1 &= ~USART_CR1_PS;
    		break;

    	case HAL_UART_PARITY_ODD:
    		device->CR1 |= USART_CR1_PCE;
    		device->CR1 |= USART_CR1_PS;
    		break;
    }

    // Configura la velocitat de transmissio
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

    // Configura el modus de comunicacio
    //
    device->CR1 |= USART_CR1_RE | USART_CR1_TE;

    // Activa el modul
    //
    device->CR1 |= USART_CR1_UE;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul UART.
/// \param    data: Buffer de dades.
/// \param    info: Parametres d'inicialitzacio.
///
UARTHandler halUARTInitialize(
    UARTData* data,
    const UARTInitializeInfo *info) {

	eosAssert(data != NULL);
	eosAssert(info != NULL);

    USART_TypeDef* device = getDevice(info->channel);

    enableDeviceClock(device);

    uint32_t options = info->options;
    if ((options & HAL_UART_CLOCK_mask) == HAL_UART_CLOCK_AUTO) {
    	options &= ~HAL_UART_CLOCK_mask;
    	options |= getClockSourceOption(device);
    }
    setupDevice(device, options, info->baud);

    UARTHandler handler = data;
    handler->device = device;
    handler->isrFunction = NULL;
    handler->isrParams = NULL;

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el modul.
/// \param    handler: El handler del dispositiu.
///
void halUARTDeinitialize(
	UARTHandler handler) {

	eosAssert(handler != NULL);

	handler->device->CR1 &= ~USART_CR1_UE;
}


/// ----------------------------------------------------------------------
/// \brief    Transmirteix un bloc de dades, en modus bloqueig.
/// \param    handler: El handler del dispoaitiu.
/// \param    data: El bloc de dades.
/// \param    length: Logitut del bloc.
/// \return   Numero de bytes realment transmitits.
///
uint32_t halUARTSend(
	UARTHandler handler,
	const void* data,
	uint32_t length) {

	USART_TypeDef* device = handler->device;

	// Habilita la transmissio
	//
	device->CR1 |= USART_CR1_TE;

	// Transmiteix el contingut del buffer
	//
	uint8_t* p = (uint8_t*) data;

	uint32_t count = 0;
	for (int i = 0; i < length; i++) {

		while ((device->ISR & USART_ISR_TXE) == 0) {

			// TODO Controloar el timeout
			continue;
		}

		device->TDR = *p++;
		count++;
	}

	// Espera que acabi la transmissio
	//
	while ((device->ISR & USART_ISR_TC) != USART_ISR_TC) {

		// TODO Controlar el timeout
		continue;
	}

	// Desabilita la transmissio
	//
	device->CR1 &= ~USART_CR1_TE;

	return count;
}


/// ----------------------------------------------------------------------
/// \brief    Assigna la funcio d'interrupcio.
/// \param    handler: Handler del dispositiu.
/// \param    function: La funcio.
/// \param    params: Els parametres.
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
/// \brief    Habilita les interrupcions.
/// \param    handler: Handler del dispositiu.
/// \param    events: Interrupcios a habiolitar.
///
void halUARTEnableInterrupts(
	UARTHandler handler,
	uint32_t events) {

	eosAssert(handler != NULL);

	USART_TypeDef* device = handler->device;

	if ((events & HAL_UART_EVENT_CTS) == HAL_UART_EVENT_CTS)
		device->CR3 |= USART_CR3_CTSIE;

	if ((events & HAL_UART_EVENT_LBD) == HAL_UART_EVENT_LBD)
		device->CR2 |= USART_CR2_LBDIE;

	if ((events & HAL_UART_EVENT_IDLE) == HAL_UART_EVENT_IDLE)
		device->CR1 |= USART_CR1_IDLEIE;

	if ((events & HAL_UART_EVENT_TXE) == HAL_UART_EVENT_TXE)
		device->CR1 |= USART_CR1_TXEIE;

	if ((events & HAL_UART_EVENT_TC) == HAL_UART_EVENT_TC)
		device->CR1 |= USART_CR1_TCIE;

	if ((events & HAL_UART_EVENT_RXNE) == HAL_UART_EVENT_RXNE)
		device->CR1 |= USART_CR1_RXNEIE;

	if ((events & HAL_UART_EVENT_PE) == HAL_UART_EVENT_PE)
		device->CR1 |= USART_CR1_PEIE;

	if ((events & HAL_UART_EVENT_ERR) == HAL_UART_EVENT_ERR)
		device->CR3 |= USART_CR3_EIE;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les interrupcions.
/// \param    handler: Handler del dispositiu.
/// \param    events: Interupcions a deshabilitar.
///
uint32_t halUARTDisableInterrupts(
	UARTHandler handler,
	uint32_t events) {

	eosAssert(handler != NULL);

	USART_TypeDef* device = handler->device;

	if ((events & HAL_UART_EVENT_CTS) == HAL_UART_EVENT_CTS)
		device->CR3 &= ~USART_CR3_CTSIE;

	if ((events & HAL_UART_EVENT_LBD) == HAL_UART_EVENT_LBD)
		device->CR2 &= ~USART_CR2_LBDIE;

	if ((events & HAL_UART_EVENT_IDLE) == HAL_UART_EVENT_IDLE)
		device->CR1 &= ~USART_CR1_IDLEIE;

	if ((events & HAL_UART_EVENT_TXE) == HAL_UART_EVENT_TXE)
		device->CR1 &= ~USART_CR1_TXEIE;

	if ((events & HAL_UART_EVENT_TC) == HAL_UART_EVENT_TC)
		device->CR1 &= ~USART_CR1_TCIE;

	if ((events & HAL_UART_EVENT_RXNE) == HAL_UART_EVENT_RXNE)
		device->CR1 &= ~USART_CR1_RXNEIE;

	if ((events & HAL_UART_EVENT_PE) == HAL_UART_EVENT_PE)
		device->CR1 &= ~USART_CR1_PEIE;

	if ((events & HAL_UART_EVENT_ERR) == HAL_UART_EVENT_ERR)
		device->CR3 &= ~USART_CR3_EIE;

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio.
/// \param    handler: Handler del dispositiu.
///
void halUARTInterruptHandler(
	UARTHandler handler) {

	eosAssert(handler != NULL);

	if (handler->isrFunction != NULL)
		handler->isrFunction(handler, handler->isrParams);
}
