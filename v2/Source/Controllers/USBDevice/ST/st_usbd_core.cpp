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

	USBD_StatusTypeDef ret;

	/* Check whether the USB Host handle is valid */
	if (pdev == NULL) {
#if (USBD_DEBUG_LEVEL > 1U)
		USBD_ErrLog("Invalid Device handle");
#endif /* (USBD_DEBUG_LEVEL > 1U) */
		return USBD_FAIL;
	}

	pdev->pClass[0] = NULL;
	pdev->pUserData[0] = NULL;
	pdev->pConfDesc = NULL;

	pdev->pDesc = pdesc;

	pdev->dev_state = USBD_STATE_DEFAULT;
	pdev->id = id;

	ret = USBD_LL_Init(pdev);

	return ret;
}

/**
  * @brief  USBD_DeInit
  *         De-Initialize the device library
  * @param  pdev: device instance
  * @retval status: USBD Status
  */
USBD_StatusTypeDef USBD_DeInit(
	USBD_HandleTypeDef *pdev) {

	USBD_StatusTypeDef ret;

	/* Disconnect the USB Device */
	USBD_LL_Stop(pdev);

	/* Set Default State */
	pdev->dev_state = USBD_STATE_DEFAULT;

	/* Free Class Resources */
	 if (pdev->pClass[0] != nullptr) {
		 pdev->pClass[0]->classDeinit((uint8_t)pdev->dev_config);
	 }
	 pdev->pUserData[0] = nullptr;


	 /* Free Device descriptors resources */
	 pdev->pDesc = nullptr;
	 pdev->pConfDesc = nullptr;

	 /* DeInitialize low level driver */
	 ret = USBD_LL_DeInit(pdev);

	 return ret;
}

/**
  * @brief  USBD_RegisterClass
  *         Link class driver to Device Core.
  * @param  pdev: Device Handle
  * @param  pclass: Class handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_RegisterClass(
	USBD_HandleTypeDef *pdev,
	eos::USBDeviceClass *pclass) {

	uint16_t len = 0U;

	if (pclass == NULL) {
#if (USBD_DEBUG_LEVEL > 1U)
		USBD_ErrLog("Invalid Class handle");
#endif /* (USBD_DEBUG_LEVEL > 1U) */
		return USBD_FAIL;
	}

	/* link the class to the USB Device handle */
	pdev->pClass[0] = pclass;

	/* Get Device Configuration Descriptor */
#ifdef USE_USB_HS
    if (pdev->pClass[pdev->classId]->GetHSConfigDescriptor != nullptr)
    	pdev->pConfDesc = (void *)pdev->pClass[pdev->classId]->GetHSConfigDescriptor(&len);
#else /* Default USE_USB_FS */
    pdev->pConfDesc = (void *)pdev->pClass[pdev->classId]->classGetFSConfigurationDescriptor(&len);
#endif /* USE_USB_FS */

    /* Increment the NumClasses */
    pdev->NumClasses++;

    return USBD_OK;
}


#if (USBD_USER_REGISTER_CALLBACK == 1U)
/**
  * @brief  USBD_RegisterDevStateCallback
  * @param  pdev : Device Handle
  * @param  pUserCallback: User Callback
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_RegisterDevStateCallback(USBD_HandleTypeDef *pdev, USBD_DevStateCallbackTypeDef pUserCallback)
{
  pdev->DevStateCallback = pUserCallback;

  return USBD_OK;
}
#endif /* USBD_USER_REGISTER_CALLBACK */

/**
  * @brief  USBD_Start
  *         Start the USB Device Core.
  * @param  pdev: Device Handle
  * @retval USBD Status
  */
/*
USBD_StatusTypeDef USBD_Start(
	USBD_HandleTypeDef *pdev) {

	return USBD_LL_Start(pdev);
}
*/
/**
  * @brief  USBD_Stop
  *         Stop the USB Device Core.
  * @param  pdev: Device Handle
  * @retval USBD Status
  */
/*
USBD_StatusTypeDef USBD_Stop
	(USBD_HandleTypeDef *pdev) {

	USBD_LL_Stop(pdev);

	if (pdev->pClass[0] != NULL) {
		pdev->pClass[0]->classDeinit((uint8_t)pdev->dev_config);
	}

  return USBD_OK;
}
*/

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

