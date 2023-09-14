#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


namespace htl {

	namespace i2c {

		enum class DeviceID {
			#ifdef HTL_I2C1_EXIST
			_1,
			#endif
			#ifdef HTL_I2C2_EXIST
			_2,
			#endif
			#ifdef HTL_I2C3_EXIST
			_3,
			#endif
			#ifdef HTL_I2C4_EXIST
			_4
			#endif
		};

		enum class ClockSource {
			sysclk,
			#if defined(EOS_PLATFORM_STM32F4)
			hsi,
			pclk1,
			#elif defined(EOS_PLATFORM_STM32G0)
			hsi16,
			pclk,
			#endif
		};

		enum class PinFunction {
			scl,
			sda,
			alert
		};
        
        
        enum class NotifyID {
            addressMatch,
            rxData,
            rxCompleted,
            txData,
            txCompleted
        };
        
        struct NotityEventArgs {
            NotifyID id;            
            bool isr;
            union {
                struct {
                    uint16_t addr;
                } AddressMatch;
                struct {
                    const uint16_t *buffer;
                    uint16_t length;
                } RxData;
                struct {
                    const uint16_t *buffer;
                    uint16_t length;
                } RxCompleted;
                struct {
                    uint8_t *buffer;
                    uint16_t size;
                    uint16_t length;
                } TxData;
                struct {
                    
                } TxCompleted;
            }
        }


