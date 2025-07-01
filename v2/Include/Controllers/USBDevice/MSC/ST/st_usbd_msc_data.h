#pragma once
#ifndef __USBD_MSC_DATA_H
#define __USBD_MSC_DATA_H


#include "usbd_conf.h"


#define MODE_SENSE6_LEN                    0x04U
#define MODE_SENSE10_LEN                   0x08U
#define LENGTH_INQUIRY_PAGE00              0x06U
#define LENGTH_INQUIRY_PAGE80              0x08U
#define LENGTH_FORMAT_CAPACITIES           0x14U
#define DIAGNOSTIC_DATA_LEN                0x08U
#define LOG_PAGE_DATA_LEN                  0x10U


extern uint8_t MSC_Page00_Inquiry_Data[LENGTH_INQUIRY_PAGE00];
extern uint8_t MSC_Page80_Inquiry_Data[LENGTH_INQUIRY_PAGE80];
extern uint8_t MSC_Mode_Sense6_data[MODE_SENSE6_LEN];
extern uint8_t MSC_Mode_Sense10_data[MODE_SENSE10_LEN];
extern uint8_t MSC_Diagnostic_Data[DIAGNOSTIC_DATA_LEN];
extern uint8_t MSC_Log_Page_Data[LOG_PAGE_DATA_LEN];


#endif // __USBD_MSC_DATA_H