USBD_StatusTypeDef USBD_SetClassConfig(
	USBD_HandleTypeDef *pdev,
	uint8_t cfgidx) {

	USBD_StatusTypeDef ret = USBD_OK;

	if (pdev->pClass[0] != NULL) {
		/* Set configuration and Start the Class */
		ret = (USBD_StatusTypeDef)pdev->pClass[0]->classInit(cfgidx);
	}

	return ret;
}

/**
  * @brief  USBD_ClrClassConfig
  *         Clear current configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
USBD_StatusTypeDef USBD_ClrClassConfig(
	USBD_HandleTypeDef *pdev,
	uint8_t cfgidx) {

	USBD_StatusTypeDef ret = USBD_OK;

	/* Clear configuration  and De-initialize the Class process */
	if (pdev->pClass[0]->classDeinit(cfgidx) != 0U) {
		ret = USBD_FAIL;
	}

	return ret;
}


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

	USBD_StatusTypeDef ret;

	USBD_ParseSetupRequest(&pdev->request, psetup);

	pdev->ep0_state = USBD_EP0_SETUP;

	pdev->ep0_data_len = pdev->request.length;

	switch (pdev->request.requestType & 0x1FU) {

		case USB_REQ_RECIPIENT_DEVICE:
		  ret = USBD_StdDevReq(pdev, &pdev->request);
		  break;

		case USB_REQ_RECIPIENT_INTERFACE:
		  ret = USBD_StdItfReq(pdev, &pdev->request);
		  break;

		case USB_REQ_RECIPIENT_ENDPOINT:
		  ret = USBD_StdEPReq(pdev, &pdev->request);
		  break;

		default:
		  ret = USBD_LL_StallEP(pdev, (pdev->request.requestType & 0x80U));
		  break;
	}

	return ret;
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

	USBD_EndpointTypeDef *pep;
	USBD_StatusTypeDef ret = USBD_OK;
	uint8_t idx;

	if (epnum == 0) {
		pep = &pdev->ep_out[0];

		if (pdev->ep0_state == USBD_EP0_DATA_OUT) {
			if (pep->rem_length > pep->maxpacket) {
				pep->rem_length -= pep->maxpacket;
				pep->pbuffer += pep->maxpacket;

				USBD_CtlContinueRx(pdev, pep->pbuffer, MAX(pep->rem_length, pep->maxpacket));
			}
			else {

				// Find the class ID relative to the current request
				//
				switch (pdev->request.requestType & 0x1FU) {
					case USB_REQ_RECIPIENT_DEVICE:
						/* Device requests must be managed by the first instantiated class
			   	   	   	   (or duplicated by all classes for simplicity) */
						idx = 0U;
						break;

					case USB_REQ_RECIPIENT_INTERFACE:
						idx = USBD_CoreFindIF(pdev, LOBYTE(pdev->request.index));
						break;

					case USB_REQ_RECIPIENT_ENDPOINT:
						idx = USBD_CoreFindEP(pdev, LOBYTE(pdev->request.index));
						break;

					default:
						/* Back to the first class in case of doubt */
						idx = 0U;
						break;
				}

				if (idx < USBD_MAX_SUPPORTED_CLASS) {

					// Setup the class ID and route the request to the relative class function
					//
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						pdev->classId = idx;
						pdev->pClass[idx]->classEP0RxReady();
					}
				}

				USBD_CtlSendStatus(pdev);
			}
		}
	}
	else {
		// Get the class index relative to this interface
		//
		idx = USBD_CoreFindEP(pdev, (epnum & 0x7FU));

		if (((uint16_t)idx != 0xFFU) && (idx < USBD_MAX_SUPPORTED_CLASS)) {
			// Call the class data out function to manage the request
			//
			if (pdev->dev_state == USBD_STATE_CONFIGURED) {
				pdev->classId = idx;
				ret = (USBD_StatusTypeDef)pdev->pClass[idx]->classDataOut(epnum);
			}
			if (ret != USBD_OK) {
				return ret;
			}
		}
	}

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

	USBD_EndpointTypeDef *pep;
	USBD_StatusTypeDef ret;
	uint8_t idx;

	if (epnum == 0U) {

		pep = &pdev->ep_in[0];

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
						pdev->classId = 0U;
						pdev->pClass[0]->classEP0TxSent();
					}
					USBD_LL_StallEP(pdev, 0x80U);
					USBD_CtlReceiveStatus(pdev);
				}
			}
		}

		if (pdev->dev_test_mode != 0U) {
			USBD_RunTestMode(pdev);
			pdev->dev_test_mode = 0U;
		}
	}
	else {
		idx = USBD_CoreFindEP(pdev, ((uint8_t)epnum | 0x80U));

		if (((uint16_t)idx != 0xFFU) && (idx < USBD_MAX_SUPPORTED_CLASS)) {
			if (pdev->dev_state == USBD_STATE_CONFIGURED) {
				pdev->classId = idx;
				ret = (USBD_StatusTypeDef)pdev->pClass[idx]->classDataIn(epnum);
				if (ret != USBD_OK)
					return ret;
			}
		}
	}

	return USBD_OK;
}