		class I2CSlaveDevice;
        using ISlaveNotifyEvent = eos::ICallbackP2<I2CSlaveDevice*, NotifyEventArgs&);
        template <typename instance_> using SlaveNotifyEvent = eos::CallbackP2<instance_, I2CSlaveDevice*, NotifyEventArgs&);

		class I2CMasterDevice;
        using IMasterNotifyEvent = eos::ICallbackP2<I2CMasterDevice*, NotifyEventArgs&);
        template <typename Instance_> using MasterNotifyEvent = eos::CallbackP2<Instance_, I2CMasterDevice*, NotifyEventArgs&);


		using IAddressMatchEvent = eos::ICallbackP2<I2CSlaveDevice*, uint16_t>;
		using IRxDataEvent = eos::ICallbackP3<I2CSlaveDevice*, const uint8_t*, uint16_t>;
		using IRxCompletedEvent = eos::ICallbackP3<I2CSlaveDevice*, const uint8_t*, uint16_t>;
		using ITxDataEvent = eos::ICallbackP4<I2CSlaveDevice*, uint8_t*, uint16_t, uint16_t&>;
		using ITxCompletedEvent = eos::ICallbackP1<I2CSlaveDevice*>;

		template <typename instance_> using AddressMatchEvent = eos::CallbackP2<instance_, I2CSlaveDevice*, uint16_t>;
		template <typename instance_> using RxDataEvent = eos::CallbackP3<instance_, I2CSlaveDevice*, const uint8_t*, uint16_t>;
		template <typename instance_> using RxCompletedEvent = eos::CallbackP3<instance_, I2CSlaveDevice*, const uint8_t*, uint16_t>;
		template <typename instance_> using TxDataCallback = eos::CallbackP4<instance_, I2CSlaveDevice*, uint8_t*, uint16_t, uint16_t&>;
		template <typename instance_> using TxCompletedEvent = eos::CallbackP1<instance_, I2CSlaveDevice*>;


		class I2CDevice {
			protected:
				virtual void activate() = 0;
				virtual void deactivate() = 0;
		};


		class I2CSlaveDevice: public I2CDevice {
			public:
				enum class State {
					reset,
					ready,
					listen,
					listenRx,
					listenTx
				};
				enum class Result {
					ok,
					error,
					busy
				};
			private:
				I2C_TypeDef * const _i2c;
				State _state;
				uint8_t *_buffer;
				uint16_t _bufferSize;
				uint16_t _count;
				uint16_t _maxCount;
                ISlaveNotifyEvent *_notifyEvent;
                bool _notifyEventEnabled;
			private:
				I2CSlaveDevice(const I2CSlaveDevice &) = delete;
				I2CSlaveDevice & operator = (const I2CSlaveDevice &) = delete;
                void notifyAddressMatch(uint16_t addr);
                void notifyRxData(const uint8_t *buffer, uint16_t length);
                void notifyRxCompleted(const uint8_t *buffer, uint16_t length);
                void notifyTxData(uint8_t *buffer, uint16_t size, uint16_t &length);
                void notifyTxCompleted();
				void interruptServiceListen();
				void interruptServiceListenRx();
				void interruptServiceListenTx();
			protected:
				I2CSlaveDevice(I2C_TypeDef *gpio);
				void interruptService();
			public:
				Result initialize(uint16_t addr, uint8_t prescaler, uint8_t scldel, uint8_t sdadel, uint8_t sclh, uint8_t scll);
				Result deinitialize();
				inline void setNotifyEvent(INotifyEventEvent &event, bool enabled = true) {
					_notifyEvent = &event;
					_notifyEventEnabled = enabled;
				}
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}
				Result listen(uint8_t *buffer, uint16_t bufferSize);
				void endListen();
				inline State getState() const {
					return _state;
				}
		};

		typedef I2CSlaveDevice *I2CSlaveDeviceHandler;


		class I2CMasterDevice: public I2CDevice {
			private:
				I2C_TypeDef * const _i2c;
			private:
				I2CMasterDevice(const I2C_TypeDef&) = delete;
				I2CMasterDevice & operator = (const I2CMasterDevice &) = delete;
			protected:
				I2CMasterDevice(I2C_TypeDef *i2c);
		};


		namespace internal {

			template <DeviceID>
			class HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct I2CPinFunctionID;
		}

		template <DeviceID deviceID_>
		class I2CSlaveDeviceX final: public I2CSlaveDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _i2cAddr = HI::i2cAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static I2CSlaveDeviceX _device;
			public:
				static constexpr DeviceID deviceID = deviceID_;
			private:
				I2CSlaveDeviceX() :
					I2CSlaveDevice {reinterpret_cast<I2C_TypeDef *>(_i2cAddr)} {
				}
			protected:
				void activate() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivate() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
			public:
				static constexpr I2CSlaveDeviceX * getHandler() {
					return &_device;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				template <typename pin_>
				void initPinSCL() {
					gpio::PinFunctionID pinFunctionID = internal::I2CPinFunctionID<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::openDrain, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initPinSDA() {
					gpio::PinFunctionID pinFunctionID = internal::I2CPinFunctionID<deviceID_, PinFunction::sda, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::openDrain, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initPinALERT() {
					gpio::PinFunctionID pinFunctionID = internal::I2CPinFunctionID<deviceID_, PinFunction::alert, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::openDrain, gpio::Speed::fast, pinFunctionID);
				}
		};

		template <DeviceID deviceID_>
		I2CSlaveDeviceX<deviceID_> I2CSlaveDeviceX<deviceID_>::_device;


		#ifdef HTL_I2C1_EXIST
		typedef I2CSlaveDeviceX<DeviceID::_1> I2CSlaveDevice1;
		#endif
		#ifdef HTL_I2C2_EXIST
		typedef I2CSlaveDeviceX<DeviceID::_2> I2CSlaveDevice2;
		#endif
		#ifdef HTL_I2C3_EXIST
		typedef I2CSlaveDeviceX<DeviceID::_3> I2CSlaveDevice3;
		#endif
		#ifdef HTL_I2C4_EXIST
		typedef I2CSlaveDeviceX<DeviceID::_4> I2CSlaveDevice4;
		#endif


		namespace internal {

			#ifdef HTL_I2C1_EXIST
			template <>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t i2cAddr = I2C1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_I2C2_EXIST
			template <>
			struct HardwareInfo<DeviceID::_2> {
				static constexpr uint32_t i2cAddr = I2C2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_I2C3_EXIST
			template <>
			struct HardwareInfo<DeviceID::_3> {
				static constexpr uint32_t i2cAddr = I2C3_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C3EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_I2C4_EXIST
			template <>
			struct HardwareInfo<DeviceID::_4> {
				static constexpr uint32_t i2cAddr = I2C4_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C4EN_Pos;
				#endif
			};
			#endif

		}
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlI2C_AF_G030.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlI2C_AF_G031.h"

#elif defined(EOS_PLATFORM_STM32G051)
    #include "htl/STM32/G0/htlI2C_AF_G051.h"

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/htlI2C_AF_G071.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/htlI2C_AF_F030.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlI2C_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlI2C_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlI2C__

