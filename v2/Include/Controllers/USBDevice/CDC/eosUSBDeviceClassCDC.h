#pragma once
#ifndef __eosUSBDeviceClassCDC__
#define __eosUSBDeviceClassCDC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


namespace eos {

	class CDCInterface {
		public :
			enum class ControlCmd: uint8_t {
				SEND_ENCAPSULATED_COMMAND = 0x00,
				GET_ENCAPSULATED_RESPONSE = 0x01,
				SET_COMM_FEATURE = 0x02,
				GET_COMM_FEATURE = 0x03,
				CLEAR_COMM_FEATURE = 0x04,
				SET_LINE_CODING = 0x20,
				GET_LINE_CODING = 0x21,
				SET_CONTROL_LINE_STATE = 0x22,
				SEND_BREAK = 0x23
			};

		public:
			virtual int8_t initialize() = 0;
			virtual int8_t deinitialize() = 0;

			virtual int8_t control(ControlCmd cc, uint8_t *data, uint16_t dataSize) = 0;

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

			int8_t classInit(uint8_t cfgidx) override;
			int8_t classDeinit(uint8_t cfgidx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;
			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(uint8_t epnum) override;
			int8_t classDataOut(uint8_t epnum) override;
			int8_t classIsoINIncomplete(uint8_t epnum) override;
			int8_t classIsoOUTIncomplete(uint8_t epnum) override;
			uint8_t* classGetHSConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetFSConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetOtherSpeedConfigurationDescriptor(uint16_t *length) override;
			uint8_t* classGetDeviceQualifierDescriptor(uint16_t *length) override;
	};
}


#endif // __eosUSBDeviceClassCDC__
