#pragma once
#ifndef __STM32_htlDMA__
#define __STM32_htlDMA__


#include "htl/STM32/htl.h"


namespace htl {

	namespace dma {

		enum class DeviceID {
            #ifdef HTL_DMA1_CHANNEL1_EXIST
			dma1_1,
            #endif
            #ifdef HTL_DMA1_CHANNEL2_EXIST
			dma1_2,
            #endif
            #ifdef HTL_DMA1_CHANNEL3_EXIST
			dma1_3,
            #endif
            #ifdef HTL_DMA1_CHANNEL4_EXIST
			dma1_4,
            #endif
            #ifdef HTL_DMA1_CHANNEL5_EXIST
			dma1_5,
            #endif
            #ifdef HTL_DMA1_CHANNEL6_EXIST
			dma1_6,
            #endif
            #ifdef HTL_DMA1_CHANNEL7_EXIST
			dma1_7
            #endif
		};

		enum class RequestID {
		    spi1_rx = 16,
		    spi1_tx = 17,
		    spi2_rx = 18,
		    spi2_tx = 19
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

		class DMADevice {
		    public:
		        enum class State {
		            reset,
		            ready,
		            transfering
		        };
			private:
				uint32_t const _channel;
				State _state;
            private:
                DMADevice(const DMADevice &) = delete;
                DMADevice & operator = (const DMADevice &) = delete;
                inline void activate() {
                    activateImpl();
                }
                inline void deactivate() {
                    activateImpl();
                }
			protected:
				DMADevice(uint32_t channel);
                void interruptService();
                virtual void activateImpl() = 0;
                virtual void deactivateImpl() = 0;
			public:
				void initMemoryToMemory();
                void initMemoryToPeripheral(Priority priority,
                        DataSize srcSize, DataSize dstSize,
                        AddressIncrement srcInc, AddressIncrement dstInc,
                        TransferMode mode, RequestID requestID);
                void initPeripheralToMemory(Priority priority,
                        DataSize srcSize, DataSize dstSize,
                        AddressIncrement srcInc, AddressIncrement dstInc,
                        TransferMode mode, RequestID requestID);
				void deinitialize();
				void start(const uint8_t *src, uint8_t *dst, uint32_t size);
				void start_IRQ(const uint8_t *src, uint8_t *dst, uint32_t size);
				bool waitForFinish(uint16_t timeout = 0xFFFF);
				void finish();
				State getState() const { return _state; }
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
                static constexpr auto _channel = uint32_t(deviceID_);
                static constexpr auto _rccEnableAddr = DMATraits::rccEnableAddr;
                static constexpr auto _rccEnablePos = DMATraits::rccEnablePos;
                static DMADeviceX _instance;
            private:
                inline DMADeviceX() :
                    DMADevice(_channel) {
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
		    struct DMATraits<DeviceID::dma1_1> {
                static constexpr uint32_t rccEnableAddr =
                        RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
		    };
            #endif

            #ifdef HTL_DMA1_CHANNEL2_EXIST
		    template <>
            struct DMATraits<DeviceID::dma1_2> {
                static constexpr uint32_t rccEnableAddr =
                        RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
            };
            #endif

		    #ifdef HTL_DMA1_CHANNEL3_EXIST
            template <>
            struct DMATraits<DeviceID::dma1_3> {
                static constexpr uint32_t rccEnableAddr =
                        RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
                static constexpr uint32_t rccEnablePos = RCC_AHBENR_DMA1EN_Pos;
            };
            #endif
		}

        #ifdef HTL_DMA1_CHANNEL1_EXIST
		using DMADevice11 = DMADeviceX<DeviceID::dma1_1>;
        #endif
        #ifdef HTL_DMA1_CHANNEL2_EXIST
        using DMADevice12 = DMADeviceX<DeviceID::dma1_2>;
        #endif
        #ifdef HTL_DMA1_CHANNEL3_EXIST
        using DMADevice13 = DMADeviceX<DeviceID::dma1_3>;
        #endif
        #ifdef HTL_DMA1_CHANNEL4_EXIST
        using DMADevice14 = DMADeviceX<DeviceID::dma1_4>;
        #endif
        #ifdef HTL_DMA1_CHANNEL5_EXIST
        using DMADevice15 = DMADeviceX<DeviceID::dma1_5>;
        #endif
        #ifdef HTL_DMA1_CHANNEL6_EXIST
        using DMADevice16 = DMADeviceX<DeviceID::dma1_6>;
        #endif
        #ifdef HTL_DMA1_CHANNEL7_EXIST
        using DMADevice17 = DMADeviceX<DeviceID::dma1_7>;
        #endif
	}
}


#endif // __STM32_htlDMA__
