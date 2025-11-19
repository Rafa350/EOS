#pragma once
#ifndef __STM32_htlCAN__
#define __STM32_htlCAN__


#include "HTL/htl.h"


#ifdef HTL_CANx_EXIST


#include "HTL/htlBits.h"
#include "HTL/STM32/htlGPIO.h"


// Default options
//
#ifndef HTL_FDCAN_OPTION_IRQ
	#define HTL_FDCAN_OPTION_IRQ HTL_FDCAN_DEFAULT_OPTION_IRQ
#endif

#ifndef HTL_FDCAN_OPTION_DMA
	#define HTL_FDCAN_OPTION_DMA HTL_FDCAN_DEFAULT_OPTION_DMA
#endif

#ifndef HTL_FDCAN_OPTION_DEACTIVATE
	#define HTL_FDCAN_OPTION_DEACTIVATE HTL_FDCAN_DEFAULT_OPTION_DEACTIVATE
#endif



namespace htl {

	namespace can {

		// Identificador del disposisiu
		//
		enum class DeviceID {
			can1,
			can2
		};

		// Funcio dels pins
		//
		enum class PinFunction {
			tx,
			rx
		};

		enum class RxFifoSelection {
			fifo0,
			fifo1
		};

		enum class ClockSource {
			pclk,
			pllqclk,
			hse
		};

		namespace internal {

			template <DeviceID>
			struct CANTraits;

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;

		}

		typedef uint32_t Identifier;

		enum class IdentifierType {
			standard,
			extended
		};

		enum class DataLength {
			len0,
			len1,
			len2,
			len3,
			len4,
			len5,
			len6,
			len7,
			len8,
			len12,
			len16,
			len20,
			len24,
			len32,
			len48,
			len64
		};

		enum class FrameType {
			dataFrame,
			remoteFrame
		};

		enum class ErrorStateFlag {
			active,
			passive
		};

		enum class BitrateSwitching {
			off,
			on
		};

		enum class FDFormat {
			can,
			fdcan
		};

		enum class TxEventFifoControl {
			noStore,
			store
		};

		struct TxHeader {
			Identifier id;
			IdentifierType idType;
			DataLength dataLength;
			FrameType frameType;
			ErrorStateFlag errorStateFlag;
			BitrateSwitching bitrateSwitching;
			FDFormat fdFormat;
			TxEventFifoControl txEventFifoControl;
			uint8_t messageMarker;
		};

		struct RxHeader {
			Identifier id;
			IdentifierType idType;
			DataLength dataLength;
			FrameType frameType;
			ErrorStateFlag errorStateFlag;
			unsigned filterIndex;
			BitrateSwitching bitrateSwitching;
			FDFormat fdFormat;
		};

		struct TxEvent {
			Identifier id;
			IdentifierType idType;
			DataLength dataLength;
			FrameType frameType;
		};

		enum class FilterType {
			range,
			dual,
			mask,
			disabled
		};

		enum class FilterConfig {
			disable,
			rxFifo0,
			rxFifo1,
			reject,
			hp,
			rxFifo0hp,
			rxFifo1hp
		};

		enum class NonMatchingFrames {
			acceptInRxFifo0,
			acceptInRxFifo1,
			reject
		};

		enum class RejectRemoteFrames {
			filterRemote,
			rejectRemote
		};

		struct Filter {
			unsigned id1;
			unsigned id2;
			IdentifierType idType;
			FilterType type;
			FilterConfig config;
		};

		enum class ClockDivider {
			div1,
			div2,
			div4,
			div6,
			div8,
			div10,
			div12,
			div14,
			div16,
			div18,
			div20,
			div22,
			div24,
			div26,
			div28,
			div30
		};

		enum class FrameFormat {
			classic,
			fdNoBsr,
			fdBsr
		};

		enum class Mode {
			normal,
			restricted,
			busMonitoring,
			internalLoopback,
			externalLoopback
		};

		enum class QFMode {
			fifo,
			queue
		};

