#pragma once
#ifndef __eosUSBDefinitions__
#define __eosUSBDefinitions__


#include "eos.h"


//namespace eos {

	namespace internal {

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
			static constexpr uint8_t device                  = 1;
			static constexpr uint8_t configuration           = 2;
			static constexpr uint8_t string                  = 3;
			static constexpr uint8_t deviceQualifier         = 6;
			static constexpr uint8_t otherSpeedConfiguration = 7;
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
		deviceQualifier 		= internal::Request_ValueDescriptorType::deviceQualifier,
		otherSpeedConfiguration = internal::Request_ValueDescriptorType::otherSpeedConfiguration
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
//}


#endif // __eosUSBDefinitions__
