#pragma once
#ifndef __USBD_MSC_BOT_H
#define __USBD_MSC_BOT_H


#include "Controllers/USBDevice/ST/st_usbd_core.h"


#define USBD_BOT_IDLE                      0U       /* Idle state */
#define USBD_BOT_DATA_OUT                  1U       /* Data Out state */
#define USBD_BOT_DATA_IN                   2U       /* Data In state */
#define USBD_BOT_LAST_DATA_IN              3U       /* Last Data In Last */
#define USBD_BOT_SEND_DATA                 4U       /* Send Immediate data */
#define USBD_BOT_NO_DATA                   5U       /* No data Stage */

#define USBD_BOT_CBW_SIGNATURE             0x43425355U
#define USBD_BOT_CSW_SIGNATURE             0x53425355U
#define USBD_BOT_CBW_LENGTH                31U
#define USBD_BOT_CSW_LENGTH                13U
#define USBD_BOT_MAX_DATA                  256U

/* CSW Status Definitions */
#define USBD_CSW_CMD_PASSED                0x00U
#define USBD_CSW_CMD_FAILED                0x01U
#define USBD_CSW_PHASE_ERROR               0x02U

/* BOT Status */
#define USBD_BOT_STATUS_NORMAL             0U
#define USBD_BOT_STATUS_RECOVERY           1U
#define USBD_BOT_STATUS_ERROR              2U


#define USBD_DIR_IN                        0U
#define USBD_DIR_OUT                       1U
#define USBD_BOTH_DIR                      2U


struct USBD_MSC_BOT_CBWTypeDef {
	uint32_t dSignature;
	uint32_t dTag;
	uint32_t dDataLength;
	uint8_t  bmFlags;
	uint8_t  bLUN;
	uint8_t  bCBLength;
	uint8_t  CB[16];
	uint8_t  ReservedForAlign;
};

struct USBD_MSC_BOT_CSWTypeDef {
	uint32_t dSignature;
	uint32_t dTag;
	uint32_t dDataResidue;
	uint8_t  bStatus;
	uint8_t  ReservedForAlign[3];
};


void MSC_BOT_Init(USBD_HandleTypeDef  *pdev);
void MSC_BOT_Reset(USBD_HandleTypeDef  *pdev);
void MSC_BOT_DeInit(USBD_HandleTypeDef  *pdev);
void MSC_BOT_DataIn(USBD_HandleTypeDef  *pdev, uint8_t epnum);
void MSC_BOT_DataOut(USBD_HandleTypeDef  *pdev, uint8_t epnum);
void MSC_BOT_SendCSW(USBD_HandleTypeDef  *pdev, uint8_t CSW_Status);
void MSC_BOT_CplClrFeature(USBD_HandleTypeDef *pdev, uint8_t epnum);


#endif // __USBD_MSC_BOT_H
