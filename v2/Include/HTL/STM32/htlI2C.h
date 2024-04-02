#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "System/eosResults.h"


namespace htl {

	namespace i2c {

	    class I2CDevice;
	    class I2CMasterDevice;
	    class I2CSlaveDevice;


	    /// Identificador del dispositiu.
	    ///
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
        
        
		/// Identificador de la notificacio.
		///
        enum class NotifyID {
            addressMatch,    ///< Conindicencia en l'adressa.
            rxDataAvailable, ///< Dades rebudes disponibles.
            rxCompleted,     ///< Recepcio de dades finalitzada.
            txDataRequest,   ///< Solicitut de dades per transmetre.
            txCompleted      ///< Transmissio de dades finalitzada.
        };
        
        struct NotifyEventArgs {
            I2CDevice * const instance;     ///< La instancia del dispositiu.
            NotifyID id;            
            bool irq;
            union {
                struct {
                    uint16_t addr;
                } AddressMatch;
                struct {
                    const uint8_t *buffer;
                    unsigned length;
                } RxDataAvailable;
                struct {
                    const uint8_t *buffer;
                    unsigned length;
                } RxCompleted;
                struct {
                    uint8_t *buffer;
                    unsigned bufferSize;
                    unsigned length;
                } TxDataRequest;
                struct {
                    unsigned length;
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


        using ISlaveNotifyEvent = eos::ICallbackP1<NotifyEventArgs&>;
        template <typename Instance_> using SlaveNotifyEvent = eos::CallbackP1<Instance_, NotifyEventArgs&>;

        using IMasterNotifyEvent = eos::ICallbackP1<NotifyEventArgs&>;
        template <typename Instance_> using MasterNotifyEvent = eos::CallbackP1<Instance_, NotifyEventArgs&>;


		class I2CDevice {
		    protected:
                I2C_TypeDef * const _i2c;

			protected:
                I2CDevice(I2C_TypeDef *i2c): _i2c {i2c} {}

                /// Habilita el dispositiu.
                ///
                inline void enable() const {
                    _i2c->CR1 |= I2C_CR1_PE;
                }

                /// Deshabilita el dispositiu.
                ///
                inline void disable() const {
                    _i2c->CR1 &= ~I2C_CR1_PE;
                }

                /// Habilita la interrupcio 'AddressMatch'
                ///
                inline void enableAddressMatchInterrupt() const {
                    _i2c->CR1 |= I2C_CR1_ADDRIE;
                }

                /// Habilita la interrupcio 'RxBufferNotEmpty'
                ///
                inline void enableRxBufferNotEmptyInterrupt() const {
                    _i2c->CR1 |= I2C_CR1_RXIE;
                }

                /// Habilita la interrupcio 'TxBufferEmpty'
                ///
                inline void enableTxBufferEmptyInterrupt() const {
                    _i2c->CR1 |= I2C_CR1_TXIE;
                }

                /// Habilita la interrupcio 'StopDetection'
                ///
                inline void enableStopDetectionInterrupt() const {
                    _i2c->CR1 |= I2C_CR1_STOPIE;
                }

                /// Desabilita la interrupcio 'AddressMatch'.
                ///
                inline void disableAddressMatchInterrupt() const {
                    _i2c->CR1 &= ~I2C_CR1_ADDRIE;
                }

                /// Desabilita la interrupcio 'RxBufferNotEmpty'
                ///
                inline void disableRxBufferNotEmptyInterrupt() const {
                    _i2c->CR1 &= ~I2C_CR1_RXIE;
                }

                /// Desabilita la interrupcio 'TxBufferEmpty'
                ///
                inline void disableTxBufferEmptyInterrupt() const {
                    _i2c->CR1 &= ~I2C_CR1_TXIE;
                }

                /// Desabilita la interrupcio 'StopDetection'
                ///
                inline void disableStopDetectionInterrupt() const {
                    _i2c->CR1 &= ~I2C_CR1_STOPIE;
                }

                /// Comprova si la interrupcio 'AddressMatch' esta habilitada.
                /// \return True si esta habilitada.
                ///
                inline bool isAddressMatchInterruptEnabled() const {
                    return (_i2c->CR1 & I2C_CR1_ADDRIE) != 0;
                }

                /// Comprova si la interrupcio 'RxBufferNotEmpty' esta habilitada.
                /// \return True si esta habilitada.
                ///
                inline bool isRxBufferNotEmptyInterruptEnabled() const {
                    return (_i2c->CR1 & I2C_CR1_RXIE) != 0;
                }

                /// Comprova si la interrupcio 'TxBufferEmpty' esta habilitada.
                /// \return True si esta habilitada.
                ///
                inline bool isTxBufferEmptyInterruptEnabled() const {
                    return (_i2c->CR1 & I2C_CR1_TXIE) != 0;
                }

                /// Comprova si la interrupcio 'StopDetection' esta habilitada.
                /// \return True si esta habilitada.
                ///
                inline bool isStopDetectionInterruptEnabled() const {
                    return (_i2c->CR1 & I2C_CR1_STOPIE) != 0;
                }

