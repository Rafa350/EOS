#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"


/**
  * @brief  USBD_Init
  *         Initialize the device stack and load the class driver
  * @param  pdev: device instance
  * @param  pdesc: Descriptor structure address
  * @param  id: Low level core index
  * @retval status: USBD Status
  */
USBD_StatusTypeDef USBD_Init(
	USBD_HandleTypeDef *pdev,
    USBD_DescriptorsTypeDef *pdesc,
	uint8_t id) {

	if (pdev == nullptr)
		return USBD_FAIL;

	pdev->dev_state = USBD_STATE_DEFAULT;
	pdev->id = id;

	return USBD_LL_Init(pdev);
}

/**
  * @brief  USBD_DeInit
  *         De-Initialize the device library
  * @param  pdev: device instance
  * @retval status: USBD Status
  */
USBD_StatusTypeDef USBD_DeInit(
	USBD_HandleTypeDef *pdev) {

	/* Disconnect the USB Device */
	USBD_LL_Stop(pdev);

	/* Set Default State */
	pdev->dev_state = USBD_STATE_DEFAULT;

	auto classe = pdev->_instance->getClass();
	if (classe != nullptr)
		classe->classDeinitialize((uint8_t)pdev->dev_config);

	/* DeInitialize low level driver */
	return USBD_LL_DeInit(pdev);
}


/**
  * @brief  USBD_RunTestMode
  *         Launch test mode process
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_RunTestMode(USBD_HandleTypeDef *pdev)
{
#ifdef USBD_HS_TESTMODE_ENABLE
  USBD_StatusTypeDef ret;

  /* Run USB HS test mode */
  ret = USBD_LL_SetTestMode(pdev, pdev->dev_test_mode);

  return ret;
#else
  /* Prevent unused argument compilation warning */
  UNUSED(pdev);

  return USBD_OK;
#endif /* USBD_HS_TESTMODE_ENABLE */
}


/**
  * @brief  USBD_SetClassConfig
  *        Configure device and start the interface
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
/*USBD_StatusTypeDef USBD_SetClassConfig(
	USBD_HandleTypeDef *pdev,
	uint8_t configIdx) {

	return pdev->_instance->setClassConfig(configIdx) ? USBD_OK : USBD_FAIL;
}*/


/**
  * @brief  USBD_ClrClassConfig
  *         Clear current configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
/*USBD_StatusTypeDef USBD_ClrClassConfig(
	USBD_HandleTypeDef *pdev,
	uint8_t configIdx) {

	return pdev->_instance->clearClassConfig(configIdx) ? USBD_OK : USBD_FAIL;
}*/


/**
  * @brief  USBD_LL_SetupStage
  *         Handle the setup stage
  * @param  pdev: device instance
  * @param  psetup: setup packet buffer pointer
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_SetupStage(
	USBD_HandleTypeDef *pdev,
	uint8_t *psetup) {

	return pdev->_instance->setupStage(psetup) ? USBD_OK : USBD_FAIL;
}


/**
  * @brief  USBD_LL_DataOutStage
  *         Handle data OUT stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @param  pdata: data pointer
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_DataOutStage(
	USBD_HandleTypeDef *pdev,
    uint8_t epnum,
	uint8_t *pdata) {

#if 0
	if (epnum == 0) {

		USBD_EndpointTypeDef *pep = &pdev->ep_out[0];

		if (pdev->ep0_state == USBD_EP0_DATA_OUT) {
			if (pep->rem_length > pep->maxpacket) {
				pep->rem_length -= pep->maxpacket;
				pep->pbuffer += pep->maxpacket;

				USBD_CtlContinueRx(pdev, pep->pbuffer, MAX(pep->rem_length, pep->maxpacket));
			}
			else {

				eos::USBDeviceClass *cls = nullptr;

				// Find the class ID relative to the current request
				//
				switch (pdev->request.requestType & 0x1F) {
					case USB_REQ_RECIPIENT_DEVICE:
						/* Device requests must be managed by the first instantiated class
			   	   	   	   (or duplicated by all classes for simplicity) */
						cls = pdev->_instance->getClass();
						break;

					case USB_REQ_RECIPIENT_INTERFACE:
						cls = pdev->_instance->getClassFromInterface(LOBYTE(pdev->request.index));
						break;

					case USB_REQ_RECIPIENT_ENDPOINT:
						cls = pdev->_instance->getClassFromEndPoint(eos::EpAddr(LOBYTE(pdev->request.index)));
						break;
				}

				if (cls != nullptr) {
					if (pdev->dev_state == USBD_STATE_CONFIGURED)
						cls->classEP0RxReady();
				}

				USBD_CtlSendStatus(pdev);
			}
		}
	}
	else
#endif
		return pdev->_instance->dataOutStage(eos::EpAddr(epnum)) ? USBD_OK : USBD_FAIL;

	return USBD_OK;
}


