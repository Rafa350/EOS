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
			sda
		};

		enum class I2CInterruptStatus {
			addrMatch,
			rxPartial,
			rxCompleted
		};

		typedef void * I2CInterruptParam;

		struct I2CInterruptContext {
			I2CInterruptStatus status;
			uint8_t *buffer;
			uint16_t size;
			uint16_t count;
			I2CInterruptParam param;
		};

		typedef void (*I2CInterruptFunction)(I2CInterruptContext*);

		class I2CSlaveDevice {
			private:
				I2C_TypeDef * const _i2c;
				I2CInterruptFunction _function;
				I2CInterruptParam _param;
				uint8_t *_buffer;
				uint16_t _size;
				uint16_t _count;
			private:
				I2CSlaveDevice(const I2CSlaveDevice &) = delete;
				I2CSlaveDevice & operator = (const I2CSlaveDevice &) = delete;
			protected:
				I2CSlaveDevice(I2C_TypeDef *gpio);
				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;
				virtual void resetImpl() = 0;
			public:
				inline void activate() {
					activateImpl();
				}
				inline void deactivate() {
					activateImpl();
				}
				inline void reset() {
					resetImpl();
				}
				void initialize(uint16_t addr);
				void deinitialize();
				void setTimming(uint8_t prescaler, uint8_t scldel, uint8_t sdadel, uint8_t sclh, uint8_t scll);
				void setInterruptFunction(I2CInterruptFunction function, I2CInterruptParam param);
				inline void enable() {
					_i2c->CR1 |= I2C_CR1_PE;
				}
				inline void disable() {
					_i2c->CR1 &= ~I2C_CR1_PE;
				}
				void listen(uint8_t *buffer, uint16_t size);
				void interruptService();
		};

		typedef I2CSlaveDevice *I2CSlaveDeviceHandler;


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
				static constexpr uint32_t _rccResetAddr = HI::rccResetAddr;
				static constexpr uint32_t _rccResetPos = HI::rccResetPos;
				static I2CSlaveDeviceX _device;
			public:
				static constexpr DeviceID deviceID = deviceID_;
			private:
				I2CSlaveDeviceX() :
					I2CSlaveDevice(reinterpret_cast<I2C_TypeDef *>(_i2cAddr)) {
				}
			protected:
				void activateImpl() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivateImpl() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
				void resetImpl() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccResetAddr);
					*p |= 1 << _rccResetPos;
					*p &= ~(1 << _rccResetPos);
				}
			public:
				static constexpr I2CSlaveDeviceX * getHandler() {
					return &_device;
				}
				template <typename pin_>
				void initSCLPin() {
					gpio::PinFunctionID pinFunctionID = internal::I2CPinFunctionID<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::openDrain, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initSDAPin() {
					gpio::PinFunctionID pinFunctionID = internal::I2CPinFunctionID<deviceID_, PinFunction::sda, pin_>::alt;
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
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C1RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C1RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C1RST_Pos;
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
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C2RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C2RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C2RST_Pos;
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
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C3RST_Pos;
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
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C4RST_Pos;
				#endif
			};
			#endif

		}
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/htlI2C_AF_G030.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/htlI2C_AF_G031.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/htlI2C_AF_F030.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlI2C_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlI2C_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlI2C__

