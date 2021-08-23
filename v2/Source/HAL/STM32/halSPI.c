#include "HAL/hal.h"
#include "HAL/STM32/halGPIO.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halSYS.h"


#define __VERIFY_CHANNEL(chanel)  eosAssert((channel >= HAL_SPI_CHANNEL_1) && (channel <= HAL_SPI_CHANNEL_6))
#define __VERIFY_HANDLER(handler) eosAssert(handler != NULL)
#define __VERIFY_DEVICE(device)   eosAssert(IS_SPI_ALL_INSTANCE(device))


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: El identificador del dispositiu
/// \return   El dispositiu.
///
static inline SPI_TypeDef* getDevice(
	halSPIChannel channel) {

	__VERIFY_CHANNEL(channel);

	static SPI_TypeDef* const devices[] = {
		SPI1,
		SPI2,
		SPI3,
		SPI4,
		SPI5,
		SPI6
	};

	return devices[channel];
}

/// ----------------------------------------------------------------------
/// \brief    Activa el rellotge del dispositiu SPI.
/// \param    device: El dispositiu.
///
static void enableDeviceClock(
	SPI_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {
		case SPI1_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
			break;

		case SPI2_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);
			break;

		case SPI3_BASE:
			__set_bit_msk(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);
			break;

		case SPI4_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);
			break;

		case SPI5_BASE:
			__set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);
			break;

		case SPI6_BASE:
			 __set_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI6EN);
			break;
	}

	__DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el rellotge del dispositiu.
