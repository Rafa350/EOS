#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#if defined(USE_CDC_DEVICE)
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"
#include "Controllers/USBDevice/CDC/eosCDCInterface_VCOM.h"
#elif defined(USE_MSC_DEVICE)
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_SSD.h"
#include "Controllers/USBDevice/MSC/eosMSCStorage_RAM.h"
#elif defined(USE_HUD_DEVICE)
#include "Controllers/USBDevice/MSC/eosUSBDeviceClassHID.h"
#endif
#include "System/Core/eosTask.h"
#include "Services/eosLedService.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sd.h"

#include "appApplication.h"


using namespace app;
using namespace eos;


extern uint8_t deviceDescriptor[1];
extern uint8_t deviceQualifierDescriptor[1];
extern uint8_t langIDDescriptor[1];

#if defined(USE_CDC_DEVICE)
extern uint8_t configurationDescriptor[];
static const USBDeviceConfiguration __deviceConfiguration {
	(USBD_DeviceDescriptor*) deviceDescriptor,
	(USBD_DeviceQualifierDescriptor*) deviceQualifierDescriptor,
	(USBD_ConfigurationDescriptor*) configurationDescriptor,
	(USBD_LangIDDescriptorHeader*) langIDDescriptor,
	"rsr.openware@gmail.com",
	"EOS USB-VCOM demo",
	"VCP interface",
	"VCP configuration"
};

#elif defined(USE_MSC_DEVICE)
extern uint8_t configurationDescriptor[];
static const USBDeviceConfiguration __deviceConfiguration {
	(USBD_DeviceDescriptor*) deviceDescriptor,
	(USBD_DeviceQualifierDescriptor*) deviceQualifierDescriptor,
	(USBD_ConfigurationDescriptor*) configurationDescriptor,
	(USBD_LangIDDescriptorHeader*) langIDDescriptor,
	"rsr.openware@gmail.com",
	"EOS USB-MSC demo",
	"MSC interface",
	"MSC configuration"
};

#elif defined(USE_HID_DEVICE)
extern uint8t_ USBD_HID_CfgDesc;
static const USBDeviceDescriptors __descriptors {
	USBD_DeviceDescriptor,
	USBD_DeviceQualifierDescriptor,
	USBLD_HID_CfgDesc,
	USBD_LangIDDesc,
	"rsr.openware@gmail.com",
	"EOS USB-HID demo",
	"MSC interface",
	"MSC configuration"
};
#endif


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication() {

	initializeGPIO();
	configureInterrupts();
}


void MyApplication::initApplication(
		ApplicationParams &params) {

	params.stackSize = params.stackSize * 2;
}


void MyApplication::initializeGPIO() {

}


