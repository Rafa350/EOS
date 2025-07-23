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

    class EpAddr final {
    	private:
    		uint8_t _addr;
    	public:
    		constexpr explicit EpAddr(uint8_t addr) : _addr {addr} {};
    		constexpr EpAddr(const EpAddr &epAddr) : _addr {epAddr._addr} {}

    		constexpr EpAddr& operator=(const EpAddr &epAddr) { _addr = epAddr._addr; return *this; }
    		constexpr operator uint8_t() const { return _addr; }
    };

	struct USBDeviceDriverConfiguration {
		const char *manufacturerStr;
		const char *productStr;
		const char *serialNumberStr;
		uint16_t languageID;
		uint16_t productID;
		uint16_t vendorID;
		unsigned maxEp0Size;
		uint8_t maxPower;
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
			const char * const _productStr;
			const char * const _serialNumberStr;

			uint16_t const _languageID;

			uint16_t const _productID;
			uint16_t const _vendorID;
			unsigned const _maxEp0Size;

			uint8_t _maxPower;

		private:
			bool processRequest(USBD_SetupReqTypedef *request);

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

			bool getDeviceDescriptor(uint8_t *buffer, unsigned bufferSize, unsigned &length) const;
			bool getDeviceQualifierDescriptor(uint8_t *buffer, unsigned bufferSize, unsigned &length) const;
			bool getConfigurationDescriptor(uint8_t *buffer, unsigned bufferSize, unsigned &length, bool hr) const;
			bool getLangIDStrDescriptor(uint8_t *buffer, unsigned bufferSize, unsigned &length) const;
			bool getManufacturerStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getProductStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getInterfaceStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getConfigurationStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getSerialStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getStringDescriptor(const char *str, uint8_t *&data, unsigned &length) const;

			void ctlError(USBD_SetupReqTypedef *request);
			void ctlSendStatus();
			void ctlSendData(uint8_t *data, unsigned length);

		public:
			USBDeviceDriver(const USBDeviceDriverConfiguration *cfg);

			Result registerClass(USBDeviceClass *devClass);

			Result initialize();
			Result start();
			Result stop();

			USBD_StatusTypeDef setClassConfig(uint8_t configIdx);
			USBD_StatusTypeDef clearClassConfig(uint8_t configIdx);

			bool dataOutStage(EpAddr epAddr);
			bool dataInStage(EpAddr epAddr);
			bool setupStage(uint8_t *data);

			inline State getState() const {	return _state; }
			inline USBD_HandleTypeDef * getHandle() { return &_usbd; }

			USBDeviceClass *getClassFromEndPoint(EpAddr epAddr) const;
			USBDeviceClass *getClassFromInterface(uint8_t iface) const;

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
			static uint8_t reserveIface(uint8_t ifaceQty);

			void ctlError(USBD_SetupReqTypedef *request);
			void ctlSendStatus();
			void ctlSendData(uint8_t *data, unsigned length);

		public:
			Result initialize();

			inline State getState() const { return _state; }

			virtual bool usesEndPoint(EpAddr epAddr) const = 0;
			virtual bool usesIface(uint8_t iface) const = 0;

			virtual int8_t classInitialize(uint8_t cfgidx) = 0;
			virtual int8_t classDeinitialize(uint8_t cfgidx) = 0;

			virtual int8_t classSetup(USBD_SetupReqTypedef *req) = 0;

			virtual int8_t classEP0TxSent() = 0;
			virtual int8_t classEP0RxReady() = 0;
			virtual int8_t classSOF() = 0;
			virtual int8_t classDataIn(EpAddr epAddr) = 0;
			virtual int8_t classDataOut(EpAddr epAddr) = 0;
			virtual int8_t classIsoINIncomplete(EpAddr epAddr) = 0;
			virtual int8_t classIsoOUTIncomplete(EpAddr epAddr) = 0;
			virtual unsigned classGetInterfaceDescriptors(uint8_t *buffer, unsigned bufferSize, bool hs) = 0;
	};
}


#endif // __eosUSBDeviceDriver__
