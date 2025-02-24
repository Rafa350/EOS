#pragma once
#ifndef __STM32_htlDMA__
#define __STM32_htlDMA__


#include "htl/STM32/htl.h"


namespace htl {

	namespace dma {

        /// Identificador del dispositiu.
        ///
		enum class DeviceID {
            #ifdef HTL_DMA1_CHANNEL1_EXIST
			_11,
            #endif
            #ifdef HTL_DMA1_CHANNEL2_EXIST
			_12,
            #endif
            #ifdef HTL_DMA1_CHANNEL3_EXIST
			_13,
            #endif
            #ifdef HTL_DMA1_CHANNEL4_EXIST
			_14,
            #endif
            #ifdef HTL_DMA1_CHANNEL5_EXIST
			_15,
            #endif
            #ifdef HTL_DMA1_CHANNEL6_EXIST
			_16,
            #endif
            #ifdef HTL_DMA1_CHANNEL7_EXIST
			_17,
            #endif
            #ifdef HTL_DMA2_CHANNEL1_EXIST
			_21,
            #endif
            #ifdef HTL_DMA3_CHANNEL2_EXIST
			_22,
            #endif
            #ifdef HTL_DMA4_CHANNEL3_EXIST
			_23,
            #endif
            #ifdef HTL_DMA5_CHANNEL4_EXIST
			_24,
            #endif
            #ifdef HTL_DMA6_CHANNEL5_EXIST
			_25,
            #endif
            #ifdef HTL_DMA7_CHANNEL6_EXIST
			_26,
            #endif
            #ifdef HTL_DMA8_CHANNEL7_EXIST
			_27
            #endif
		};

		enum class RequestID {
		    i2c1RX = 10,
		    i2c1TX = 11,
		    i2c2TX = 12,
		    i2c2RX = 13,
		    spi1RX = 16,
		    spi1TX = 17,
		    spi2RX = 18,
		    spi2TX = 19,
		    uart1RX = 50,
		    uart1TX = 51,
            uart2RX = 52,
            uart2TX = 53,
            uart3RX = 54,
            uart3TX = 55,
            uart4RX = 56,
            uart4TX = 57,
            uart5RX = 74,
            uart5TX = 75,
            uart6RX = 76,
            uart6TX = 77
		};

		enum class TransferMode {
		    normal,
		    circular
		};

        enum class DataSize {
            byte,
            word,
            qword
        };

        enum class AddressIncrement {
            none,
            inc
		};

		enum class Priority {
            low,
            medium,
            hight,
            veryHight
		};


        enum class NotifyID {
            null,
            half,
            completed,
            error
        };

        struct NotifyEventArgs {
            NotifyID id;
            bool irq;
        };

        class DMADevice;
        using INotifyEvent = eos::ICallbackP2<DMADevice*, NotifyEventArgs&>;
        template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, DMADevice*, NotifyEventArgs&>;

        namespace internal {
            typedef struct {
                DMA_TypeDef * const dma;
				#if defined(EOS_PLATFORM_STM32G0)
                DMA_Channel_TypeDef * const dmac;
                DMAMUX_Channel_TypeDef * const muxc;
				#endif
                unsigned const flagPos;
            } DMADEV_TypeDef;

            extern const DMADEV_TypeDef __dmadev11;
            extern const DMADEV_TypeDef __dmadev12;
            extern const DMADEV_TypeDef __dmadev13;
            extern const DMADEV_TypeDef __dmadev14;
            extern const DMADEV_TypeDef __dmadev15;
            extern const DMADEV_TypeDef __dmadev16;
            extern const DMADEV_TypeDef __dmadev17;
        }

		class DMADevice {
		    public:
		        enum class State {
		            reset,
		            ready,
		            transfering
		        };

			private:
		        const internal::DMADEV_TypeDef * const _dmadev;
				State _state;
                INotifyEvent *_notifyEvent;
                bool _notifyEventEnabled;

            private:
                DMADevice(const DMADevice &) = delete;
                DMADevice & operator = (const DMADevice &) = delete;

                void notifyTransferCompleted(bool irq);
                void notifyHalfTransfer(bool irq);

                inline void activate() {
                    activateImpl();
                }
                inline void deactivate() {
                    activateImpl();
                }

			protected:
				DMADevice(const internal::DMADEV_TypeDef *dmadev);
                void interruptService();
                virtual void activateImpl() = 0;
                virtual void deactivateImpl() = 0;

