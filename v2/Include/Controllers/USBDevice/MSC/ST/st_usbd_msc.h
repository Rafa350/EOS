#pragma once
#ifndef __st_usbd_msc__
#define __st_usbd_msc__


#include  "Controllers/USBDevice/ST/st_usbd_ioreq.h"
#include  "Controllers/USBDevice/MSC/ST/st_usbd_msc_bot.h"
#include  "Controllers/USBDevice/MSC/ST/st_usbd_msc_scsi.h"


/* MSC Class Config */
#ifndef MSC_MEDIA_PACKET
#define MSC_MEDIA_PACKET             512U
#endif /* MSC_MEDIA_PACKET */

#define MSC_MAX_FS_PACKET            0x40U
#define MSC_MAX_HS_PACKET            0x200U

#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF
#define USB_MSC_CONFIG_DESC_SIZ      32

#ifndef MSC_EPIN_ADDR
#define MSC_EPIN_ADDR                0x81U
#endif /* MSC_EPIN_ADDR */

#ifndef MSC_EPOUT_ADDR
#define MSC_EPOUT_ADDR               0x01U
#endif /* MSC_EPOUT_ADDR */

#ifndef MSC_BOT_MAX_LUN
#define MSC_BOT_MAX_LUN              0x2U
#endif /* MSC_BOT_MAX_LUN */


typedef struct _USBD_STORAGE
{
  int8_t (* Init)(uint8_t lun);
  int8_t (* GetCapacity)(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
  int8_t (* IsReady)(uint8_t lun);
  int8_t (* IsWriteProtected)(uint8_t lun);
  int8_t (* Read)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* Write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* GetMaxLun)(void);
  int8_t *pInquiry;

} USBD_StorageTypeDef;

typedef struct
{
  uint16_t size;
  uint32_t nbr;
  uint32_t addr;
  uint32_t len;
} USBD_MSC_BOT_LUN_TypeDef;

typedef struct
{
  uint32_t                 max_lun;
  uint32_t                 interface;
  uint8_t                  bot_state;
  uint8_t                  bot_status;
  uint32_t                 bot_data_length;
  uint8_t                  bot_data[MSC_MEDIA_PACKET];
  USBD_MSC_BOT_CBWTypeDef  cbw;
  USBD_MSC_BOT_CSWTypeDef  csw;

  USBD_SCSI_SenseTypeDef   scsi_sense [SENSE_LIST_DEEPTH];
  uint8_t                  scsi_sense_head;
  uint8_t                  scsi_sense_tail;
  uint8_t                  scsi_medium_state;

  USBD_MSC_BOT_LUN_TypeDef scsi_blk[MSC_BOT_MAX_LUN];
} USBD_MSC_BOT_HandleTypeDef;

/* Structure for MSC process */
extern USBD_ClassTypeDef  USBD_MSC;
#define USBD_MSC_CLASS    &USBD_MSC

uint8_t  USBD_MSC_RegisterStorage(USBD_HandleTypeDef *pdev, USBD_StorageTypeDef *fops);

#endif // __st_usbd__msc__