void MyApplication::configureInterrupts() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onExecute() {


	//auto ledService = new eos::LedService(LED1_Instance, nullptr);
	//addService(ledService);

	//auto mainService = new MainService();
	//addService(mainService);

	USBDeviceDriverConfiguration configuration = {
		.manufacturerStr = "rsr.openware@gmail.com",
		.productStr = "EOS USB Device Demo",
		.serialNumberStr = nullptr,
		.langID = USBD_LANGID_STRING,
		.pid = USBD_PID,
		.vid = USBD_VID,
		.maxEp0Size = USB_MAX_EP0_SIZE,
		.maxPower = USBD_MAX_POWER
	};

	auto drvUSBD = new eos::USBDeviceDriver(&__deviceConfiguration, &configuration);

#if defined(USE_CDC_DEVICE)

	auto vcom = new eos::CDCInterface_VCOM();

	USBDeviceClassCDCConfiguration cdcConfiguration = {
		.iface = 0,
		.inEpAddr = CDC_IN_EP,
		.outEpAddr = CDC_OUT_EP,
		.cmdEpAddr = CDC_CMD_EP
	};
	auto devClassCDC = new eos::USBDeviceClassCDC(drvUSBD, &cdcConfiguration, vcom);

	drvUSBD->registerClass(devClassCDC);
	drvUSBD->initialize();

#elif defined(USE_MSC_DEVICE)

#if 1
	auto storage = new eos::MSCStorage_SSD();

#else
	unsigned memSize = 64 * 1024;
	uint8_t *mem = new uint8_t[memSize];
	auto storage = new eos::MSCStorage_RAM(mem, memSize);
#endif

	USBDeviceClassMSCConfiguration mscConfiguration = {
		.iface = 0, // Generar el numero automaticament
		.inEpAddr = MSC_EPIN_ADDR,
		.outEpAddr = MSC_EPOUT_ADDR
	};
	auto devClassMSC = new eos::USBDeviceClassMSC(drvUSBD, &mscConfiguration, storage);

	drvUSBD->registerClass(devClassMSC);
	drvUSBD->initialize();

#elif defined(USE_HID_DEVICE)
	auto devClassHID = new eos::USBDeviceClassHID(devUSB);

	drvUSBD->registerClass(devClassHID);
	drvUSBD->initialize(&HID_Desc);

#endif

	drvUSBD->start();

#if defined(USE_CDC_DEVICE)
	const char *txBuffer = "Capullo total\r\n";
	uint8_t rxBuffer[5];
#endif

	while (true) {
#if defined(USE_CDC_DEVICE)
	    devClassCDC->receive(rxBuffer, sizeof(rxBuffer));
	    if (devClassCDC->wait(1000) == eos::Results::success) {
	    	if (devClassCDC->transmit((uint8_t*) txBuffer, strlen(txBuffer)) == eos::Results::success) {
	    		devClassCDC->wait(1000);
	    	}
	    }
#elif defined(USE_MSC_DEVICE) || defined(USE_HID_DEVICE)
	    eos::Task::delay(1000);
#else
	    eos::Task::delay(1000);
#endif
	}
}


#ifdef USE_MSC_DEVICE
/**
  * @brief  Initializes the SD MSP.
  * @param  hsd: SD handle
  * @param  Params
  * @retval None
  */
extern "C" void xBSP_SD_MspInit(SD_HandleTypeDef *hsd, void *Params)
{
  static DMA_HandleTypeDef dma_rx_handle;
  static DMA_HandleTypeDef dma_tx_handle;
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable SDIO clock */
  __HAL_RCC_SDMMC1_CLK_ENABLE();

  /* Enable DMA2 clocks */
  __DMAx_TxRx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_SDMMC1;

  /* GPIOC configuration */
  gpio_init_structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);

  /* GPIOD configuration */
  gpio_init_structure.Pin = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* NVIC configuration for SDIO interrupts */
  HAL_NVIC_SetPriority(SDMMC1_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(SDMMC1_IRQn);

  /* Configure DMA Rx parameters */
  dma_rx_handle.Init.Channel             = SD_DMAx_Rx_CHANNEL;
  dma_rx_handle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  dma_rx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dma_rx_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_rx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_rx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_rx_handle.Init.Mode                = DMA_PFCTRL;
  dma_rx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dma_rx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dma_rx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_rx_handle.Init.MemBurst            = DMA_MBURST_INC4;
  dma_rx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;

  dma_rx_handle.Instance = SD_DMAx_Rx_STREAM;

  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmarx, dma_rx_handle);

  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dma_rx_handle);

  /* Configure the DMA stream */
  HAL_DMA_Init(&dma_rx_handle);

  /* Configure DMA Tx parameters */
  dma_tx_handle.Init.Channel             = SD_DMAx_Tx_CHANNEL;
  dma_tx_handle.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  dma_tx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
  dma_tx_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_tx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_tx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_tx_handle.Init.Mode                = DMA_PFCTRL;
  dma_tx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
  dma_tx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  dma_tx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_tx_handle.Init.MemBurst            = DMA_MBURST_INC4;
  dma_tx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;

  dma_tx_handle.Instance = SD_DMAx_Tx_STREAM;

  /* Associate the DMA handle */
  __HAL_LINKDMA(hsd, hdmatx, dma_tx_handle);

  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dma_tx_handle);

  /* Configure the DMA stream */
  HAL_DMA_Init(&dma_tx_handle);

  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 0x06, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Rx_IRQn);

  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 0x06, 0);
  HAL_NVIC_EnableIRQ(SD_DMAx_Tx_IRQn);
}
#endif


extern "C" void HAL_Delay(uint32_t delay) {

	while (delay) {
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
			delay--;
	}
}
