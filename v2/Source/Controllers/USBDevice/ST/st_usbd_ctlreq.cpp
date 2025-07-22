#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/ST/st_usbd_ioreq.h"


#ifndef USBD_MAX_STR_DESC_SIZ
#define USBD_MAX_STR_DESC_SIZ                          64U
#endif /* USBD_MAX_STR_DESC_SIZ */

static uint8_t USBD_GetLen(uint8_t *buf);


/**
  * @brief  USBD_ParseSetupRequest
  *         Copy buffer into setup structure
  * @param  req: usb request
  * @param  pdata: setup data pointer
  * @retval None
  */
void USBD_ParseSetupRequest(
	USBD_SetupReqTypedef *req,
	uint8_t *pdata)
{
  uint8_t *pbuff = pdata;

  req->requestType = *(uint8_t*)(pbuff);

  pbuff++;
  req->requestID = *(uint8_t*)(pbuff);

  pbuff++;
  req->value = SWAPBYTE(pbuff);

  pbuff++;
  pbuff++;
  req->index = SWAPBYTE(pbuff);

  pbuff++;
  pbuff++;
  req->length = SWAPBYTE(pbuff);
}


/**
  * @brief  USBD_CtlError
  *         Handle USB low level Error
  * @param  pdev: device instance
  * @param  req: usb request
  * @retval None
  */
void USBD_CtlError(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  UNUSED(req);

  (void)USBD_LL_StallEP(pdev, 0x80U);
  (void)USBD_LL_StallEP(pdev, 0U);
}


/**
  * @brief  USBD_GetString
  *         Convert Ascii string into unicode one
  * @param  desc : descriptor buffer
  * @param  unicode : Formatted string buffer (unicode)
  * @param  len : descriptor length
  * @retval None
  */
#if 0
void USBD_GetString(uint8_t *desc, uint8_t *unicode, uint16_t *len)
{
  uint8_t idx = 0U;
  uint8_t *pdesc;

  if (desc == NULL)
  {
    return;
  }

  pdesc = desc;
  *len = MIN(USBD_MAX_STR_DESC_SIZ, ((uint16_t)USBD_GetLen(pdesc) * 2U) + 2U);

  unicode[idx] = *(uint8_t *)len;
  idx++;
  unicode[idx] = USB_DESC_TYPE_STRING;
  idx++;

  while (*pdesc != (uint8_t)'\0')
  {
    unicode[idx] = *pdesc;
    pdesc++;
    idx++;

    unicode[idx] = 0U;
    idx++;
  }
}


/**
  * @brief  USBD_GetLen
  *         return the string length
   * @param  buf : pointer to the ascii string buffer
  * @retval string length
  */
static uint8_t USBD_GetLen(uint8_t *buf)
{
  uint8_t  len = 0U;
  uint8_t *pbuff = buf;

  while (*pbuff != (uint8_t)'\0')
  {
    len++;
    pbuff++;
  }

  return len;
}


#endif
