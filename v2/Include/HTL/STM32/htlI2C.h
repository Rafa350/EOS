#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


/// \file      htlI2C.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     I2C device manager.


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	namespace i2c {

	    class I2CDevice;
	    class I2CMasterDevice;
	    class I2CSlaveDevice;

	    // Adressa I2C
	    //
	    typedef uint16_t I2CAddr;

	    /// Identificador del dispositiu.
	    ///
		enum class DeviceID {
#ifdef HTL_I2C1_EXIST
			i2c1,
#endif
#ifdef HTL_I2C2_EXIST
			i2c2,
#endif
#ifdef HTL_I2C3_EXIST
			i2c3,
#endif
#ifdef HTL_I2C4_EXIST
			i2c4
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
			smba
		};

        /// Identificador de la notificacio.
		///
        enum class NotifyID {
        	null,
            addressMatch,    ///< Coindicencia en l'adressa.
            rxStart,         ///< Inici de la recepcio.
            rxCompleted,     ///< Recepcio finalitzada.
            txStart,         ///< Inici de la transmissio.
            txCompleted,     ///< Transmissio finalitzada.
			error
        };

        struct NotifyEventArgs {
            bool irq;
            union {
                struct {
                    I2CAddr addr;       ///< L'adressa coincident.
                } addressMatch;
                struct {
                    uint8_t *buffer;     ///< Buffer de dades.
                    unsigned bufferSize; ///< Tamany del buffer de dades.
                } rxStart;
                struct {
                    unsigned length;     ///< Nombre de bytes rebuts.
                } rxCompleted;
                struct {
                    uint8_t *buffer;     ///< Buffer de dades
                    unsigned length;     ///< Nombre de bytes a transmetre.
                } txStart;
                struct {
                    unsigned length;     ///< Nombre de bytes transmessos.
                } txCompleted;
            };
        };


        using SlaveNotifyRaiser = eos::NotifyEventRaiser<NotifyID, NotifyEventArgs>;
        using ISlaveNotifyEvent = SlaveNotifyRaiser::IEvent;
        template <typename Instance_> using SlaveNotifyEvent = SlaveNotifyRaiser::Event<Instance_>;

        using MasterNotifyRaiser = eos::NotifyEventRaiser<NotifyID, NotifyEventArgs>;
        using IMasterNotifyEvent = MasterNotifyRaiser::IEvent;
        template <typename Instance_> using MasterNotifyEvent = MasterNotifyRaiser::Event<Instance_>;


		class I2CDevice {
		    protected:
                I2C_TypeDef * const _i2c;

			protected:
                I2CDevice(I2C_TypeDef *i2c): _i2c {i2c} {}

                virtual void activate() = 0;
				virtual void deactivate() = 0;
				virtual void reset() = 0;
		};

		class I2CSlaveDevice: public I2CDevice {
			public:
				enum class State {
					invalid,
					reset,
					ready,
					listen,
					receiving,
					transmiting
				};

			private:
				State _state;
				bool _restart;
				uint8_t *_buffer;
				unsigned _dataCount;
				unsigned _xferCount;
				SlaveNotifyRaiser _erNotify;

			private:
				I2CSlaveDevice(const I2CSlaveDevice &) = delete;
				I2CSlaveDevice & operator = (const I2CSlaveDevice &) = delete;

                void notifyAddressMatch(I2CAddr addr, bool irq);
                void notifyRxStart(uint8_t * &buffer, unsigned &bufferSize, bool irq);
                void notifyRxCompleted(unsigned length, bool irq);
                void notifyTxStart(uint8_t * &buffer, unsigned &length, bool irq);
                void notifyTxCompleted(unsigned length, bool irq);

				void interruptServiceListen();
				void interruptServiceReceive();
				void interruptServiceTransmit();

			protected:
				I2CSlaveDevice(I2C_TypeDef *i2c);
				void interruptService();

			public:
				eos::Result initialize(I2CAddr addr, uint8_t prescaler, uint8_t scldel, uint8_t sdadel, uint8_t sclh, uint8_t scll);
				eos::Result deinitialize();

				eos::Result setNotifyEvent(ISlaveNotifyEvent &event, bool enabled = true);

				/// Habilita l'event de notificacio.
				///
				inline void enableNotifyEvent() {
					_erNotify.enable();
				}

				/// Deshabilita l'event de notificacio.
				///
				inline void disableNotifyEvent() {
					_erNotify.disable();
				}

				eos::Result listen(unsigned timeout);
				eos::Result listen_IRQ(bool restart);
				eos::Result abort();

				/// Obte l'estat del dispositiu.
				///
				inline State getState() const { return _state; }
				inline bool isValid() const { return _state != State::invalid; }
				inline bool isReady() const { return _state == State::ready; }
				inline bool isBusy() const { return _state != State::ready; }
		};

		class I2CMasterDevice: public I2CDevice {
			public:
				enum class State {
					invalid,
					reset,
					ready,
                    transmiting,
                    receiving
				};

			private:
				State _state;
				MasterNotifyRaiser _erNotify;
                uint8_t *_buffer;
                unsigned _maxCount;
                unsigned _count;

			private:
				I2CMasterDevice(const I2C_TypeDef&) = delete;
				I2CMasterDevice & operator = (const I2CMasterDevice &) = delete;

				void notifyTxCompleted(unsigned length, bool irq);
				void notifyRxCompleted(unsigned length, bool irq);

			protected:
				I2CMasterDevice(I2C_TypeDef *i2c);
				void interruptService();
				void interruptServiceTransmit();
				void interruptServiceReceive();

			public:
				eos::Result initialize(uint8_t prescaler, uint8_t scldel, uint8_t sdadel,
					uint8_t sclh, uint8_t scll);
				eos::Result deinitialize();

				eos::Result setNotifyEvent(IMasterNotifyEvent &event, bool enabled = true);

				/// Habilita l'event de notificacio.
				///
				inline void enableNotifyEvent() {
					_erNotify.enable();
				}

				/// Deshabilita l'event de notificacio.
				///
				inline void disableNotifyEvent() {
					_erNotify.disable();
				}

				eos::Result transmit(I2CAddr addr, const uint8_t *buffer, unsigned length, unsigned timeout);
				eos::Result receive(I2CAddr addr, uint8_t *buffer, unsigned bufferSize, unsigned timeout);

				eos::Result transmit_IRQ(I2CAddr addr, const uint8_t *buffer, unsigned length);
				eos::Result receive_IRQ(I2CAddr addr, uint8_t *buffer, unsigned bufferSize);

				/// Obte l'estat del dispositiu.
				///
				inline State getState() const { return _state; }
				inline bool isValid() const { return _state != State::invalid; }
				inline bool isReady() const { return _state == State::ready; }
				inline bool isBusy() const { return _state != State::ready; }
		};


		namespace internal {

			template <DeviceID>
			class I2CTraits;

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;
		}

		template <DeviceID deviceID_>
		class I2CSlaveDeviceX final: public I2CSlaveDevice {
			private:
				using I2CTraits = internal::I2CTraits<deviceID_>;

			private:
				static constexpr auto _i2cAddr = I2CTraits::i2cAddr;
				static constexpr auto _rccEnableAddr = I2CTraits::rccEnableAddr;
				static constexpr auto _rccEnablePos = I2CTraits::rccEnablePos;
                static constexpr auto _rccResetAddr = I2CTraits::rccResetAddr;
                static constexpr auto _rccResetPos = I2CTraits::rccResetPos;
				static I2CSlaveDeviceX _instance;

			public:
				static constexpr auto deviceID = deviceID_;
				static constexpr I2CSlaveDeviceX *pInst = &_instance;
				static constexpr I2CSlaveDeviceX &rInst = _instance;

			private:
				constexpr I2CSlaveDeviceX() :
					I2CSlaveDevice {reinterpret_cast<I2C_TypeDef *>(_i2cAddr)} {
				}

			protected:
				void activate() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivate() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}

                void reset() override {
                    auto p = reinterpret_cast<uint32_t *>(_rccResetAddr);
                    *p |= 1 << _rccResetPos;
                    while ((*p & (1 << _rccResetPos)) == 0)
                        continue;
                    *p &= ~(1 << _rccResetPos);
                    while ((*p & (1 << _rccResetPos)) != 0)
                        continue;
                }

			public:
				inline static void interruptHandler() {
					_instance.interruptService();
				}

				template <typename pin_>
				void inline initPinSCL() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void inline initPinSDA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void inline initPinSMBA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::smba, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		I2CSlaveDeviceX<deviceID_> I2CSlaveDeviceX<deviceID_>::_instance;


		#ifdef HTL_I2C1_EXIST
		typedef I2CSlaveDeviceX<DeviceID::i2c1> I2CSlaveDevice1;
		#endif
		#ifdef HTL_I2C2_EXIST
		typedef I2CSlaveDeviceX<DeviceID::i2c2> I2CSlaveDevice2;
		#endif
		#ifdef HTL_I2C3_EXIST
		typedef I2CSlaveDeviceX<DeviceID::i2c3> I2CSlaveDevice3;
		#endif
		#ifdef HTL_I2C4_EXIST
		typedef I2CSlaveDeviceX<DeviceID::i2c4> I2CSlaveDevice4;
		#endif


		template <DeviceID deviceID_>
		class I2CMasterDeviceX final: public I2CMasterDevice {
			private:
				using I2CTraits = internal::I2CTraits<deviceID_>;

			private:
				static constexpr auto _i2cAddr = I2CTraits::i2cAddr;
				static constexpr auto _rccEnableAddr = I2CTraits::rccEnableAddr;
				static constexpr auto _rccEnablePos = I2CTraits::rccEnablePos;
                static constexpr auto _rccResetAddr = I2CTraits::rccResetAddr;
                static constexpr auto _rccResetPos = I2CTraits::rccResetPos;
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

				void reset() override {

				}

			public:
				inline static void interruptHandler() {
					_instance.interruptService();
				}

				template <typename pin_>
				void inline initPinSCL() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void inline initPinSDA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::openDrain, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		I2CMasterDeviceX<deviceID_> I2CMasterDeviceX<deviceID_>::_instance;


		#ifdef HTL_I2C1_EXIST
		typedef I2CMasterDeviceX<DeviceID::i2c1> I2CMasterDevice1;
		#endif
		#ifdef HTL_I2C2_EXIST
		typedef I2CMasterDeviceX<DeviceID::i2c2> I2CMasterDevice2;
		#endif
		#ifdef HTL_I2C3_EXIST
		typedef I2CMasterDeviceX<DeviceID::i2c3> I2CMasterDevice3;
		#endif
		#ifdef HTL_I2C4_EXIST
		typedef I2CMasterDeviceX<DeviceID::i2c4> I2CMasterDevice4;
		#endif


#ifndef STM32G0
		namespace internal {

			#ifdef HTL_I2C1_EXIST
			template <>
			struct I2CTraits<DeviceID::_1> {
				static constexpr uint32_t i2cAddr = I2C1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C1EN_Pos;
                static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
                static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C1RST_Pos;
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
			struct I2CTraits<DeviceID::_2> {
				static constexpr uint32_t i2cAddr = I2C2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C2EN_Pos;
                static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
                static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C2RST_Pos;
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
			struct I2CTraits<DeviceID::_3> {
				static constexpr uint32_t i2cAddr = I2C3_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C3EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_I2C4_EXIST
			template <>
			struct I2CTraits<DeviceID::_4> {
				static constexpr uint32_t i2cAddr = I2C4_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C4EN_Pos;
				#endif
			};
			#endif

		}

		#endif
	}
}


#if defined(EOS_PLATFORM_STM32G030)
	#include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/G0/G030/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32G031)
	#include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/G0/G031/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32G051)
	#include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/G0/G051/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32G071)
	#include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/G0/G071/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/G0/G0B1/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32F030)
	#include "htl/STM32/G0/htlI2C_Traits.h"
    #include "htl/STM32/F0/F030/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32F429)
    #include "htl/STM32/F4/F429/htlI2C_Pins.h"

#elif defined(EOS_PLATFORM_STM32F746)
	#include "htl/STM32/F7/htlI2C_Traits.h"
    #include "htl/STM32/F7/F746/htlI2C_Pins.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlI2C__
