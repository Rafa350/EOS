#include "hal/halSPI.h"


static SPI_TypeDef *spiTbl[] = {
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
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
			break;

		case HAL_SPI_MODULE_2:
			RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
			break;

		case HAL_SPI_MODULE_3:
			RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
			break;

		case HAL_SPI_MODULE_4:
			RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
			break;

		case HAL_SPI_MODULE_5:
			RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
			break;

		case HAL_SPI_MODULE_6:
			RCC->APB2ENR |= RCC_APB2ENR_SPI6EN;
			break;
	}

	SPI_TypeDef *spi = spiTbl[module];

	spi->CR1 &= ~SPI_CR1_SPE;

	SPI_InitTypeDef spiInit;
	spiInit.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spiInit.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spiInit.SPI_NSS = SPI_NSS_Soft;
	spiInit.SPI_Mode = ((options & HAL_SPI_MS_MASK) == HAL_SPI_MS_MASTER) ? SPI_Mode_Master : SPI_Mode_Slave;
	spiInit.SPI_DataSize = ((options & HAL_SPI_SIZE_MASK) == HAL_SPI_SIZE_8) ? SPI_DataSize_8b : SPI_DataSize_16b;
	spiInit.SPI_CPOL = ((options & HAL_SPI_CPOL_MASK) == HAL_SPI_CPOL_LOW) ? SPI_CPOL_Low : SPI_CPOL_High;
	spiInit.SPI_CPHA = ((options & HAL_SPI_CPHA_MASK) == HAL_SPI_CPHA_EDGE1) ? SPI_CPHA_1Edge : SPI_CPHA_2Edge;
	spiInit.SPI_FirstBit = ((options & HAL_SPI_FIRSTBIT_MASK) == HAL_SPI_FIRSTBIT_MSB) ? SPI_FirstBit_MSB : SPI_FirstBit_LSB;

	SPI_Init(spi, &spiInit);
	spi->CR1 |= SPI_CR1_SPE;
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

	SPI_TypeDef *spi = spiTbl[module];

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