			public:
                eos::Result initMemoryToMemory();
                eos::Result initMemoryToPeripheral(Priority priority,
                        DataSize srcSize, DataSize dstSize,
                        AddressIncrement srcInc, AddressIncrement dstInc,
                        TransferMode mode, RequestID requestID);
                eos::Result initPeripheralToMemory(Priority priority,
                        DataSize srcSize, DataSize dstSize,
                        AddressIncrement srcInc, AddressIncrement dstInc,
                        TransferMode mode, RequestID requestID);
                eos::Result deinitialize();

                void setNotifyEvent(INotifyEvent &event, bool enabled = true);
                inline void enableNotifyEvent() {
                    _notifyEventEnabled = _notifyEvent != nullptr;
                }
                inline void disableNotifyEvent() {
                    _notifyEventEnabled = false;
                }

                eos::Result start(const uint8_t *src, uint8_t *dst, unsigned size);

				// TODO: temporal
                eos::Result waitForFinish(unsigned timeout);

				inline State getState() const { return _state; }
                inline bool isReady() const { return _state == State::ready; }
		};


		namespace internal {

		    template <DeviceID>
            struct DMATraits;
		}


		template <DeviceID deviceID_>
		class DMADeviceX final: public DMADevice {
            private:
                using DMATraits = internal::DMATraits<deviceID_>;

            private:
                static constexpr auto dmadev = DMATraits::dmadev;
                static constexpr auto _rccEnableAddr = DMATraits::rccEnableAddr;
                static constexpr auto _rccEnablePos = DMATraits::rccEnablePos;
                static DMADeviceX _instance;

            private:
                inline DMADeviceX() :
                    DMADevice(dmadev) {
                }

            protected:
                void activateImpl() override {
                    auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
                    *p |= 1 << _rccEnablePos;
                    __DSB();
                }
                void deactivateImpl() override {
                    auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
                    *p &= ~(1 << _rccEnablePos);
                }

            public:
                static constexpr auto deviceID = deviceID_;
                static constexpr DMADeviceX *pInst = &_instance;
                static constexpr DMADeviceX &rInst = _instance;

		    public:
                inline static void interruptHandler() {
                    _instance.interruptService();
                }
		};

        template <DeviceID deviceID_>
        DMADeviceX<deviceID_> DMADeviceX<deviceID_>::_instance;


		namespace internal {

            #ifdef HTL_DMA1_CHANNEL1_EXIST
		    template <>
		    struct DMATraits<DeviceID::_11> {
		        static constexpr const DMADEV_TypeDef *dmadev = &__dmadev11;
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				#if defined(EOS_PLATFORM_STM32F0)
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMAEN_Pos;
				#else
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
				#endif
		    };
            #endif

            #ifdef HTL_DMA1_CHANNEL2_EXIST
		    template <>
            struct DMATraits<DeviceID::_12> {
                static constexpr const DMADEV_TypeDef *dmadev = &__dmadev12;
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				#if defined(EOS_PLATFORM_STM32F0)
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMAEN_Pos;
				#else
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
				#endif
            };
            #endif

		    #ifdef HTL_DMA1_CHANNEL3_EXIST
            template <>
            struct DMATraits<DeviceID::_13> {
                static constexpr const DMADEV_TypeDef *dmadev = &__dmadev13;
                static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				#if defined(EOS_PLATFORM_STM32F0)
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMAEN_Pos;
				#else
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
				#endif
            };
            #endif
		}

        #ifdef HTL_DMA1_CHANNEL1_EXIST
		using DMADevice11 = DMADeviceX<DeviceID::_11>;
        #endif
        #ifdef HTL_DMA1_CHANNEL2_EXIST
        using DMADevice12 = DMADeviceX<DeviceID::_12>;
        #endif
        #ifdef HTL_DMA1_CHANNEL3_EXIST
        using DMADevice13 = DMADeviceX<DeviceID::_13>;
        #endif
        #ifdef HTL_DMA1_CHANNEL4_EXIST
        using DMADevice14 = DMADeviceX<DeviceID::_14>;
        #endif
        #ifdef HTL_DMA1_CHANNEL5_EXIST
        using DMADevice15 = DMADeviceX<DeviceID::_15>;
        #endif
        #ifdef HTL_DMA1_CHANNEL6_EXIST
        using DMADevice16 = DMADeviceX<DeviceID::_16>;
        #endif
        #ifdef HTL_DMA1_CHANNEL7_EXIST
        using DMADevice17 = DMADeviceX<DeviceID::_17>;
        #endif
	}
}


#endif // __STM32__htlDMA__
