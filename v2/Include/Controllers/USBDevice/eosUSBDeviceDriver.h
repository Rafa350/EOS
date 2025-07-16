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

	struct USBDeviceConfiguration {
		USBD_DeviceDescriptor *deviceDescriptor;
		USBD_DeviceQualifierDescriptor *deviceQualifierDescriptor;
		USBD_ConfigurationDescriptor *configurationDescriptor;
		USBD_LangIDDescriptorHeader *langIDDescriptor;
		const char *manufacturer;
		const char *product;
		const char *interface;
		const char *configuration;
	};

	class USBDeviceDriver final {
		public:
			enum class State {
				invalid,
				reset,
				ready,
				running
			};

		private:
			const USBDeviceConfiguration * const _configuration;
			State _state;
			USBDeviceClassList _classes;
			USBD_HandleTypeDef _usbd;

		private:
			USBDeviceClass *getClassFromEndPoint(uint8_t epAdd) const;

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
			bool getLangIDStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getManufacturerStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getProductStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getInterfaceStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getConfigurationStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getSerialStrDescriptor(uint8_t *&data, unsigned &length) const;
			bool getStringDescriptor(const char *str, uint8_t *&data, unsigned &length) const;

		public:
			USBDeviceDriver(const USBDeviceConfiguration *configuration);

			Result registerClass(USBDeviceClass *devClass);

			Result initialize();
			Result start();
			Result stop();

			USBD_StatusTypeDef setClassConfig(uint8_t cfgidx);
			bool processRequest(USBD_SetupReqTypedef *request);

			inline State getState() const {	return _state; }
			inline USBD_HandleTypeDef * getHandle() { return &_usbd; }
			inline const USBDeviceConfiguration* getConfiguration() const { return _configuration; }
			inline USBDeviceClass *getClass() const { return _classes.front(); }
	};

	class USBDeviceClass: public USBDeviceClassListNode {
		protected:
			USBDeviceDriver * const _drvUSBD;

		protected:
			USBDeviceClass(USBDeviceDriver *drvUSBD);

		public:
			virtual Result initialize() = 0;

			virtual int8_t classInitialize(uint8_t cfgidx) = 0;
			virtual int8_t classDeinitialize(uint8_t cfgidx) = 0;

			virtual int8_t classSetup(USBD_SetupReqTypedef *req) = 0;

			virtual int8_t classEP0TxSent() = 0;
			virtual int8_t classEP0RxReady() = 0;
			virtual int8_t classSOF() = 0;
			virtual int8_t classDataIn(uint8_t epnum) = 0;
			virtual int8_t classDataOut(uint8_t epnum) = 0;
			virtual int8_t classIsoINIncomplete(uint8_t epnum) = 0;
			virtual int8_t classIsoOUTIncomplete(uint8_t epnum) = 0;
			virtual bool classGetHSConfigurationDescriptor(uint8_t *&data, unsigned &length) = 0;
			virtual bool classGetFSConfigurationDescriptor(uint8_t *&data, unsigned &length) = 0;
			virtual bool classGetOtherSpeedConfigurationDescriptor(uint8_t *&data, unsigned &length) = 0;
			virtual bool classGetDeviceQualifierDescriptor(uint8_t *&data, unsigned &length) = 0;

			virtual bool usesEndPoint(uint8_t epAddr) const = 0;
	};
}


#endif // __eosUSBDeviceDriver__
