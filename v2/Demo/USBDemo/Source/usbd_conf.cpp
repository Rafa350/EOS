#include "eos.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"


PCD_HandleTypeDef hpcd;


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del modul PDC
/// \param    hpcd: El handler del modul.
///
void HAL_PCD_MspInit(
	PCD_HandleTypeDef *hpcd) {

#ifdef USE_USB_FS
	GPIO_InitTypeDef  GPIO_InitStruct;

	if (hpcd->Instance == USB_OTG_FS) {

		// Configure USB FS GPIOs
		//
		__HAL_RCC_GPIOA_CLK_ENABLE();

		// Configure DM DP Pins
		//
		GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// Enable USB FS Clock
		//
		__HAL_RCC_USB_OTG_FS_CLK_ENABLE();

		// Set USBFS Interrupt priority
		//
		HAL_NVIC_SetPriority(OTG_FS_IRQn, 7, 0);

		// Enable USBFS Interrupt
		//
		HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
	}
#endif

#ifdef USE_USB_HS
	if (hpcd->Instance == USB_OTG_HS) {

		/* Configure USB FS GPIOs */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();

		/* CLK */
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* D0 */
		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* D1 D2 D3 D4 D5 D6 D7 */
		GPIO_InitStruct.Pin = GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* STP */
		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* NXT */
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		/* DIR */
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		__HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();

		/* Enable USB HS Clocks */
		__HAL_RCC_USB_OTG_HS_CLK_ENABLE();

		/* Set USBHS Interrupt to the lowest priority */
		HAL_NVIC_SetPriority(OTG_HS_IRQn, 7, 0);

		/* Enable USBHS Interrupt */
		HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el modul PDC
/// \param    hpdc: Handler del modul.
///
void HAL_PCD_MspDeInit(
	PCD_HandleTypeDef *hpcd) {

#ifdef USE_USB_FS
	if (hpcd->Instance == USB_OTG_FS) {

		// Disable USB FS Clock
		//
		__HAL_RCC_USB_OTG_FS_CLK_DISABLE();
		__HAL_RCC_SYSCFG_CLK_DISABLE();
	}
#endif

#ifdef USE_USB_HS
	if (hpcd->Instance == USB_OTG_HS) {

		// Disable USB HS Clocks
		//
		__HAL_RCC_USB_OTG_HS_CLK_DISABLE();
		__HAL_RCC_SYSCFG_CLK_DISABLE();
	}
#endif
}


/*************************************************************************
 *       LL Driver Callbacks (PCD -> USB Device Library)
 ************************************************************************/

/**
  * @brief  SetupStage callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SetupStageCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_SetupStage((USBD_HandleTypeDef*) hpcd->pData, (uint8_t *)hpcd->Setup);
}


/**
  * @brief  DataOut Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataOutStageCallback(
	PCD_HandleTypeDef *hpcd,
	uint8_t epnum) {

	USBD_LL_DataOutStage((USBD_HandleTypeDef*) hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}


/**
  * @brief  DataIn Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataInStageCallback(
	PCD_HandleTypeDef *hpcd,
	uint8_t epnum) {

	USBD_LL_DataInStage((USBD_HandleTypeDef*) hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}


/**
  * @brief  SOF callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SOFCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_SOF((USBD_HandleTypeDef*) hpcd->pData);
}


/**
  * @brief  Reset callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResetCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_SpeedTypeDef speed = USBD_SPEED_FULL;
	switch(hpcd->Init.speed) {
		case PCD_SPEED_HIGH:
			speed = USBD_SPEED_HIGH;
			break;

		case PCD_SPEED_FULL:
			speed = USBD_SPEED_FULL;
			break;
	}

	USBD_LL_Reset((USBD_HandleTypeDef*) hpcd->pData);
	USBD_LL_SetSpeed((USBD_HandleTypeDef*) hpcd->pData, speed);
}


/**
  * @brief  Suspend callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SuspendCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_Suspend((USBD_HandleTypeDef*) hpcd->pData);
}

/**
  * @brief  Resume callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResumeCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_Resume((USBD_HandleTypeDef*) hpcd->pData);
}


/**
  * @brief  ISOOUTIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOOUTIncompleteCallback(
	PCD_HandleTypeDef *hpcd,
	uint8_t epnum) {

	USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef*) hpcd->pData, epnum);
}


/**
  * @brief  ISOINIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOINIncompleteCallback(
	PCD_HandleTypeDef *hpcd,
	uint8_t epnum) {

	USBD_LL_IsoINIncomplete((USBD_HandleTypeDef*) hpcd->pData, epnum);
}


/**
  * @brief  ConnectCallback callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ConnectCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_DevConnected((USBD_HandleTypeDef*) hpcd->pData);
}


/**
  * @brief  Disconnect callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_DisconnectCallback(
	PCD_HandleTypeDef *hpcd) {

	USBD_LL_DevDisconnected((USBD_HandleTypeDef*) hpcd->pData);
}


/*************************************************************************
 *       LL Driver Interface (USB Device Library --> PCD)
 ************************************************************************/

/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(
	USBD_HandleTypeDef *pdev) {
#ifdef USE_USB_FS

  /* Set LL Driver parameters */
  hpcd.Instance = USB_OTG_FS;
  hpcd.Init.dev_endpoints = 6;
  hpcd.Init.use_dedicated_ep1 = 0;
  hpcd.Init.dma_enable = 0;
  hpcd.Init.low_power_enable = 0;
  hpcd.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd.Init.Sof_enable = 0;
  hpcd.Init.speed = PCD_SPEED_FULL;
  hpcd.Init.vbus_sensing_enable = 0;
  hpcd.Init.lpm_enable = 0;

  /* Link The driver to the stack */
  hpcd.pData = pdev;
  pdev->pData = &hpcd;

  /* Initialize LL Driver */
  HAL_PCD_Init(&hpcd);

  HAL_PCDEx_SetRxFiFo(&hpcd, 0x80);
  HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40);
  HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x80);
#endif


#ifdef USE_USB_HS
  /* Set LL Driver parameters */
  hpcd.Instance = USB_OTG_HS;
  hpcd.Init.dev_endpoints = 9;
  hpcd.Init.use_dedicated_ep1 = 0;

  /* Be aware that enabling DMA mode will result in data being sent only by
  multiple of 4 packet sizes. This is due to the fact that USB DMA does
  not allow sending data from non word-aligned addresses.
  For this specific application, it is advised to not enable this option
  unless required. */
  hpcd.Init.dma_enable = 0;
  hpcd.Init.low_power_enable = 0;
  hpcd.Init.lpm_enable = 0;
  hpcd.Init.phy_itface = PCD_PHY_ULPI;
  hpcd.Init.Sof_enable = 0;
  hpcd.Init.speed = PCD_SPEED_HIGH;
  hpcd.Init.vbus_sensing_enable = 1;

  /* Link The driver to the stack */
  hpcd.pData = pdev;
  pdev->pData = &hpcd;

  /* Initialize LL Driver */
  HAL_PCD_Init(&hpcd);

  HAL_PCDEx_SetRxFiFo(&hpcd, 0x200);
  HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40);
  HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x100);
