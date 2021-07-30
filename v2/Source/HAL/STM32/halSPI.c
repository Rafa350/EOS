#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halGPIO.h"

#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


#define __VERIFY_CHANNEL(chanel)  eosAssert((channel >= HAL_SPI_CHANNEL_1) && (channel <= HAL_SPI_CHANNEL_6))
#define __VERIFY_HANDLER(handler) eosAssert(handler != NULL)
#define __VERIFY_DEVICE(device)   eosAssert(IS_SPI_ALL_INSTANCE(device))


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    channel: El identificador del dispositiu
/// \return   El dispositiu.
///
static inline SPI_TypeDef* getDevice(
	SPIChannel channel) {

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
	SPI_HandleTypeDef* handle,
	SPIOptions options) {

	eosAssert(handle != NULL);
	__VERIFY_DEVICE(device);

	static uint32_t const baudRateTbl[] = {
		SPI_BAUDRATEPRESCALER_2,
		SPI_BAUDRATEPRESCALER_4,
		SPI_BAUDRATEPRESCALER_8,
		SPI_BAUDRATEPRESCALER_16,
		SPI_BAUDRATEPRESCALER_32,
		SPI_BAUDRATEPRESCALER_64,
		SPI_BAUDRATEPRESCALER_128,
		SPI_BAUDRATEPRESCALER_256
	};

	// Configura el modul
	//
	handle->Instance = device;
	handle->Init.BaudRatePrescaler = baudRateTbl[(options & HAL_SPI_CLOCKDIV_mask) >> HAL_SPI_CLOCKDIV_pos];
	//handle->Init.Direction = SPI_DIRECTION_2LINES;
	handle->Init.Direction = SPI_DIRECTION_1LINE;
	handle->Init.NSS = SPI_NSS_SOFT;
	handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	handle->Init.TIMode = SPI_TIMODE_DISABLED;
	handle->Init.Mode = ((options & HAL_SPI_MS_mask) == HAL_SPI_MS_MASTER) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	handle->Init.DataSize = ((options & HAL_SPI_SIZE_mask) == HAL_SPI_SIZE_8) ? SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
	handle->Init.CLKPolarity = ((options & HAL_SPI_CPOL_mask) == HAL_SPI_CPOL_LOW) ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
	handle->Init.CLKPhase = ((options & HAL_SPI_CPHA_mask) == HAL_SPI_CPHA_EDGE1) ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
	handle->Init.FirstBit = ((options & HAL_SPI_FIRSTBIT_mask) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

	HAL_SPI_Init(handle);

	// Activa el modul
	//
	__set_bit_msk(device->CR1, SPI_CR1_SPE);
}


/// ----------------------------------------------------------------------
/// \brief    Inicilitza el modul SPI.
/// \param    data: Buffer de dades.
/// \param    settings: Parametres d'inicialitzacio.
///
SPIHandler halSPIInitialize(
	SPIData* data,
	const SPISettings *settings) {

	eosAssert(data != NULL);
	eosAssert(settings != NULL);

	SPI_TypeDef* device = getDevice(settings->channel);

	enableDeviceClock(device);
    setupDevice(device, &data->handle, settings->options);

    SPIHandler handler = data;
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
	SPIHandler handler) {

	__VERIFY_HANDLER(handler);
	__VERIFY_DEVICE(handler->device);

	SPI_TypeDef* device = handler->device;

	__clear_bit_msk(device->CR1, ~SPI_CR1_SPE);
	disableDeviceClock(device);
}


/// ----------------------------------------------------------------------
/// \brief    Assigna la funcio d'interrupcio.
/// \param    handler: Handler del dispositiu.
/// \param    function: La funcio.
/// \param    params: El parametres.
///
void halSPISetInterruptFunction(
	SPIHandler handler,
	SPIInterruptFunction function,
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
///
void halSPISendBuffer(
	SPIHandler handler,
	const uint8_t* data,
	int size) {

	__VERIFY_HANDLER(handler);

	HAL_SPI_Transmit(&handler->handle, data, size, 100);
}