/**
  * @brief  USBD_LL_Reset
  *         Handle Reset event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Reset(USBD_HandleTypeDef *pdev)
{
  USBD_StatusTypeDef ret = USBD_OK;

  /* Upon Reset call user call back */
  pdev->dev_state = USBD_STATE_DEFAULT;
  pdev->ep0_state = USBD_EP0_IDLE;
  pdev->dev_config = 0U;
  pdev->dev_remote_wakeup = 0U;
  pdev->dev_test_mode = 0U;

#ifdef USE_USBD_COMPOSITE
  /* Parse the table of classes in use */
  for (uint32_t i = 0U; i < USBD_MAX_SUPPORTED_CLASS; i++)
  {
    /* Check if current class is in use */
    if ((pdev->tclasslist[i].Active) == 1U)
    {
      if (pdev->pClass[i] != NULL)
      {
        pdev->classId = i;
        /* Clear configuration  and De-initialize the Class process*/

        if (pdev->pClass[i]->DeInit != NULL)
        {
          if (pdev->pClass[i]->DeInit(pdev, (uint8_t)pdev->dev_config) != USBD_OK)
          {
            ret = USBD_FAIL;
          }
        }
      }
    }
  }
#else

  if (pdev->pClass[0] != NULL)
	  if (pdev->pClass[0]->classDeinit((uint8_t)pdev->dev_config) != USBD_OK)
		  ret = USBD_FAIL;
#endif /* USE_USBD_COMPOSITE */

  /* Open EP0 OUT */
  (void)USBD_LL_OpenEP(pdev, 0x00U, USBD_EP_TYPE_CTRL, USB_MAX_EP0_SIZE);
  pdev->ep_out[0x00U & 0xFU].is_used = 1U;

  pdev->ep_out[0].maxpacket = USB_MAX_EP0_SIZE;

  /* Open EP0 IN */
  (void)USBD_LL_OpenEP(pdev, 0x80U, USBD_EP_TYPE_CTRL, USB_MAX_EP0_SIZE);
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
USBD_StatusTypeDef USBD_LL_SetSpeed(USBD_HandleTypeDef *pdev,
                                    USBD_SpeedTypeDef speed)
{
  pdev->dev_speed = speed;

  return USBD_OK;
}