                /// Comprova si la interrupcio 'NackDetection' esta habilitada.
                /// \return True si esta habilitada.
                ///
                inline bool isNackDetectionInterruptEnabled() const {
                    return (_i2c->CR1 & I2C_CR1_NACKIE) != 0;
                }

                /// Comprova si el flag 'AddressMatch' esta activat.
                /// \return True si esta activat.
                ///
                inline bool isAddressMatchFlagSet() const {
                    return (_i2c->ISR & I2C_ISR_ADDR) != 0;
                }

                /// Comprova si el flag 'RxBufferNotEmpty' esta activat.
                /// \return True si esta activat.
                ///
                inline bool isRxBufferNotEmptyFlagSet() const {
                    return (_i2c->ISR & I2C_ISR_RXNE) != 0;
                }

                /// Comprova si el flag 'TxBufferEmpty' esta activat.
                /// \return True si esta activat.
                ///
                inline bool isTxBufferEmptyFlagSet() const {
                    return (_i2c->ISR & I2C_ISR_TXE) != 0;
                }

                /// Comprova si el flag 'StopDetection' esta activat.
                /// \return True si esta activat.
                ///
                inline bool isStopDetectionFlagSet() const {
                    return (_i2c->ISR & I2C_ISR_STOPF) != 0;
                }

                /// Comprova si el flag 'NackDetection' esta activat.
                /// \return True si esta activat.
                ///
                inline bool isNackDetectionFlagSet() const {
                    return (_i2c->ISR & I2C_ISR_NACKF) != 0;
                }

                /// Borra el flag 'AddressMatch'
                ///
                inline void clearAddressMatchFlag() const {
                    _i2c->ICR |= I2C_ICR_ADDRCF;
                }

                /// Borra el flag 'StopDetection'
                ///
                inline void clearStopDetectionFlag() const {
                    _i2c->ICR |= I2C_ICR_STOPCF;
                }

                virtual void activate() = 0;
				virtual void deactivate() = 0;
				virtual void reset() = 0;
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
				State _state;
				uint8_t *_buffer;
				unsigned _bufferSize;
				unsigned _count;
				unsigned _length;
                ISlaveNotifyEvent *_notifyEvent;
                bool _notifyEventEnabled;
                
			private:
				I2CSlaveDevice(const I2CSlaveDevice &) = delete;
				I2CSlaveDevice & operator = (const I2CSlaveDevice &) = delete;

                void notifyAddressMatch(uint16_t addr, bool irq);
                void notifyRxDataAvailable(const uint8_t *buffer, unsigned length, bool irq);
                void notifyRxCompleted(const uint8_t *buffer, unsigned length, bool irq);
                void notifyTxDataRequest(uint8_t *buffer, unsigned bufferSize, unsigned &length, bool irq);
                void notifyTxCompleted(bool irq);

				void interruptServiceListen();
				void interruptServiceListenRx();
				void interruptServiceListenTx();
                
			protected:
				I2CSlaveDevice(I2C_TypeDef *i2c);
				void interruptService();
                
			public:
				Result initialize(uint16_t addr, uint8_t prescaler, uint8_t scldel, uint8_t sdadel, uint8_t sclh, uint8_t scll);
				Result deinitialize();
                
				void setNotifyEvent(ISlaveNotifyEvent &event, bool enabled = true);

				/// Habilita l'event de notificacio.
				///
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}

				/// Deshabilita l'event de notificacio.
				///
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}
                
				Result listem(uint8_t *buffer, unsigned bufferSize, Tick timeout = Tick(-1));
				Result listen_IRQ(uint8_t *buffer, unsigned bufferSize);
				Result abortListen();
                
				/// Obte l'estat del dispositiu.
				///
				inline State getState() const { return _state; }

				/// Comprova si el dispositiu esta preparat.
				///
				inline bool isReady() const { return _state == State::ready; }
		};

		class I2CMasterDevice: public I2CDevice {
			public:
				enum class State {
					reset,
					ready
				};
                
			private:
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
                
				Result send(uint16_t addr, const uint8_t *buffer, unsigned bufferSize, Tick timeout);
				Result receive(uint16_t addr, uint8_t *buffer, unsigned bufferSize, Tick timeout);
		};


		namespace internal {

			template <DeviceID>
			class I2CTraits;

			template <DeviceID, PinFunction, typename>
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
                static constexpr uint32_t _rccResetAddr = I2CTraits::rccResetAddr;
                static constexpr uint32_t _rccResetPos = I2CTraits::rccResetPos;
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
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
				}                
				template <typename pin_>
				void inline initPinSDA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void inline initPinALERT() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::alert, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
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
				using I2CTraits = internal::I2CTraits<deviceID_>;
                
			private:
				static constexpr uint32_t _i2cAddr = I2CTraits::i2cAddr;
				static constexpr uint32_t _rccEnableAddr = I2CTraits::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = I2CTraits::rccEnablePos;
                static constexpr uint32_t _rccResetAddr = I2CTraits::rccResetAddr;
                static constexpr uint32_t _rccResetPos = I2CTraits::rccResetPos;
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
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::scl, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void inline initPinSDA() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sda, pin_>::alt;
					pin_::initAlternate(gpio::AlternateMode::openDrain, gpio::Speed::fast, af);
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
