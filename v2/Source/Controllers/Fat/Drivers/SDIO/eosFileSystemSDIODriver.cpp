#include "eos.h"
#include "Controllers/Fat/Drivers/SDIO/eosFileSystemSDIODriver.h"
#include "HAL/halGPIO.h"

#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_sd.h"


using namespace eos;


static SD_HandleTypeDef sdHandle;
static DMA_HandleTypeDef dmaRxHandle;
static DMA_HandleTypeDef dmaTxHandle;

IFileSystemDriver *FileSystemSDIODriver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
IFileSystemDriver *FileSystemSDIODriver::getInstance() {

	if (instance == nullptr)
		instance = new FileSystemSDIODriver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
FileSystemSDIODriver::FileSystemSDIODriver() {

	fsStatus = FileSystemDriverStatus::notInitialized;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
bool FileSystemSDIODriver::initialize() {

	static const GPIOInitializePinInfo gpioInitInfo[] = {
		{SD_PRESENT_PORT, SD_PRESENT_PIN,
				HAL_GPIO_MODE_INPUT | HAL_GPIO_SPEED_FAST, HAL_GPIO_AF_NONE},
		{HAL_GPIO_PORT_C, HAL_GPIO_PIN_8,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
		{HAL_GPIO_PORT_C, HAL_GPIO_PIN_9,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
		{HAL_GPIO_PORT_C, HAL_GPIO_PIN_10,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
		{HAL_GPIO_PORT_C, HAL_GPIO_PIN_11,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
		{HAL_GPIO_PORT_C, HAL_GPIO_PIN_12,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
		{HAL_GPIO_PORT_D, HAL_GPIO_PIN_2,
				HAL_GPIO_MODE_ALT_PP | HAL_GPIO_PULL_UP | HAL_GPIO_SPEED_HIGH, HAL_GPIO_AF12_SDMMC1},
	};

	// Inicialitza els port de comunicacio
	//
	halGPIOInitializePins(gpioInitInfo, sizeof(gpioInitInfo) / sizeof(gpioInitInfo[0]));

	// Comprova si esta present el dispositiu
	//
	if (halGPIOReadPin(SD_PRESENT_PORT, SD_PRESENT_PIN) == 1) {
		fsStatus = FileSystemDriverStatus::deviceNotPressent;
		return false;
	}

	// Inicialitza el controlador DMA per RX
	//
	__HAL_RCC_DMA2_CLK_ENABLE();
	dmaRxHandle.Instance = SD_DMA_RX_STREAM;
	dmaRxHandle.Init.Channel = SD_DMA_RX_CHANNEL;
	dmaRxHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dmaRxHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	dmaRxHandle.Init.MemInc = DMA_MINC_ENABLE;
	dmaRxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	dmaRxHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	dmaRxHandle.Init.Mode = DMA_PFCTRL;
	dmaRxHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	dmaRxHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	dmaRxHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	dmaRxHandle.Init.MemBurst = DMA_MBURST_INC4;
	dmaRxHandle.Init.PeriphBurst = DMA_PBURST_INC4;

	__HAL_LINKDMA(&sdHandle, hdmarx, dmaRxHandle);
	HAL_DMA_DeInit(&dmaRxHandle);
	HAL_DMA_Init(&dmaRxHandle);
	HAL_NVIC_SetPriority(SD_DMA_RX_IRQ, 0x0F, 0);

	// Inicialitza el controlador DMA per TX
	//
    dmaRxHandle.Instance = SD_DMA_TX_STREAM;
	dmaRxHandle.Init.Channel = SD_DMA_TX_CHANNEL;
	dmaRxHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dmaRxHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	dmaRxHandle.Init.MemInc = DMA_MINC_ENABLE;
	dmaRxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	dmaRxHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	dmaRxHandle.Init.Mode = DMA_PFCTRL;
	dmaRxHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	dmaRxHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	dmaRxHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	dmaRxHandle.Init.MemBurst = DMA_MBURST_INC4;
	dmaRxHandle.Init.PeriphBurst = DMA_PBURST_INC4;

	__HAL_LINKDMA(&sdHandle, hdmatx, dmaTxHandle);
	HAL_DMA_DeInit(&dmaTxHandle);
	HAL_DMA_Init(&dmaTxHandle);
	HAL_NVIC_SetPriority(SD_DMA_TX_IRQ, 0x0F, 0);

	// Initializa el controlador SDMMC
	//
	__HAL_RCC_SDMMC1_CLK_ENABLE();
	sdHandle.Instance = SD_MODULE;
	sdHandle.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
	sdHandle.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
	sdHandle.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
	sdHandle.Init.BusWide = SDMMC_BUS_WIDE_1B;
	sdHandle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
	sdHandle.Init.ClockDiv = SDMMC_TRANSFER_CLK_DIV;
	if (HAL_SD_Init(&sdHandle) != HAL_OK) {
	    fsStatus = FileSystemDriverStatus::error;
	    return false;
	}
	if (HAL_SD_ConfigWideBusOperation(&sdHandle, SDMMC_BUS_WIDE_4B) != HAL_OK) {
		fsStatus = FileSystemDriverStatus::error;
		return false;
    }

	// Activa les interrupcions
	//
	HAL_NVIC_EnableIRQ(SD_DMA_TX_IRQ);
	HAL_NVIC_EnableIRQ(SD_DMA_TX_IRQ);

	// Tot correcte
	//
	fsStatus = FileSystemDriverStatus::ok;
	return true;
}


void FileSystemSDIODriver::shutdown() {

}


FileSystemDriverStatus FileSystemSDIODriver::getStatus() const {

	return fsStatus;
}


/// ----------------------------------------------------------------------
/// \brief Comprova si esta ocupat.
/// \return True si esta ocupat. False en cas contrari.
///
bool FileSystemSDIODriver::isBusy() {

	return HAL_SD_GetCardState(&sdHandle) != HAL_SD_CARD_TRANSFER;
}


int FileSystemSDIODriver::ioctrl() {

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un bloc de dades
/// \param data: Adresa del buffer de dades.
/// \param blockAddr: Primer bloc a lleigir.
/// \param numBlocks: Numero de blocs a lleigir.
/// \param timeout: Temps maxim d'espera.
/// \return True si tot es correcte. False en cas contrari.
///
bool FileSystemSDIODriver::read(
	uint8_t *data,
	uint32_t blockAddr,
	uint32_t numBlocks,
	uint32_t timeout) {

	return HAL_SD_ReadBlocks(&sdHandle, data, blockAddr, numBlocks, timeout) == HAL_OK;
}


int FileSystemSDIODriver::write() {

	return 0;
}


extern "C" void *fsGetInstance(void) {

	return (void*) FileSystemSDIODriver::getInstance();
}


extern "C" bool fsInitialize(void *instance) {

	bool result = false;

	if (instance != NULL) {
		IFileSystemDriver *drv = (IFileSystemDriver*) instance;
		result = drv->initialize();
	}

	return result;
}


extern "C" bool fsIsBusy(void *instance) {

	bool result = true;

	if (instance != NULL) {
		IFileSystemDriver *drv = (IFileSystemDriver*) instance;
		result = drv->isBusy();
	}

	return result;
}
