#include "eos.h"
#include "eosAssert.h"
#include "hal/STM32/halSPI.h"
#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


static SPI_HandleTypeDef handles[HAL_SPI_ID_MAX];
static uint32_t enabledClocks = 0;


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del modul SPI.
/// \param id: identificador del modul.
///
static void enableClock(
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
    
    enabledClocks |= 1 << id;
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el rellotge del modul SPI.
/// \param id: Identificador del modul.
///
static void disableClock(
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
static SPI_HandleTypeDef *getHandle(
	uint8_t id) {

	return &handles[id];
}


/// ----------------------------------------------------------------------
/// \brief Configura els parametres d'inicialitzacio del handler.
/// \param pInfo: Parametres de configuracio.
/// \param handle: El handler a configurar.
///
static SPI_HandleTypeDef *prepareHandle(
	const SPIInitializeInfo *pInfo) {

	// Precondicions
	//
	eosAssert(pInfo != NULL);

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

	// Configura el modul
	//
	SPI_HandleTypeDef *handle = getHandle(pInfo->id);
	handle->Instance = instances[pInfo->id];
	handle->Init.BaudRatePrescaler = baudRateTbl[pInfo->clockDiv];
	handle->Init.Direction = SPI_DIRECTION_2LINES;
	handle->Init.NSS = SPI_NSS_SOFT;
	handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	handle->Init.TIMode = SPI_TIMODE_DISABLED;
	handle->Init.Mode = ((pInfo->options & HAL_SPI_MS_mask) == HAL_SPI_MS_MASTER) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	handle->Init.DataSize = ((pInfo->options & HAL_SPI_SIZE_mask) == HAL_SPI_SIZE_8) ? SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
	handle->Init.CLKPolarity = ((pInfo->options & HAL_SPI_CPOL_mask) == HAL_SPI_CPOL_LOW) ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
	handle->Init.CLKPhase = ((pInfo->options & HAL_SPI_CPHA_mask) == HAL_SPI_CPHA_EDGE1) ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
	handle->Init.FirstBit = ((pInfo->options & HAL_SPI_FIRSTBIT_mask) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

	return handle;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el modul SPI.
/// \param handle: El handler del modul.
///
static void initializeModule(
	SPI_HandleTypeDef *handle) {

	// Precondicions
	//
	eosAssert(handle != NULL);

	// Inicialitza el modul
	//
	HAL_SPI_Init(handle);
	__HAL_SPI_ENABLE(handle);
}


/// ----------------------------------------------------------------------
/// \brier Desinicialitza el modul SPI
/// \param handle: El handler del modul.
///
static void deinitializeModule(
	SPI_HandleTypeDef *handle) {

	// Precondicions
	//
	eosAssert(handle != NULL);

	// Desinitcialitza el modul
	//
	HAL_SPI_DeInit(handle);
}


/// ----------------------------------------------------------------------
/// \brief Inicilitza el modul SPI.
/// \param pInfo: Parametres d'inicialitzacio.
///
void halSPIInitialize(
	const SPIInitializeInfo *pInfo) {

	// Precondicions
	//
	eosAssert(pInfo != NULL);

	// Activa el rellotge
	//
	enableClock(pInfo->id);

	// Inicialitza el modul
	//
	SPI_HandleTypeDef *handle = prepareHandle(pInfo);
    initializeModule(handle);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el modul SPI.
/// \param id: Identificador del modul.
///
void halSPIShutdown(
	uint8_t id) {

	// Desinicialitza el modul
	//
	deinitializeModule(getHandle(id));
	disableClock(id);
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

	// Precondicions
	//
	eosAssert(data != NULL);
	eosAssert(size != 0);

	// Transfereix el bloc de dades
	//
	HAL_SPI_Transmit(getHandle(id), data, size, 100);
}