/// \param    device: El dispositiu.
///
static void disableDeviceClock(
	SPI_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {

		case SPI1_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
			break;

		case SPI2_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);
			break;

		case SPI3_BASE:
			__clear_bit_msk(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);
			break;

		case SPI4_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);
			break;

		case SPI5_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);
			break;

		case SPI6_BASE:
			__clear_bit_msk(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura els parametres d'inicialitzacio del handler.
/// \param    device: El dispositiu
/// \param    handle: Handle del HAL (provisional)
/// \param    info: Parametres de configuracio.
///
static void setupDevice(
	SPI_TypeDef* device,
	halSPIOptions options) {

	__VERIFY_DEVICE(device);

	uint32_t temp;

	// Descativa el modul
	//
	__clear_bit_msk(device->CR1, SPI_CR1_SPE);

	// Configura el registre CR1
	//
	temp = 0;
	switch (options & HAL_SPI_CLOCKDIV_mask) {
		case HAL_SPI_CLOCKDIV_4:
			temp |= SPI_CR1_BR_0;
			break;

		case HAL_SPI_CLOCKDIV_8:
			temp |= SPI_CR1_BR_1;
			break;

		case HAL_SPI_CLOCKDIV_16:
			temp |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
			break;

		case HAL_SPI_CLOCKDIV_32:
			temp |= SPI_CR1_BR_2;
			break;

		case HAL_SPI_CLOCKDIV_64:
			temp |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
			break;

		case HAL_SPI_CLOCKDIV_128:
			temp |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
			break;

		case HAL_SPI_CLOCKDIV_256:
			temp |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
			break;
	}
#ifdef EOS_STM32F4
	if ((options & HAL_SPI_SIZE_mask) == HAL_SPI_SIZE_16)
		temp |= SPI_CR1_DFF;
#endif
	if ((options & HAL_SPI_MS_mask) == HAL_SPI_MS_MASTER)
		temp |= SPI_CR1_MSTR | SPI_CR1_SSI;
	if ((options & HAL_SPI_CPOL_mask) == HAL_SPI_CPOL_HIGH)
		temp |= SPI_CR1_CPOL;
	if ((options & HAL_SPI_CPHA_mask) == HAL_SPI_CPHA_EDGE2)
		temp |= SPI_CR1_CPHA;
	if ((options & HAL_SPI_FIRSTBIT_mask) == HAL_SPI_FIRSTBIT_LSB)
		temp |= SPI_CR1_LSBFIRST;
	temp |= SPI_CR1_SSI;
	temp |= SPI_CR1_SSM;
	device->CR1 = temp;

	// Configura el registre CR2
	//
	temp = 0;
#ifdef EOS_STM32F7
	switch (options & HAL_SPI_SIZE_mask) {
		case HAL_SPI_SIZE_8:
			temp |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
			break;

		case HAL_SPI_SIZE_16:
			temp |= SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
			break;
	}
#endif
	device->CR2 = temp;

	// Activa el modul
	//
	__set_bit_msk(device->CR1, SPI_CR1_SPE);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de transmissio estigui buit.
/// \param    handler: El handler del dispositiu.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
#ifdef EOS_STM32F7
static void waitTxFifoEmpty(
	halSPIHandler handler,
	unsigned startTime,
	unsigned blockTime) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	SPI_TypeDef* device = handler->device;

	while ((device->SR & SPI_SR_FTLVL) != SPI_FTLVL_EMPTY) {
		if (halSYSCheckTimeout(startTime, blockTime)) {

		}
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el fifo de recepcio estigui buit.
/// \param    handler: El handler del dispositiu.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
#ifdef EOS_STM32F7
static void waitRxFifoEmpty(
	halSPIHandler handler,
	unsigned startTime,
	unsigned blockTime) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	SPI_TypeDef* device = handler->device;

	while ((device->SR & SPI_SR_FRLVL) != SPI_FRLVL_EMPTY) {
		if (halSYSCheckTimeout(startTime, blockTime)) {

		}

		uint8_t dummy = *((__IO uint8_t *)&device->DR);
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Espera que el dispositiu estigui lliure
/// \param    handler: El handler del dispositiu.
/// \param    startTime: Temps del inici de les operacions
/// \param    blockTime: Temps maxim de bloqueig.
///
static void waitBusy(
	halSPIHandler handler,
	unsigned startTime,
	unsigned blockTime) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	SPI_TypeDef* device = handler->device;

	while (__check_bit_pos(device->SR, SPI_SR_BSY_Pos)) {
		if (halSYSCheckTimeout(startTime, blockTime)) {
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicilitza el modul SPI.
/// \param    data: Buffer de dades.
/// \param    settings: Parametres d'inicialitzacio.
///
halSPIHandler halSPIInitialize(
	halSPIData* data,
	const halSPISettings* settings) {

	eosAssert(data != NULL);
	eosAssert(settings != NULL);

	SPI_TypeDef* device = getDevice(settings->channel);

	enableDeviceClock(device);
    setupDevice(device, settings->options);

    halSPIHandler handler = data;
    handler->device = device;
    handler->isrFunction = NULL;
    handler->isrParams = NULL;

	return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul SPI.
/// \param    handler: El handler del dispositiu.
///
void halSPIDeinitialize(
	halSPIHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	SPI_TypeDef* device = handler->device;

	__clear_bit_msk(device->CR1, SPI_CR1_SPE);
	disableDeviceClock(device);
}


/// ----------------------------------------------------------------------
/// \brief    Assigna la funcio d'interrupcio.
/// \param    handler: Handler del dispositiu.
/// \param    function: La funcio.
/// \param    params: El parametres.
///
void halSPISetInterruptFunction(
	halSPIHandler handler,
	halSPIInterruptFunction function,
	void* params) {

	__VERIFY_HANDLER(handler);

	handler->isrFunction = function;
	handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Envia un bloc de dades.
/// \param    handler: El handler del dispositiu.
/// \param    data: Bloc de dades.
/// \param    size: Longitut del bloc de dades.
/// \param    blockTime: Temps maxim de bloqueig
///
void halSPISendBuffer(
	halSPIHandler handler,
	const uint8_t* data,
	int size,
	unsigned blockTime) {

	eosAssert(data != NULL);
	eosAssert(size > 0);
	__VERIFY_HANDLER(handler);


	SPI_TypeDef* device = handler->device;

	int count = size;
	const uint8_t *p = data;
	unsigned startTime = halSYSGetTick();

	while (count > 0) {

#if defined(EOS_STM32F4)
		*((volatile uint8_t*)&device->DR) = *((uint8_t*)p);
		p += sizeof(uint8_t);
		count -= sizeof(uint8_t);

#elif defined(EOS_STM32F7)
		if (count > 1) {
			// Acces com a 16 bits (Packing mode)
			device->DR = *((uint16_t*)p);
			p += sizeof(uint16_t);
			count -= sizeof(uint16_t);
		}
		else {
			// Access com a 8 bits
			*((volatile uint8_t*)&device->DR) = *((uint8_t*)p);
			p += sizeof(uint8_t);
			count -= sizeof(uint8_t);
		}
#else
#error "CPU no soportada."
#endif

		while (!__check_bit_pos(device->SR, SPI_SR_TXE_Pos)) {
			if (halSYSCheckTimeout(startTime, blockTime)) {

			}
		}
	}

#ifdef EOS_STM32F7
	waitTxFifoEmpty(handler, startTime, blockTime);
#endif
	waitBusy(handler, startTime, blockTime);
#ifdef EOS_STM32F7
	waitRxFifoEmpty(handler, startTime, blockTime);
#endif
}
