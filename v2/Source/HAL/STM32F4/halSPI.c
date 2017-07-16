#include "hal/halSPI.h"


static SPI_TypeDef * const spiTbl[] = {
	SPI1,
	SPI2,
	SPI3,
	SPI4,
	SPI5,
	SPI6
};


/// ----------------------------------------------------------------------
/// \brief Inicilitza wl modul SPI.
/// \param module: El modul a inicilitzar.
/// \param options: Opcions de configuracio.
///
void halSPIInitialize(
	SPIModule module,
	SPIOptions options) {

	// Activa el modul
	switch (module) {
		case HAL_SPI_MODULE_1:
			__HAL_RCC_SPI1_CLK_ENABLE();
			break;

		case HAL_SPI_MODULE_2:
			__HAL_RCC_SPI2_CLK_ENABLE();
			break;

		case HAL_SPI_MODULE_3:
			__HAL_RCC_SPI3_CLK_ENABLE();
			break;

		case HAL_SPI_MODULE_4:
			__HAL_RCC_SPI4_CLK_ENABLE();
			break;

		case HAL_SPI_MODULE_5:
			__HAL_RCC_SPI5_CLK_ENABLE();
			break;

		case HAL_SPI_MODULE_6:
			__HAL_RCC_SPI6_CLK_ENABLE();
			break;
	}

	SPI_HandleTypeDef spiHandle;
	spiHandle.Instance = spiTbl[module];
	spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	spiHandle.Init.Direction = SPI_DIRECTION_2LINES;
	spiHandle.Init.NSS = SPI_NSS_SOFT;
	spiHandle.Init.Mode = ((options & HAL_SPI_MS_MASK) == HAL_SPI_MS_MASTER) ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	spiHandle.Init.DataSize = ((options & HAL_SPI_SIZE_MASK) == HAL_SPI_SIZE_8) ? SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
	spiHandle.Init.CLKPolarity = ((options & HAL_SPI_CPOL_MASK) == HAL_SPI_CPOL_LOW) ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
	spiHandle.Init.CLKPhase = ((options & HAL_SPI_CPHA_MASK) == HAL_SPI_CPHA_EDGE1) ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
	spiHandle.Init.FirstBit = ((options & HAL_SPI_FIRSTBIT_MASK) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

	__HAL_SPI_DISABLE(&spiHandle);
	HAL_SPI_Init(&spiHandle);
	__HAL_SPI_ENABLE(&spiHandle);
}


/// ----------------------------------------------------------------------
/// \brief Transmet un valor de
/// \param module: Modul spi a utilitzar.
/// \param data: El valor a transmetre
/// \return El valor rebut.
///
uint8_t halSPISend(
	SPIModule module,
	uint8_t data) {

	SPI_TypeDef * const spi = spiTbl[module];

	// Wait for previous transmissions to complete if DMA TX enabled for SPI
	while ((spi->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || (spi->SR & SPI_SR_BSY))
		continue;

	// Fill output buffer with data
	spi->DR = data;

	// Wait for transmission to complete
	 while ((spi->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || (spi->SR & SPI_SR_BSY))
		 continue;

	// Return data from buffer
	return spi->DR;
}
