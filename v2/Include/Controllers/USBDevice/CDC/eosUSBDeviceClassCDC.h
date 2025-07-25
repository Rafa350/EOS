#pragma once
#ifndef __eosUSBDeviceClassCDC__
#define __eosUSBDeviceClassCDC__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDeviceDriver.h"
#include "Controllers/USBDevice/CDC/eosCDCDefinitions.h"
#include "System/eosResults.h"


namespace eos {

	class USBDeviceClassCDC;

	struct CDCLineCoding {
		uint32_t dwDTERate;
		uint8_t bCharFormat;
		uint8_t bParityType;
		uint8_t bDataBits;
	};

	class CDCInterface {
		public:
			virtual int8_t initialize(USBDeviceClassCDC *cdc) = 0;
			virtual int8_t deinitialize(USBDeviceClassCDC *cdc) = 0;

			virtual int8_t control(CDCRequestID requestID, uint8_t *data, unsigned dataSize) = 0;

			virtual void rxDataAvailable(const uint8_t *buffer, unsigned length) = 0;
			virtual void txDataCompleted(const uint8_t *buffer, unsigned length, uint8_t epnum) = 0;
	};

	struct USBDeviceClassCDCConfiguration {
		EpAddr const inEpAddr;
		EpAddr const outEpAddr;
		EpAddr const cmdEpAddr;
	};

	class USBDeviceClassCDC final: public USBDeviceClass {
		private:
			enum class State {
				reset,
				idle,
				transmiting,
				receiving
			};

		private:
			EpAddr _inEpAddr;
			EpAddr _outEpAddr;
			EpAddr _cmdEpAddr;
			CDCInterface *_interface;
			USBD_CDC_HandleTypeDef _cdc;
			volatile State _state; // S'actualitza per interrupcions
			const uint8_t *_txBuffer;
			unsigned _txLength;
			uint8_t *_rxBuffer;
			unsigned _rxBufferSize;
			unsigned _rxLength;
			CDCRequestID _req_requestID;
			uint8_t _req_length;

		protected:
			Result initializeImpl() override;

		public:
			USBDeviceClassCDC(USBDeviceDriver *drvUSBD, const USBDeviceClassCDCConfiguration *configuration, CDCInterface *interface);

			Result transmit(const uint8_t *buffer, unsigned length);
			Result receive(uint8_t *buffer, unsigned bufferSize);
			Result wait(unsigned timeout);

			inline bool isBusy() const { return _state != State::idle; }

			int8_t classInitialize(uint8_t configIdx) override;
			int8_t classDeinitialize(uint8_t configIdx) override;

			int8_t classSetup(USBD_SetupReqTypedef *req) override;
			int8_t classEP0TxSent() override;
			int8_t classEP0RxReady() override;
			int8_t classSOF() override;
			int8_t classDataIn(EpAddr epAddr) override;
			int8_t classDataOut(EpAddr epAddr) override;
			int8_t classIsoINIncomplete(EpAddr epAddr) override;
			int8_t classIsoOUTIncomplete(EpAddr epAddr) override;

			bool buildInterfaceDescriptors(uint8_t *buffer, unsigned bufferSize, bool hs, unsigned &length) override;

			bool usesEndPoint(EpAddr epAddr) const override;
			bool usesIface(uint8_t ifaceQty) const override;
	};
}


#endif // __eosUSBDeviceClassCDC__
