#pragma once
#ifndef __st_usbd_ioreq__
#define __st_usbd_ioreq__


#include  "Controllers/USBDevice/ST/st_usbd_def.h"
#include  "Controllers/USBDevice/ST/st_usbd_core.h"


USBD_StatusTypeDef USBD_CtlSendData(USBD_HandleTypeDef *pdev, uint8_t *pbuf, uint32_t len);
USBD_StatusTypeDef USBD_CtlContinueSendData(USBD_HandleTypeDef *pdev, uint8_t *pbuf, uint32_t len);
USBD_StatusTypeDef USBD_CtlPrepareRx(USBD_HandleTypeDef *pdev, uint8_t *pbuf, uint32_t len);
USBD_StatusTypeDef USBD_CtlContinueRx(USBD_HandleTypeDef *pdev, uint8_t *pbuf, uint32_t len);
USBD_StatusTypeDef USBD_CtlSendStatus(USBD_HandleTypeDef *pdev);
USBD_StatusTypeDef USBD_CtlReceiveStatus(USBD_HandleTypeDef *pdev);
uint32_t USBD_GetRxCount(USBD_HandleTypeDef *pdev, uint8_t ep_addr);


#endif // __st_usbd_ioreq__