		class CANDevice {
			public:
				struct InitParams {
					ClockDivider clockDivider;
					FrameFormat frameFormat;
					Mode mode;
					bool autoRetransmission;
					bool transmitPause;
					bool protocolException;
					unsigned nominalPrescaler;
					unsigned nominalSyncJumpWidth;
					unsigned nominalTimeSeg1;
					unsigned nominalTimeSeg2;
					unsigned dataPrescaler;
					unsigned dataSyncJumpWidth;
					unsigned dataTimeSeg1;
					unsigned dataTimeSeg2;
					unsigned stdFiltersNbr;
					unsigned extFiltersNbr;
					QFMode qfMode;
				};

				enum class NotificationID {
					rxFifoNotEmpty,
					txCompleted
				};
				struct NotificationEventArgs {
					NotificationID id;
					bool irq;
					union {
						struct {
							RxFifoSelection fifo;
						} rxFifoNotEmpty;
						struct {
						} txCompleted;
					};
				};
				using NotificationEventRaiser = eos::EventRaiser<CANDevice, NotificationEventArgs>;
				using INotificationEvent = NotificationEventRaiser::IEvent;
				template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

			public:
				enum class State {
					reset,
					ready,
					running
				};

			private:
				struct StandardFilterElement {
					uint32_t SF;
				};

				struct ExtendedFilterElement {
					uint32_t EF0;
					uint32_t EF1;
				};

				struct RxFifoElement {
					uint32_t R0;
					uint32_t R1;
					uint32_t data[16];
				};

				struct TxEventFifoElement {
					uint32_t E0;
					uint32_t E1;
				};

				struct TxBufferElement {
					uint32_t T0;
					uint32_t T1;
					uint32_t data[16];
				};

				struct MessageRam {
					StandardFilterElement standardFilter[28];
					ExtendedFilterElement extendedFilter[8];
					RxFifoElement rxFifo0[3];
					RxFifoElement rxFifo1[3];
					TxEventFifoElement txEventFifo[3];
					TxBufferElement txBuffer[3];
				};

			private:
				FDCAN_GlobalTypeDef * const _can;
				uint8_t * const _ram;
				State _state;
				NotificationEventRaiser _erNotification;

			private:
				inline void activate() {
					activateImpl();
				}

				inline void deactivate() {
					deactivateImpl();
				}

				void notifyRxFifoNotEmpty(RxFifoSelection fifo, bool irq);
				void notifyTxCompleted(bool irq);

			protected:
				CANDevice(FDCAN_GlobalTypeDef *can, uint8_t *ram);

				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;

				void interruptService();

			private:
				unsigned getTxBufferFreeLevel() const;
				TxBufferElement* getTxBufferAddr(unsigned index) const;
				unsigned getTxBufferPutIndex() const;

				unsigned getRxFifoFillLevel(RxFifoSelection fifo) const;
				RxFifoElement* getRxFifoAddr(RxFifoSelection selection, unsigned index) const;
				unsigned getRxFifoGetIndex(RxFifoSelection) const;

				StandardFilterElement* getStandardFilterAddr(unsigned index) const;
				ExtendedFilterElement* getExtendedFilterAddr(unsigned index) const;

				void copyToTxBuffer(const TxHeader *header, const uint8_t *data, unsigned index);
				void copyFromRxFifo(RxFifoSelection fifo, RxHeader *header, uint8_t *data, unsigned dataSize, unsigned index);

			public:
				eos::Result initialize(InitParams const * const params);
				eos::Result deinitialize();

				eos::Result start();
				eos::Result start_IRQ();
				eos::Result stop();

				void clearFilters();
				void setMaxFilters(unsigned maxStdFilters, unsigned maxExtFilters);
				eos::Result setFilter(Filter *filter, unsigned index);
				eos::Result setGlobalFilter(NonMatchingFrames nonMatchingStd, NonMatchingFrames nonMatchingExt, RejectRemoteFrames rejectRemoteStd, RejectRemoteFrames rejectRemoteExt);

