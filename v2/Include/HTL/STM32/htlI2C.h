#pragma once


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/eosResults.h"


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
			#if defined(EOS_PLATFORM_STM32F4)
			pclk1,
			sysclk,
			hsi,
			#elif defined(EOS_PLATFORM_STM32G0)
			pclk,
			sysclk,
			hsi16,
			#endif
			automatic
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
        
        struct NotifyEventArgs {
            NotifyID id;            
            bool isr;
            union {
                struct {
                    uint16_t addr;
                } AddressMatch;
                struct {
                    const uint8_t *buffer;
                    uint16_t length;
                } RxData;
                struct {
                    const uint8_t *buffer;
                    uint16_t length;
                } RxCompleted;
                struct {
                    uint8_t *buffer;
                    uint16_t size;
                    uint16_t length;
                } TxData;
                struct {
                    uint16_t length;
                } TxCompleted;
            };
        };

        enum class Results {
            success,
            busy,
            timeout,
            error
        };
        using Result = eos::SimpleResult<Results>;


		class I2CSlaveDevice;
        using ISlaveNotifyEvent = eos::ICallbackP2<I2CSlaveDevice*, NotifyEventArgs&>;
        template <typename Instance_> using SlaveNotifyEvent = eos::CallbackP2<Instance_, I2CSlaveDevice*, NotifyEventArgs&>;

		class I2CMasterDevice;
        using IMasterNotifyEvent = eos::ICallbackP2<I2CMasterDevice*, NotifyEventArgs&>;
        template <typename Instance_> using MasterNotifyEvent = eos::CallbackP2<Instance_, I2CMasterDevice*, NotifyEventArgs&>;


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
				inline void setNotifyEvent(ISlaveNotifyEvent &event, bool enabled = true) {
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

		class I2CMasterDevice: public I2CDevice {
			public:
				enum class State {
					reset,
					ready
				};
			private:
				I2C_TypeDef * const _i2c;
				State _state;
			private:
				I2CMasterDevice(const I2C_TypeDef&) = delete;
				I2CMasterDevice & operator = (const I2CMasterDevice &) = delete;
			protected:
				I2CMasterDevice(I2C_TypeDef *i2c);
				void interruptService();
			public:
				Result initialize(uint8_t prescaler, uint8_t scldel, uint8_t sdadel,
					uint8_t sclh, uint8_t scll);
				Result deinitialize();
				Result send(uint16_t addr, const uint8_t *buffer, uint16_t size, uint16_t timeout = 0xFFFF);
				Result receive(uint16_t addr, uint8_t *buffer, uint16_t size, uint16_t timeout = 0xFFFF);
		};


		namespace internal {

			template <DeviceID>
			class HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct PinFunctionInfo;
		}

		template <DeviceID deviceID_>
		class I2CSlaveDeviceX final: public I2CSlaveDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _i2cAddr = HI::i2cAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static I2CSlaveDeviceX _instance;
			public:
				static constexpr DeviceID deviceID = deviceID_;
				static constexpr I2CSlaveDeviceX *pInst = &_instance;
				static constexpr I2CSlaveDeviceX &rInst = _instance;
			private:
				constexpr I2CSlaveDeviceX() :
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
				inline static void interruptHandler() {
					_instance.interruptService();
				}
				template <typename pin_>
				void initPinSCL() {
					auto pf = internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::pInst->initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, pf);
				}
				template <typename pin_>
				void initPinSDA() {
					auto pf = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_>::alt;
					pin_::pInst->initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, pf);
				}
				template <typename pin_>
				void initPinALERT() {
					auto pf = internal::PinFunctionInfo<deviceID_, PinFunction::alert, pin_>::alt;
					pin_::pInst->initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, pf);
				}
		};

		template <DeviceID deviceID_>
		I2CSlaveDeviceX<deviceID_> I2CSlaveDeviceX<deviceID_>::_instance;


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


		template <DeviceID deviceID_>
		class I2CMasterDeviceX final: public I2CMasterDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _i2cAddr = HI::i2cAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static I2CMasterDeviceX _instance;
			public:
				static constexpr DeviceID deviceID = deviceID_;
                static constexpr I2CMasterDeviceX *pInst = &_instance;
                static constexpr I2CMasterDeviceX &rInst = _instance;
			private:
				I2CMasterDeviceX() :
					I2CMasterDevice {reinterpret_cast<I2C_TypeDef *>(_i2cAddr)} {
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
				inline static void interruptHandler() {
					_instance.interruptService();
				}
				template <typename pin_>
				void initPinSCL() {
					auto af= internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::pInst->initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void initPinSDA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_>::alt;
					pin_::pInst->initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		I2CMasterDeviceX<deviceID_> I2CMasterDeviceX<deviceID_>::_instance;


		#ifdef HTL_I2C1_EXIST
		typedef I2CMasterDeviceX<DeviceID::_1> I2CMasterDevice1;
		#endif
		#ifdef HTL_I2C2_EXIST
		typedef I2CMasterDeviceX<DeviceID::_2> I2CMasterDevice2;
		#endif
		#ifdef HTL_I2C3_EXIST
		typedef I2CMasterDeviceX<DeviceID::_3> I2CMasterDevice3;
		#endif
		#ifdef HTL_I2C4_EXIST
		typedef I2CMasterDeviceX<DeviceID::_4> I2CMasterDevice4;
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