/**
  * @brief  USBD_LL_DataInStage
  *         Handle data in stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @param  pdata: data pointer
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_DataInStage(
	USBD_HandleTypeDef *pdev,
    uint8_t epnum,
	uint8_t *pdata) {
#if 0
	if (epnum == 0) {

		USBD_EndpointTypeDef *pep = &pdev->ep_in[0];

		if (pdev->ep0_state == USBD_EP0_DATA_IN) {
			if (pep->rem_length > pep->maxpacket) {
				pep->rem_length -= pep->maxpacket;
				pep->pbuffer += pep->maxpacket;

				USBD_CtlContinueSendData(pdev, pep->pbuffer, pep->rem_length);

				USBD_LL_PrepareReceive(pdev, 0U, NULL, 0U);
			}
			else {
				if ((pep->maxpacket == pep->rem_length) &&
					(pep->total_length >= pep->maxpacket) &&
					(pep->total_length < pdev->ep0_data_len)) {

					USBD_CtlContinueSendData(pdev, NULL, 0U);
					pdev->ep0_data_len = 0U;

					USBD_LL_PrepareReceive(pdev, 0U, NULL, 0U);
				}
				else {
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						//pdev->classId = 0;
						pdev->_instance->getClass()->classEP0TxSent();
					}
					USBD_LL_StallEP(pdev, 0x80U);
					USBD_CtlReceiveStatus(pdev);
				}
			}
		}

		if (pdev->dev_test_mode != 0U) {
			USBD_RunTestMode(pdev);
			pdev->dev_test_mode = 0;
		}
	}
	else
#endif
		return (USBD_StatusTypeDef) pdev->_instance->dataInStage(eos::EpAddr(epnum)) ? USBD_OK : USBD_FAIL;

	return USBD_OK;
}


/**
  * @brief  USBD_LL_Reset
  *         Handle Reset event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Reset(
	USBD_HandleTypeDef *pdev) {

	USBD_StatusTypeDef ret = USBD_OK;

	pdev->dev_state = USBD_STATE_DEFAULT;
	pdev->ep0_state = USBD_EP0_IDLE;
	pdev->dev_config = 0;
	pdev->dev_remote_wakeup = 0;
	pdev->dev_test_mode = 0;

	if (pdev->_instance->getClass()!= nullptr)
		if (pdev->_instance->getClass()->classDeinitialize((uint8_t)pdev->dev_config) != USBD_OK)
			ret = USBD_FAIL;

	USBD_LL_OpenEP(pdev, 0x00U, USBD_EP_TYPE_CTRL, USB_MAX_EP0_SIZE);
	pdev->ep_out[0x00U & 0xFU].is_used = 1U;

	pdev->ep_out[0].maxpacket = USB_MAX_EP0_SIZE;

	USBD_LL_OpenEP(pdev, 0x80U, USBD_EP_TYPE_CTRL, USB_MAX_EP0_SIZE);
	pdev->ep_in[0x80U & 0xFU].is_used = 1U;

	pdev->ep_in[0].maxpacket = USB_MAX_EP0_SIZE;

	return ret;
}

/**
  * @brief  USBD_LL_SetSpeed
  *         Handle Reset event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_SetSpeed(
	USBD_HandleTypeDef *pdev,
    USBD_SpeedTypeDef speed) {

	pdev->dev_speed = speed;

	return USBD_OK;
}

/**
  * @brief  USBD_LL_Suspend
  *         Handle Suspend event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Suspend(
	USBD_HandleTypeDef *pdev) {

	if (pdev->dev_state != USBD_STATE_SUSPENDED)
		pdev->dev_old_state = pdev->dev_state;

	pdev->dev_state = USBD_STATE_SUSPENDED;

	return USBD_OK;
}

/**
  * @brief  USBD_LL_Resume
  *         Handle Resume event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Resume(
	USBD_HandleTypeDef *pdev) {

	if (pdev->dev_state == USBD_STATE_SUSPENDED)
		pdev->dev_state = pdev->dev_old_state;

	return USBD_OK;
}

/**
  * @brief  USBD_LL_SOF
  *         Handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_SOF(
	USBD_HandleTypeDef *pdev) {

	/* The SOF event can be distributed for all classes that support it */
	if (pdev->dev_state == USBD_STATE_CONFIGURED) {
		if (pdev->_instance->getClass() != nullptr) {
			pdev->_instance->getClass()->classSOF();
		}
	}

  	return USBD_OK;
}

/**
  * @brief  USBD_LL_IsoINIncomplete
  *         Handle iso in incomplete event
  * @param  pdev: device instance
  * @param  epnum: Endpoint number
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_IsoINIncomplete(
	USBD_HandleTypeDef *pdev,
    uint8_t epnum) {

	auto epAddr = eos::EpAddr(epnum);
	auto cls = pdev->_instance->getClassFromEndPoint(epAddr);
	if (cls == nullptr)
		return USBD_FAIL;

	if (pdev->dev_state == USBD_STATE_CONFIGURED)
		cls->classIsoINIncomplete(epAddr);

	return USBD_OK;
}

/**
  * @brief  USBD_LL_IsoOUTIncomplete
  *         Handle iso out incomplete event
  * @param  pdev: device instance
  * @param  epnum: Endpoint number
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_IsoOUTIncomplete(
	USBD_HandleTypeDef *pdev,
    uint8_t epnum) {

	auto epAddr = eos::EpAddr(epnum);
	auto cls = pdev->_instance->getClassFromEndPoint(epAddr);
	if (cls == nullptr)
		return USBD_FAIL;

	if (pdev->dev_state == USBD_STATE_CONFIGURED)
		cls->classIsoOUTIncomplete(epAddr);

	return USBD_OK;
}

/**
  * @brief  USBD_LL_DevConnected
  *         Handle device connection event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_DevConnected(
	USBD_HandleTypeDef *pdev) {

	return USBD_OK;
}


/**
  * @brief  USBD_LL_DevDisconnected
  *         Handle device disconnection event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_DevDisconnected(
	USBD_HandleTypeDef *pdev) {

	USBD_StatusTypeDef   ret = USBD_OK;

	pdev->dev_state = USBD_STATE_DEFAULT;

	if (pdev->_instance->getClass() != nullptr) {
		if (pdev->_instance->getClass()->classDeinitialize((uint8_t)pdev->dev_config) != 0U) {
			ret = USBD_FAIL;
		}
	}

	return ret;
}


