#include "hal/halSPI.h"
#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


static SPI_HandleTypeDef handles[HAL_SPI_ID_MAX];


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del modul SPI.
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
static SPI_HandleTypeDef *GetHandle(
	uint8_t id) {

	return &handles[id];
}


/// ----------------------------------------------------------------------
/// \brief Configura els parametres d'inicialitzacio del handler.
/// \param info: Parametres de configuracio.
/// \param handle: El handler a configurar.
///
static SPI_HandleTypeDef *PrepareHandle(
	const SPIInitializeInfo *info) {

	static SPI_TypeDef * const instances[HAL_SPI_ID_MAX] = {
		SPI1,
		SPI2,
		SPI3,
		SPI4,
		SPI5,
		SPI6
	};

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

	SPI_HandleTypeDef *handle = GetHandle(info->id);
	handle->Instance = instances[info->id];
	handle->Init.BaudRatePrescaler = baudRateTbl[info->clockDiv];
	handle->Init.Direction = SPI_DIRECTION_2LINES;
	handle->Init.NSS = SPI_NSS_SOFT;
	handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	handle->Init.TIMode = SPI_TIMODE_DISABLED;
	handle->Init.Mode = ((info->options & HAL_SPI_MS_MASK) == HAL_SPI_MS_MASTER) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	handle->Init.DataSize = ((info->options & HAL_SPI_SIZE_MASK) == HAL_SPI_SIZE_8) ? SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
	handle->Init.CLKPolarity = ((info->options & HAL_SPI_CPOL_MASK) == HAL_SPI_CPOL_LOW) ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
	handle->Init.CLKPhase = ((info->options & HAL_SPI_CPHA_MASK) == HAL_SPI_CPHA_EDGE1) ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
	handle->Init.FirstBit = ((info->options & HAL_SPI_FIRSTBIT_MASK) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

	return handle;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul SPI.
/// \param handle: El handler del modul.
///
static void InitializeModule(
	SPI_HandleTypeDef *handle) {

	HAL_SPI_Init(handle);
	__HAL_SPI_ENABLE(handle);
}


/// ----------------------------------------------------------------------
/// \brier Desinitialitza el modul SPI
/// \param handle: El handler del modul.
///
static void DeinitializeModule(
	SPI_HandleTypeDef *handle) {

	HAL_SPI_DeInit(handle);
}


/// ----------------------------------------------------------------------
/// \brief Inicilitza wl modul SPI.
/// \param info: Parametres d'inicialitzacio.
///
void halSPIInitialize(
	const SPIInitializeInfo *info) {

	EnableClock(info->id);

	SPI_HandleTypeDef *handle = PrepareHandle(info);
    InitializeModule(handle);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul SPI.
/// \param id: Identificador del modul.
///
void halSPIShutdown(
	uint8_t id) {

	DeinitializeModule(GetHandle(id));
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

	HAL_SPI_Transmit(GetHandle(id), data, size, 100);
}

