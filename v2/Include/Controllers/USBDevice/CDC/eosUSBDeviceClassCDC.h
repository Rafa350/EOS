#pragma once
#ifndef __eosUSBDeviceClassCDC__
#define __eosUSBDeviceClassCDC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


namespace eos {

	class CDCInterface {
		public:
			virtual int8_t initialize() = 0;
			virtual int8_t deinitialize() = 0;

			virtual int8_t control(uint8_t cmd, uint8_t *data, uint16_t dataSize) = 0;

			virtual int8_t rxDataAvailable(uint8_t *data, uint32_t *length) = 0;
			virtual int8_t txDataCompleted(uint8_t *data, uint32_t *length, uint8_t epnum) = 0;
	};

	class USBDeviceClassCDC final: public USBDeviceClass {
		private:
			CDCInterface *_interface;
			USBD_CDC_HandleTypeDef _cdc;
			static constexpr uint8_t _inEpAdd  = CDC_IN_EP;
			static constexpr uint8_t _outEpAdd = CDC_OUT_EP;
			static constexpr uint8_t _cmdEpAdd = CDC_CMD_EP;

		public:
			USBDeviceClassCDC(USBDeviceDriver *drvUSBD, CDCInterface *interface);

			void initialize();

			int8_t classInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) override;
			int8_t classDeinit(USBD_HandleTypeDef *pdev, uint8_t cfgidx) override;
			int8_t classSetup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req) override;
			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady(USBD_HandleTypeDef *pdev) override;
			int8_t classDataIn(USBD_HandleTypeDef *pdev, uint8_t epnum) override;
			int8_t classDataOut(USBD_HandleTypeDef *pdev, uint8_t epnum) override;
			int8_t* classGetHSCfgDesc(uint16_t *length) override;
			int8_t* classGetFSCfgDesc(uint16_t *length) override;
			int8_t* classGetOtherSpeedCfgDesc(uint16_t *length) override;
			int8_t* classGetDeviceQualifierDescriptor(uint16_t *length) override;
	};
}


#endif // __eosUSBDeviceClassCDC__