				eos::Result addTxMessage(const TxHeader *header, const uint8_t *data);
				eos::Result getRxMessage(RxFifoSelection fifo, RxHeader *header, uint8_t *data, unsigned dataSize);
				eos::Result getTxEvent();

				inline bool isRxFifoEmpty(RxFifoSelection fifo) const {
					return getRxFifoFillLevel(fifo) == 0;
				}

				inline bool isRxFifoNotEmpty(RxFifoSelection fifo) const {
					return getRxFifoFillLevel(fifo) != 0;
				}

				inline bool isTxBufferFull() const {
					return getTxBufferFreeLevel() == 0;
				}

				inline bool isTxBufferNotFull() const {
					return getTxBufferFreeLevel() != 0;
				}

				State getState() const {
					return _state;
				}

				inline void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
					_erNotification.set(event, enabled);
				}
				inline void enableNotificationEvent() {
					_erNotification.enable();
				}
				inline void disableNotificationEvent() {
					_erNotification.disable();
				}

		};

		template <DeviceID deviceID_>
		class CANDeviceX final: public CANDevice {
			private:
				using CANTraits = internal::CANTraits<deviceID_>;
				template <PinFunction pinFunction_, gpio::PortID portID_, gpio::PinID pinID_> using CANPins = internal::PinFunctionInfo<deviceID_, pinFunction_, portID_, pinID_>;

			private:
				static constexpr auto _canAddr = CANTraits::canAddr;
				static constexpr auto _ramAddr = CANTraits::ramAddr;
				static constexpr auto _activateAddr = CANTraits::activateAddr;
				static constexpr auto _activatePos = CANTraits::activatePos;
				static constexpr auto _clockSourceAddr = CANTraits::clockSourceAddr;
				static constexpr auto _clockSourcePos = CANTraits::clockSourcePos;
				static constexpr auto _clockSourceMsk = CANTraits::clockSourceMsk;
				static CANDeviceX _instance;

			public:
				static constexpr auto deviceID = deviceID_;
				static constexpr CANDeviceX *pInst = &_instance;
				static constexpr CANDeviceX &rInst = _instance;

			private:
				CANDeviceX() :
					CANDevice {reinterpret_cast<FDCAN_GlobalTypeDef*>(_canAddr), reinterpret_cast<uint8_t*>(_ramAddr)} {
				}

			protected:
				void activateImpl() override {
					bits::set(*reinterpret_cast<uint32_t *>(_activateAddr), 1UL << _activatePos);
					__DSB();
				}

				void deactivateImpl() override {
					bits::clear(*reinterpret_cast<uint32_t *>(_activateAddr),  1UL << _activatePos);
					__DSB();
				}

			public:
				template <typename pin_>
				void initPinTX() {
					auto af = CANPins<PinFunction::tx, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}

				template <typename pin_>
				void initPinRX() {
					auto af = CANPins<PinFunction::rx, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternate(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}

				void initClockSource(ClockSource clockSource) {
					uint32_t *p = reinterpret_cast<uint32_t *>(_clockSourceAddr);
					*p &= ~_clockSourceMsk;
					*p |= ((uint32_t)clockSource << _clockSourcePos) & _clockSourceMsk;
				}

#if HTL_FDCAN_OPTION_IRQ == 1
				inline static void interruptHandler() {
					_instance.interruptService();
				}
#endif
		};

		template <DeviceID deviceID_>
		CANDeviceX<deviceID_> CANDeviceX<deviceID_>::_instance;

		using CANDevice1 = CANDeviceX<DeviceID::can1>;
		using CANDevice2 = CANDeviceX<DeviceID::can2>;
	}
}


#if defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/htlCAN_Traits.h"
    #include "htl/STM32/G0/G0B1/htlCAN_Pins.h"
#endif


#endif // defined(HTL_CANx_EXIST)


#endif // __STM32_htlCAN_H
