#include "hal/halSPI.h"
#include "stm32f4xx_hal.h"


static SPI_HandleTypeDef spiHandler[HAL_SPI_ID_MAX];


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del modul SPI..
/// \param id: identificador del modul.
///
static void EnableClock(
	uint8_t id) {

	switch (id) {
		case HAL_SPI_ID_1:
			__HAL_RCC_SPI1_CLK_ENABLE();
			break;

		case HAL_SPI_ID_2:
			__HAL_RCC_SPI2_CLK_ENABLE();
			break;

		case HAL_SPI_ID_3:
			__HAL_RCC_SPI3_CLK_ENABLE();
			break;

		case HAL_SPI_ID_4:
			__HAL_RCC_SPI4_CLK_ENABLE();
			break;

		case HAL_SPI_ID_5:
			__HAL_RCC_SPI5_CLK_ENABLE();
			break;

		case HAL_SPI_ID_6:
			__HAL_RCC_SPI6_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el rellotge del modul SPI.
/// \param id: Identificador del modul.
///
static void DisableClock(
	uint8_t id) {

	switch (id) {
		case HAL_SPI_ID_1:
			__HAL_RCC_SPI1_CLK_DISABLE();
			break;

		case HAL_SPI_ID_2:
			__HAL_RCC_SPI2_CLK_DISABLE();
			break;

		case HAL_SPI_ID_3:
			__HAL_RCC_SPI3_CLK_DISABLE();
			break;

		case HAL_SPI_ID_4:
			__HAL_RCC_SPI4_CLK_DISABLE();
			break;

		case HAL_SPI_ID_5:
			__HAL_RCC_SPI5_CLK_DISABLE();
			break;

		case HAL_SPI_ID_6:
			__HAL_RCC_SPI6_CLK_DISABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Obte el handler del modul SPI.
/// \param id: identificador del modul.
/// \return El handler del modul.
///
static SPI_HandleTypeDef *GetHandler(
	uint8_t id) {

	return &spiHandler[id];
}


/// ----------------------------------------------------------------------
/// \brief Configura els parametres d'inicialitzacio del handler.
/// \param info: Parametres de configuracio.
/// \param handle: El handler a configurar.
///
static SPI_HandleTypeDef *PrepareHandler(
	const SPIInitializeInfo *info) {

	static SPI_TypeDef * const spiTbl[HAL_SPI_ID_MAX] = {
		SPI1,
		SPI2,
		SPI3,
		SPI4,
		SPI5,
		SPI6
	};

	static const uint32_t const baudRateTbl[] = {
		SPI_BAUDRATEPRESCALER_2,
		SPI_BAUDRATEPRESCALER_4,
		SPI_BAUDRATEPRESCALER_8,
		SPI_BAUDRATEPRESCALER_16,
		SPI_BAUDRATEPRESCALER_32,
		SPI_BAUDRATEPRESCALER_64,
		SPI_BAUDRATEPRESCALER_128,
		SPI_BAUDRATEPRESCALER_256
	};

	SPI_HandleTypeDef *handler = GetHandler(info->id);
	handler->Instance = spiTbl[info->id];
	handler->Init.BaudRatePrescaler = baudRateTbl[info->clockDiv];
	handler->Init.Direction = SPI_DIRECTION_2LINES;
	handler->Init.NSS = SPI_NSS_SOFT;
	handler->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	handler->Init.TIMode = SPI_TIMODE_DISABLED;
	handler->Init.Mode = ((info->options & HAL_SPI_MS_MASK) == HAL_SPI_MS_MASTER) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	handler->Init.DataSize = ((info->options & HAL_SPI_SIZE_MASK) == HAL_SPI_SIZE_8) ? SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
	handler->Init.CLKPolarity = ((info->options & HAL_SPI_CPOL_MASK) == HAL_SPI_CPOL_LOW) ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
	handler->Init.CLKPhase = ((info->options & HAL_SPI_CPHA_MASK) == HAL_SPI_CPHA_EDGE1) ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
	handler->Init.FirstBit = ((info->options & HAL_SPI_FIRSTBIT_MASK) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

	return handler;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul SPI.
/// \param handler: El handler del modul.
///
static void InitializeModule(
	SPI_HandleTypeDef *handler) {

	HAL_SPI_Init(handler);
	__HAL_SPI_ENABLE(handler);
}


/// ----------------------------------------------------------------------
/// \brier Desinitialitza el modul SPI
/// \param handler: El handler del modul.
///
static void DeinitializeModule(
	SPI_HandleTypeDef *handler) {

	HAL_SPI_DeInit(handler);
}


/// ----------------------------------------------------------------------
/// \brief Inicilitza wl modul SPI.
/// \param info: Parametres d'inicialitzacio.
///
void halSPIInitialize(
	const SPIInitializeInfo *info) {

	EnableClock(info->id);

	SPI_HandleTypeDef *handler = PrepareHandler(info);
    InitializeModule(handler);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul SPI.
/// \param id: Identificador del modul.
///
void halSPIShutdown(
	uint8_t id) {

	SPI_HandleTypeDef *handler = GetHandler(id);

	DeinitializeModule(handler);
	DisableClock(id);
}


/// ----------------------------------------------------------------------
/// \brief Envia un bloc de dades.
/// \param data: Bloc de dades.
/// \param size: Longitut del bloc de dades.
///
void halSPISendBuffer(
	uint8_t id,
	uint8_t *data,
	uint16_t size) {

	SPI_HandleTypeDef *handler = GetHandler(id);

	HAL_SPI_Transmit(handler, data, size, 100);
}

