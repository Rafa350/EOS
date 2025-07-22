#pragma once
#ifndef __eosUSBDefinitions__
#define __eosUSBDefinitions__


#include "eos.h"


//namespace eos {

	namespace internal {

		constexpr unsigned maxRequestResponseDataSize = 150;

		struct Request_RequestType_Direction {
			static constexpr uint8_t POS          = 7;
			static constexpr uint8_t MASK         = 0b1 << Request_RequestType_Direction::POS;
			static constexpr uint8_t hostToDevice = 0 << Request_RequestType_Direction::POS;
			static constexpr uint8_t deviceToHost = 1 << Request_RequestType_Direction::POS;
		};

		struct Request_RequestType_Type {
			static constexpr uint8_t POS      = 5;
			static constexpr uint8_t MASK     = 0b11 << Request_RequestType_Type::POS;
			static constexpr uint8_t standard = 0 << Request_RequestType_Type::POS;
			static constexpr uint8_t clase    = 1 << Request_RequestType_Type::POS;
			static constexpr uint8_t vendor   = 2 << Request_RequestType_Type::POS;
		};

		struct Request_RequestType_Recipient {
			static constexpr uint8_t POS       = 0;
			static constexpr uint8_t MASK      = 0b11111 << Request_RequestType_Recipient::POS;
			static constexpr uint8_t device    = 0 << Request_RequestType_Recipient::POS;
			static constexpr uint8_t interface = 1 << Request_RequestType_Recipient::POS;
			static constexpr uint8_t endPoint  = 2 << Request_RequestType_Recipient::POS;
		};

		struct Request_RequestID {
			static constexpr uint8_t getStatus        = 0x00;
			static constexpr uint8_t clearFeature     = 0x01;
			static constexpr uint8_t setFeature       = 0x03;
			static constexpr uint8_t setAddress       = 0x05;
			static constexpr uint8_t getDescriptor    = 0x06;
			static constexpr uint8_t setDescriptor    = 0x07;
			static constexpr uint8_t getConfiguration = 0x08;
			static constexpr uint8_t setConfiguration = 0x09;
			static constexpr uint8_t getInterface     = 0x0A;
			static constexpr uint8_t setInterface     = 0x0B;
			static constexpr uint8_t setSynchFrame    = 0x0C;
		};

		struct Request_ValueDescriptorType {
			static constexpr uint8_t device                  = 0x01;
			static constexpr uint8_t configuration           = 0x02;
			static constexpr uint8_t string                  = 0x03;
			static constexpr uint8_t interface 				 = 0x04;
			static constexpr uint8_t endPoint                = 0x05;
			static constexpr uint8_t deviceQualifier         = 0x06;
			static constexpr uint8_t otherSpeedConfiguration = 0x07;
			static constexpr uint8_t iad                     = 0x0B;
			static constexpr uint8_t bos                     = 0x0F;
		};

	}

	enum class USBDRequestDirection {
		hostToDevice = internal::Request_RequestType_Direction::hostToDevice,
		deviceToHost = internal::Request_RequestType_Direction::deviceToHost
	};

	enum class USBDRequestType {
		standard = internal::Request_RequestType_Type::standard,
		clase    = internal::Request_RequestType_Type::clase,
		vendor   = internal::Request_RequestType_Type::vendor
	};

	enum class USBDRequestRecipient {
		device    = internal::Request_RequestType_Recipient::device,
		interface = internal::Request_RequestType_Recipient::interface,
		endPoint  = internal::Request_RequestType_Recipient::endPoint
	};

	enum class USBDRequestID {
		getStatus        = internal::Request_RequestID::getStatus,
		clearFeature     = internal::Request_RequestID::clearFeature,
		setFeature       = internal::Request_RequestID::setFeature,
		setAddress       = internal::Request_RequestID::setAddress,
		getDescriptor    = internal::Request_RequestID::getDescriptor,
		setDescriptor    = internal::Request_RequestID::setDescriptor,
		getConfiguration = internal::Request_RequestID::getConfiguration,
		setConfiguration = internal::Request_RequestID::setConfiguration,
		getInterface     = internal::Request_RequestID::getInterface,
		setInterface     = internal::Request_RequestID::setInterface,
		setSynchFrame    = internal::Request_RequestID::setSynchFrame
	};

	enum class USBDRequestValueDescriptorType {
		device                  = internal::Request_ValueDescriptorType::device,
		configuration           = internal::Request_ValueDescriptorType::configuration,
		string 					= internal::Request_ValueDescriptorType::string,
		interface               = internal::Request_ValueDescriptorType::interface,
		endPoint                = internal::Request_ValueDescriptorType::endPoint,
		deviceQualifier 		= internal::Request_ValueDescriptorType::deviceQualifier,
		otherSpeedConfiguration = internal::Request_ValueDescriptorType::otherSpeedConfiguration,
		iad                     = internal::Request_ValueDescriptorType::iad,
		bos                     = internal::Request_ValueDescriptorType::bos
	};

	struct USBD_SetupReqTypedef {
		uint8_t requestType;
		uint8_t requestID;
		uint16_t value;
		uint16_t index;
		uint16_t length;

		inline USBDRequestDirection getDirection() const {
			return (USBDRequestDirection) (requestType & internal::Request_RequestType_Direction::MASK);
		}

		inline USBDRequestType getType() const {
			return (USBDRequestType) (requestType & internal::Request_RequestType_Type::MASK);
		}

		inline USBDRequestRecipient getRecipient() const {
			return (USBDRequestRecipient) (requestType & internal::Request_RequestType_Recipient::MASK);
		}

		inline USBDRequestID getRequestID() const  {
			return (USBDRequestID) requestID;
		}

		inline USBDRequestValueDescriptorType getValueDescriptorType() const {
			return (USBDRequestValueDescriptorType) (value >> 8);
		}

		inline uint8_t getValueDescriptorIndex() const {
			return value & 0xFF;
		}

		template <typename T>
		inline T getClassRequestID() const {
			return (T) requestID;
		}
	};

	constexpr uint16_t bcdUSB = 0x0200;    // Versio USB 2.0

	enum class ClassID: uint8_t {
		classFromInterface = 0x00,
		audio = 0x01,
		cdc = 0x02,
		cdcData = 0x0A,
		hid = 0x03,
		image = 0x06,
		msc = 0x08,
		printer = 0x07,
		video = 0x0E,
		miscelaneous = 0xFE,
		vendorSpecific = 0xFF
	};

	enum class DescriptorType: uint8_t {
		device = 0x01,
		configuration = 0x02,
		string = 0x03,
		interface = 0x04,
		endPoint = 0x05,
		deviceQualifier = 0x06,
		otherSpeedConfiguration = 0x07,
		interfacePower = 0x08,
		interfaceAssociation = 0x0B
	};

	// Device Descriptor header (USB spec.)
	//
	struct USBD_DescriptorHeader {
		uint8_t bLength;
		uint8_t bDescriptorType;
	} __attribute__((packed, aligned(1)));

	// Device descriptor (USB spec.)
	//
	struct USBD_DeviceDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t bcdUSB;
		uint8_t bDeviceClass;
		uint8_t bDeviceSubClass;
		uint8_t bDeviceProtocol;
		uint8_t bMaxPacketSize;
		uint16_t idVendor;
		uint16_t idProduct;
		uint16_t bcdDevice;
		uint8_t iManufacturer;
		uint8_t iProduct;
		uint8_t iSerialNumber;
		uint8_t bMaxConfigurations;
	} __attribute__((packed, aligned(1)));

	// Device qualifier descriptor (USB spec.)
	//
	struct USBD_DeviceQualifierDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t bcdUSB;
		uint8_t bDeviceClass;
		uint8_t bDeviceSubClass;
		uint8_t bDeviceProtocol;
		uint8_t bMaxPacketSize0;
		uint8_t bNumConfigurations;
		uint8_t bReserved;
	} __attribute__((packed, aligned(1)));

	// Configuration descriptor (USB spec.)
	//
	struct USBD_ConfigurationDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t wTotalLength;
		uint8_t bNumInterfaces;
		uint8_t bConfigurationValue;
		uint8_t iConfiguration;
		uint8_t bmAttributes;
		uint8_t bMaxPower;
	} __attribute__((packed, aligned(1)));

	// Interface association descreiptor (USB spec.)
	//
	struct USBD_InterfaceAssociationDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bFirstInterface;
		uint8_t bInterfaceCount;
		uint8_t bFunctionClass;
		uint8_t bFunctionSubClass;
		uint8_t bFunctionProtocol;
		uint8_t iFunction;
	} __attribute__((packed, aligned(1)));

	// Interface descriptor (USB spec.)
	//
	struct USBD_InterfaceDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bInterfaceNumber;
		uint8_t bAlternateSetting;
		uint8_t bNumEndPoints;
		uint8_t bInterfaceClass;
		uint8_t bInterfaceSubClass;
		uint8_t bInterfaceProtocol;
		uint8_t iInterface;
	} __attribute__((packed, aligned(1)));

	// Endpoint descriptor (USB spec.)
	//
	struct USBD_EndPointDescriptor {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bEndPointAddress;
		uint8_t bmAttributes;
		uint16_t wMaxPacketSize;
		uint8_t bInterval;
	} __attribute__((packed, aligned(1)));

	// Language ID descriptor (USB spec.)
	//
	struct USBD_LangIDDescriptorHeader {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t wLangID[1];
	} __attribute__((packed, aligned(1)));

	// String descriptor (USB spec.)
	//
	struct USBD_StringDescriptorHeader {
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t wChar[1];
	} __attribute__((packed, aligned(1)));

//}


#endif // __eosUSBDefinitions__