#endif

  return USBD_OK;
}


/**
  * @brief  De-Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_DeInit(
	USBD_HandleTypeDef *pdev) {

	HAL_PCD_DeInit((PCD_HandleTypeDef*) pdev->pData);
	return USBD_OK;
}


/**
  * @brief  Starts the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(
	USBD_HandleTypeDef *pdev) {

	HAL_PCD_Start((PCD_HandleTypeDef*) pdev->pData);
	return USBD_OK;
}


/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(
	USBD_HandleTypeDef *pdev) {

	HAL_PCD_Stop((PCD_HandleTypeDef*) pdev->pData);
	return USBD_OK;
}


/**
  * @brief  Opens an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  ep_type: Endpoint Type
  * @param  ep_mps: Endpoint Max Packet Size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(
	USBD_HandleTypeDef *pdev,
    uint8_t ep_addr,
    uint8_t ep_type,
    uint16_t ep_mps) {

	HAL_PCD_EP_Open((PCD_HandleTypeDef*) pdev->pData, ep_addr, ep_mps, ep_type);
	return USBD_OK;
}


/**
  * @brief  Closes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	HAL_PCD_EP_Close((PCD_HandleTypeDef*)pdev->pData, ep_addr);
	return USBD_OK;
}


/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	HAL_PCD_EP_Flush((PCD_HandleTypeDef*)pdev->pData, ep_addr);
	return USBD_OK;
}


/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_StallEP(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	HAL_PCD_EP_SetStall((PCD_HandleTypeDef*)pdev->pData, ep_addr);
	return USBD_OK;
}


/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	HAL_PCD_EP_ClrStall((PCD_HandleTypeDef*)pdev->pData, ep_addr);
	return USBD_OK;
}


/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef*) pdev->pData;

	if ((ep_addr & 0x80) == 0x80)
		return hpcd->IN_ep[ep_addr & 0x0F].is_stall;
	else
		return hpcd->OUT_ep[ep_addr & 0x0F].is_stall;
}


/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(
	USBD_HandleTypeDef *pdev,
	uint8_t dev_addr) {

	HAL_PCD_SetAddress((PCD_HandleTypeDef*)pdev->pData, dev_addr);
	return USBD_OK;
}


/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Transmit(
	USBD_HandleTypeDef *pdev,
    uint8_t ep_addr,
    uint8_t *pbuf,
    uint32_t size) {

	HAL_PCD_EP_Transmit((PCD_HandleTypeDef*) pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}


/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(
	USBD_HandleTypeDef *pdev,
    uint8_t ep_addr,
    uint8_t *pbuf,
    uint32_t size) {

	HAL_PCD_EP_Receive((PCD_HandleTypeDef*) pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}


/**
  * @brief  Returns the last transferred packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Received Data Size
  */
uint32_t USBD_LL_GetRxDataSize(
	USBD_HandleTypeDef *pdev,
	uint8_t ep_addr) {

	return HAL_PCD_EP_GetRxCount((PCD_HandleTypeDef*) pdev->pData, ep_addr);
}


/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(
	uint32_t delay) {

	HAL_Delay(delay);
}
