#pragma once
#ifndef __eosUSBDeviceDriver__
#define __eosUSBDeviceDriver__


#include "eos.h"
#include "Controllers/USBDevice/eosUSBDefinitions.h"
#include "Controllers/USBDevice/ST/st_usbd_def.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/eosResults.h"

#include "usbd_desc.h"


namespace eos {

	class USBDevice;
	class USBDeviceClass;

    using USBDeviceClassList = IntrusiveForwardList<USBDeviceClass, 0>;
    using USBDeviceClassListNode = IntrusiveForwardListNode<USBDeviceClass, 0>;

	struct USBDeviceDriverConfiguration {
		const char *manufacturerStr;
		const char *productStr;
		const char *serialNumberStr;
		uint16_t langID;
		uint16_t pid;
		uint16_t vid;
		unsigned maxEp0Size;
		unsigned maxPower;
	};

	class USBDeviceDriver final {
		public:
			enum class State {
				reset,
				error,
				ready,
				running
			};

		private:
			State _state;
			USBDeviceClassList _classes;
			USBD_HandleTypeDef _usbd;

			const char * const _manufacturerStr;
			uint8_t const _manufacturerIdx = 1;
			const char * const _productStr;
			uint8_t const _productIdx = 2;
			const char * const _serialNumberStr;
			uint8_t const _serialNumberIdx = 3;

			uint16_t const _langID;

			uint16_t const _pid;
			uint16_t const _vid;
			unsigned const _maxEp0Size;

			uint8_t _maxPower;

		private:
			USBDeviceClass *getClassFromEndPoint(uint8_t epAddr) const;
			USBDeviceClass *getClassFromInterface(uint8_t iface) const;

			bool processDeviceRequest(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_GetDescriptor(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_SetAddress(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_SetFeature(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_ClearFeature(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_GetConfiguration(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_SetConfiguration(USBD_SetupReqTypedef *request);
			bool processDeviceRequest_GetStatus(USBD_SetupReqTypedef *request);

			bool processInterfaceRequest(USBD_SetupReqTypedef *request);

			bool processEndPointRequest(USBD_SetupReqTypedef *request);
			bool processEndPointRequest_SetFeature(USBD_SetupReqTypedef *request);
			bool processEndPointRequest_ClearFeature(USBD_SetupReqTypedef *request);
			bool processEndPointRequest_GetStatus(USBD_SetupReqTypedef *request);

			bool getDeviceDescriptor(uint8_t *&data, unsigned &length) const;
			bool getConfigurationDescriptor(uint8_t *&data, unsigned &length, bool hr) const;
			bool getLangIDStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getManufacturerStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getProductStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getInterfaceStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getConfigurationStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getSerialStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getStringDescriptor(const char *str, uint8_t *&data, unsigned &length) const;

		public:
			USBDeviceDriver(const USBDeviceDriverConfiguration *cfg);

			Result registerClass(USBDeviceClass *devClass);

			Result initialize();
			Result start();
			Result stop();

			USBD_StatusTypeDef setClassConfig(uint8_t cfgidx);
			USBD_StatusTypeDef clearClassConfig(uint8_t cfgidx);

			bool dataOutStage(uint8_t epAddr);
			bool dataInStage(uint8_t epAddr);
			bool processRequest(USBD_SetupReqTypedef *request);

			inline State getState() const {	return _state; }
			inline USBD_HandleTypeDef * getHandle() { return &_usbd; }

			// TODO: Obsolete
			inline USBDeviceClass *getClass() const { return _classes.front(); }
	};

	class USBDeviceClass: public USBDeviceClassListNode {
		public:
			enum class State {
				reset,
				ready,
				error
			};

		private:
			static uint8_t _ifaceCount;
			State _state;

		protected:
			USBDeviceDriver * const _drvUSBD;
			uint8_t const _iface;

		protected:
			USBDeviceClass(USBDeviceDriver *drvUSBD, uint8_t iface);

			virtual Result initializeImpl() = 0;
			uint8_t reserveIface(unsigned ifaceQty);

		public:
			Result initialize();

			inline State getState() const { return _state; }

			virtual bool usesEndPoint(uint8_t epAddr) const = 0;
			virtual bool usesIface(uint8_t iface) const = 0;

			virtual int8_t classInitialize(uint8_t cfgidx) = 0;
			virtual int8_t classDeinitialize(uint8_t cfgidx) = 0;

			virtual int8_t classSetup(USBD_SetupReqTypedef *req) = 0;

			virtual int8_t classEP0TxSent() = 0;
			virtual int8_t classEP0RxReady() = 0;
			virtual int8_t classSOF() = 0;
			virtual int8_t classDataIn(uint8_t epAddr) = 0;
			virtual int8_t classDataOut(uint8_t epAddr) = 0;
			virtual int8_t classIsoINIncomplete(uint8_t epAddr) = 0;
			virtual int8_t classIsoOUTIncomplete(uint8_t epAddr) = 0;
			virtual unsigned classGetInterfaceDescriptors(uint8_t *buffer, unsigned bufferSize, bool hs) = 0;
			virtual bool classGetDeviceQualifierDescriptor(uint8_t *&data, unsigned &length) = 0;
	};
}


#endif // __eosUSBDeviceDriver__
