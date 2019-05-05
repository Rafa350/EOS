#include "eos.h"
#include "Controllers/Usb/STM32/usbd.h"
#include "HAL/halUSB.h"


#ifdef USE_USB_DEVICE0
static PCD_HandleTypeDef hpcd_FS;
#endif
#ifdef USE_USB_DEVICE1
static PCD_HandleTypeDef hpcd_HS;
#endif


/*******************************************************************************
                       LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/

/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(
	USBD_HandleTypeDef *pdev) {

#ifdef USE_USB_DEVICE0
	if (pdev->id == HAL_USB_PORT_FS) {

		// Set LL Driver parameters
		//
		hpcd_FS.Instance = USB_OTG_FS;
		hpcd_FS.Init.dev_endpoints = 4;
		hpcd_FS.Init.use_dedicated_ep1 = 0;
		hpcd_FS.Init.ep0_mps = 0x40;
		hpcd_FS.Init.dma_enable = 0;
		hpcd_FS.Init.low_power_enable = 0;
		hpcd_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
		hpcd_FS.Init.Sof_enable = 0;
		hpcd_FS.Init.speed = PCD_SPEED_FULL;
		hpcd_FS.Init.vbus_sensing_enable = 0;
		hpcd_FS.Init.lpm_enable = 0;

		// Link The driver to the stack
		//
		hpcd_FS.pData = pdev;
		pdev->pData = &hpcd_FS;

		// Initialize LL Driver
		//
		HAL_PCD_Init(&hpcd_FS);

		HAL_PCDEx_SetRxFiFo(&hpcd_FS, 0x80);
		HAL_PCDEx_SetTxFiFo(&hpcd_FS, 0, 0x40);
		HAL_PCDEx_SetTxFiFo(&hpcd_FS, 1, 0x80);
	}
#endif

#ifdef USE_USB_DEVICE1
	if (pdev->id == >HAL_USB_PORT_HS) {

		/* Set LL Driver parameters */
		hpcd_HS.Instance = USB_OTG_HS;
		hpcd_HS.Init.dev_endpoints = 6;
		hpcd_HS.Init.use_dedicated_ep1 = 0;
		hpcd_HS.Init.ep0_mps = 0x40;
		hpcd_HS.Init.dma_enable = 0;
		hpcd_HS.Init.low_power_enable = 0;
		hpcd_HS.Init.lpm_enable = 0;
#ifdef USB_USE_ULPI_PHY
		hpcd_HS.Init.phy_itface = PCD_PHY_ULPI;
		hpcd_HS.Init.speed = PCD_SPEED_HIGH;
#else
		hpcd_HS.Init.phy_itface = PCD_PHY_EMBEDDED;
		hpcd_HS.Init.speed = PCD_SPEED_HIGH_IN_FULL;
#endif
		hpcd_HS.Init.Sof_enable = 0;
		hpcd_HS.Init.vbus_sensing_enable = 0;

		/* Link The driver to the stack */
		hpcd_HS.pData = pdev;
		pdev->pData = &hpcd_HS;

		/* Initialize LL Driver */
		HAL_PCD_Init(&hpcd_HS);

		HAL_PCDEx_SetRxFiFo(&hpcd_HS, 0x200);
		HAL_PCDEx_SetTxFiFo(&hpcd_HS, 0, 0x80);
		HAL_PCDEx_SetTxFiFo(&hpcd_HS, 1, 0x174);
	}
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

	HAL_PCD_DeInit(pdev->pData);
	return USBD_OK;
}

/**
  * @brief  Starts the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(
	USBD_HandleTypeDef *pdev) {

	HAL_PCD_Start(pdev->pData);
	return USBD_OK;
}

/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(
	USBD_HandleTypeDef *pdev) {

	HAL_PCD_Stop(pdev->pData);
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

	HAL_PCD_EP_Open(pdev->pData, ep_addr, ep_mps, ep_type);
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

	HAL_PCD_EP_Close(pdev->pData, ep_addr);
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

	HAL_PCD_EP_Flush(pdev->pData, ep_addr);
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

	HAL_PCD_EP_SetStall(pdev->pData, ep_addr);
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

	HAL_PCD_EP_ClrStall(pdev->pData, ep_addr);
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

	PCD_HandleTypeDef *hpcd = pdev->pData;

	if ((ep_addr & 0x80) == 0x80)
		return hpcd->IN_ep[ep_addr & 0x7F].is_stall;

	else
		return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
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

	HAL_PCD_SetAddress(pdev->pData, dev_addr);
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
    uint16_t size) {

	HAL_PCD_EP_Transmit(pdev->pData, ep_addr, pbuf, size);
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
	uint16_t size) {

	HAL_PCD_EP_Receive(pdev->pData, ep_addr, pbuf, size);
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

	return HAL_PCD_EP_GetRxCount(pdev->pData, ep_addr);
}

/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(
	uint32_t Delay) {

	HAL_Delay(Delay);
}