/**
  * @brief  USBD_LL_Suspend
  *         Handle Suspend event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Suspend(USBD_HandleTypeDef *pdev)
{
  if (pdev->dev_state != USBD_STATE_SUSPENDED)
  {
    pdev->dev_old_state = pdev->dev_state;
  }

  pdev->dev_state = USBD_STATE_SUSPENDED;

  return USBD_OK;
}

/**
  * @brief  USBD_LL_Resume
  *         Handle Resume event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_Resume(USBD_HandleTypeDef *pdev)
{
  if (pdev->dev_state == USBD_STATE_SUSPENDED)
  {
    pdev->dev_state = pdev->dev_old_state;
  }

  return USBD_OK;
}

/**
  * @brief  USBD_LL_SOF
  *         Handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
USBD_StatusTypeDef USBD_LL_SOF(USBD_HandleTypeDef *pdev) {

	/* The SOF event can be distributed for all classes that support it */
	if (pdev->dev_state == USBD_STATE_CONFIGURED) {
		if (pdev->pClass[0] != NULL) {
			pdev->pClass[0]->classSOF();
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
USBD_StatusTypeDef USBD_LL_IsoINIncomplete(USBD_HandleTypeDef *pdev,
                                           uint8_t epnum)
{
  if (pdev->pClass[pdev->classId] == NULL)
  {
    return USBD_FAIL;
  }

  if (pdev->dev_state == USBD_STATE_CONFIGURED)
  {
      pdev->pClass[pdev->classId]->classIsoINIncomplete(epnum);
  }

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

	if (pdev->pClass[pdev->classId] == NULL) {
		return USBD_FAIL;
	}

	if (pdev->dev_state == USBD_STATE_CONFIGURED) {
		pdev->pClass[pdev->classId]->classIsoOUTIncomplete(epnum);
	}

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

	/* Free Class Resources */
	pdev->dev_state = USBD_STATE_DEFAULT;

	if (pdev->pClass[0] != NULL) {
		if (pdev->pClass[0]->classDeinit((uint8_t)pdev->dev_config) != 0U) {
			ret = USBD_FAIL;
		}
	}

	return ret;
}

/**
  * @brief  USBD_CoreFindIF
  *         return the class index relative to the selected interface
  * @param  pdev: device instance
  * @param  index : selected interface number
  * @retval index of the class using the selected interface number. OxFF if no class found.
  */
uint8_t USBD_CoreFindIF(
	USBD_HandleTypeDef *pdev,
	uint8_t index) {

	return 0x00U;
}

/**
  * @brief  USBD_CoreFindEP
  *         return the class index relative to the selected endpoint
  * @param  pdev: device instance
  * @param  index : selected endpoint number
  * @retval index of the class using the selected endpoint number. 0xFF if no class found.
  */
uint8_t USBD_CoreFindEP(
	USBD_HandleTypeDef *pdev,
	uint8_t index) {

	return 0x00U;
}


/**
  * @brief  USBD_GetEpDesc
  *         This function return the Endpoint descriptor
  * @param  pdev: device instance
  * @param  pConfDesc:  pointer to Bos descriptor
  * @param  EpAddr:  endpoint address
  * @retval pointer to video endpoint descriptor
  */
void *USBD_GetEpDesc(
	uint8_t *pConfDesc,
	uint8_t EpAddr) {

	USBD_DescHeaderTypeDef *pdesc = (USBD_DescHeaderTypeDef *)(void *)pConfDesc;
	USBD_ConfigDescTypeDef *desc = (USBD_ConfigDescTypeDef *)(void *)pConfDesc;
	USBD_EpDescTypeDef *pEpDesc = NULL;
	uint16_t ptr;

	if (desc->wTotalLength > desc->bLength) {
		ptr = desc->bLength;
		while (ptr < desc->wTotalLength) {
			pdesc = USBD_GetNextDesc((uint8_t*) pdesc, &ptr);
			if (pdesc->bDescriptorType == USB_DESC_TYPE_ENDPOINT) {
				pEpDesc = (USBD_EpDescTypeDef*)(void *)pdesc;
				if (pEpDesc->bEndpointAddress == EpAddr) {
					break;
				}
				else {
					pEpDesc = nullptr;
				}
			}
		}
	}

	return pEpDesc;
}

/**
  * @brief  USBD_GetNextDesc
  *         This function return the next descriptor header
  * @param  buf: Buffer where the descriptor is available
  * @param  ptr: data pointer inside the descriptor
  * @retval next header
  */
USBD_DescHeaderTypeDef *USBD_GetNextDesc(
	uint8_t *pbuf,
	uint16_t *ptr) {

	USBD_DescHeaderTypeDef *pnext = (USBD_DescHeaderTypeDef *)(void *)pbuf;

	*ptr += pnext->bLength;
	pnext = (USBD_DescHeaderTypeDef *)(void *)(pbuf + pnext->bLength);

	return pnext;
}


