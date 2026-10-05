module;


#include "HTL/htl.h"
#include "eosEvents.h"


export module Eos.Hardware.CAN.__CLASSES;


import Eos.Bits;
import Eos.Hardware.CAN.__INTERNAL;
import Eos.Math;
import Eos.Result;
import Eos.System.Core.Ticks;
import Eos.Types;


export namespace eos::hardware::can {

    enum class ClockSource {
        pclk,
        pllqclk,
        hse
    };

    typedef UInt32 Identifier;

    enum class IdentifierType {
        standard,
        extended
    };

    enum class DataLength {
        len0, len1, len2, len3, len4, len5, len6, len7, len8,
        len12, len16, len20, len24, len32, len48, len64
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
        UInt8 messageMarker;
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

    enum class RxFifoSelection {
        fifo0,
        fifo1
    };

    class CANDevice: private NonCopyableClass {
        public:
            struct InitParams {
                ClockDivider clockDivider;
                FrameFormat frameFormat;
                Mode mode;
                bool autoRetransmission;
                bool transmitPause;
                bool protocolException;
                UInt32 nominalPrescaler;
                UInt32 nominalSyncJumpWidth;
                UInt32 nominalTimeSeg1;
                UInt32 nominalTimeSeg2;
                UInt32 dataPrescaler;
                UInt32 dataSyncJumpWidth;
                UInt32 dataTimeSeg1;
                UInt32 dataTimeSeg2;
                UInt32 stdFiltersNbr;
                UInt32 extFiltersNbr;
                QFMode qfMode;
            };

            enum class NotificationID {
                rxFifoNotEmpty,
                txCompleted,
                txCancelled
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
                    struct {
                    } txCancelled;
                };
            };
            using NotificationEventRaiser = EventRaiser<CANDevice, NotificationEventArgs>;
            using INotificationEvent = NotificationEventRaiser::IEvent;
            template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

        public:
            enum class ErrorCode {
                ok,
                busy,
                timeout,
                error,
                errorParam,
                errorState
            };
            using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;

            enum class State {
                reset,
                ready,
                running
            };

        private:
            struct StandardFilterElement {
                UInt32 SF;
            };

            struct ExtendedFilterElement {
                UInt32 EF0;
                UInt32 EF1;
            };

            struct RxFifoElement {
                UInt32 R0;
                UInt32 R1;
                UInt32 data[16];
            };

            struct TxEventFifoElement {
                UInt32 E0;
                UInt32 E1;
            };

            struct TxBufferElement {
                UInt32 T0;
                UInt32 T1;
                UInt32 data[16];
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
            UInt8 * const _ram;
            State _state;
            NotificationEventRaiser _notificationEventRaiser;

        private:
            inline void activate() { activateImpl(); }
            inline void deactivate() { deactivateImpl(); }

            void raiseRxFifoNotEmptyNotification(RxFifoSelection fifo, bool irq);
            void raiseTxCompletedNotification(bool irq);
            void raiseTxCancelledNotification(bool irq);

        protected:
            CANDevice(UInt32 canAddr, UInt32 ramAddr);

            virtual void activateImpl() = 0;
            virtual void deactivateImpl() = 0;

            void interruptService();

        private:
            TxBufferElement* getTxBufferAddr(UInt32 index) const;
            UInt32 getTxBufferPutIndex() const;

            UInt32 getRxFifoFillLevel(RxFifoSelection fifo) const;
            RxFifoElement* getRxFifoAddr(RxFifoSelection selection, UInt32 index) const;
            UInt32 getRxFifoGetIndex(RxFifoSelection) const;

            StandardFilterElement* getStandardFilter(UInt32 index) const;
            ExtendedFilterElement* getExtendedFilter(UInt32 index) const;

            void copyToTxBuffer(const TxHeader *header, const UInt8 *data, UInt32 index);
            void copyFromRxFifo(RxFifoSelection fifo, RxHeader *header, UInt8 *data, UInt32 dataSize, UInt32 index);

        public:
            virtual ~CANDevice() = default;

            Result initialize(InitParams const * const params);
            Result deinitialize();

            Result start();
            Result start_IRQ();
            Result stop();

            void clearFilters();
            void setMaxFilters(UInt32 maxStdFilters, UInt32 maxExtFilters);
            Result setFilter(Filter *filter, UInt32 index);
            Result setGlobalFilter(NonMatchingFrames nonMatchingStd, NonMatchingFrames nonMatchingExt, RejectRemoteFrames rejectRemoteStd, RejectRemoteFrames rejectRemoteExt);

            Result addTxMessage(const TxHeader *header, const UInt8 *data);
            Result getRxMessage(RxFifoSelection fifo, RxHeader *header, UInt8 *data, UInt32 dataSize);
            Result getTxEvent();

            Result abortTxBufferTransmission();
            Result waitTxBufferNotFull(Ticks timeout);
            Result waitTxBufferEmpty(Ticks timeout);

            inline bool isRxFifoEmpty(RxFifoSelection fifo) const {
                return getRxFifoFillLevel(fifo) == 0;
            }

            inline bool isRxFifoNotEmpty(RxFifoSelection fifo) const {
                return getRxFifoFillLevel(fifo) != 0;
            }

            bool isTxBufferFull() const;
            bool isTxBufferEmpty() const;

            State getState() const {
                return _state;
            }

            inline void enableNotificationEvent(INotificationEvent &event) {
                _notificationEventRaiser.enable(event);
            }
            inline void disableNotificationEvent() {
                _notificationEventRaiser.disable();
            }
    };
}

using namespace eos;
using namespace eos::hardware::can;
using namespace eos::hardware::can::internal;


constexpr UInt8 __dataLengthTbl[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 12, 16, 20, 24, 32, 48, 64
};


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    can: Registres de hardware del dispositiu.
/// @param    ram: Ram de comunicacio del FDCAN
///
CANDevice::CANDevice(
	UInt32 canAddr,
	UInt32 ramAddr) :

	_can {reinterpret_cast<FDCAN_GlobalTypeDef*>(canAddr)},
	_ram {reinterpret_cast<UInt8*>(ramAddr)},
	_state {State::reset} {

}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza el dispositiu.
/// @param    params: Parametres d'inicialitzacio.
///
CANDevice::Result CANDevice::initialize(
	CANDevice::InitParams const * const params) {

	if (_state == State::reset) {

		activate();

		// Surt del modus sleep
		//
		Bits::clear(_can->CCCR, FDCAN_CCCR_CSR);
		while (Bits::isSet(_can->CCCR, FDCAN_CCCR_CSR))
			continue;

		// Selecciona modus INIT i espera que acabi
		//
		Bits::set(_can->CCCR, FDCAN_CCCR_INIT);
		while (!Bits::isSet(_can->CCCR, FDCAN_CCCR_INIT))
			continue;

		// Habilita el canvi de configuracio
		//
		Bits::set(_can->CCCR, FDCAN_CCCR_CCE);

		// Configura el registre del divisor del rellotge
		//
		if (_can == FDCAN1)
			FDCAN_CONFIG->CKDIV = (UInt32) params->clockDivider;

		// Configura el registre CCCR
		//
		auto CCCR = _can->CCCR;

		Bits::clear(CCCR, FDCAN_CCCR_DAR | FDCAN_CCCR_TXP | FDCAN_CCCR_PXHD |
			FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM |
			FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE);

		if (!params->autoRetransmission)
			Bits::set(CCCR, FDCAN_CCCR_DAR);

		if (params->transmitPause)
			Bits::set(CCCR, FDCAN_CCCR_TXP);

		if (!params->protocolException)
			Bits::set(CCCR, FDCAN_CCCR_PXHD);

		switch (params->frameFormat) {
			case FrameFormat::classic:
				break;

			case FrameFormat::fdNoBsr:
				Bits::set(CCCR, FDCAN_CCCR_FDOE);
				break;

			case FrameFormat::fdBsr:
				Bits::set(CCCR, FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE);
				break;
		}

		switch (params->mode) {
			case Mode::normal:
				break;

			case Mode::restricted:
				Bits::set(CCCR, FDCAN_CCCR_ASM);
			    break;

			case Mode::internalLoopback:
				Bits::set(CCCR, FDCAN_CCCR_TEST);
				Bits::set(CCCR, FDCAN_CCCR_MON);
				break;

			case Mode::externalLoopback:
				Bits::set(CCCR, FDCAN_CCCR_TEST);
				break;

			case Mode::busMonitoring:
				Bits::set(CCCR, FDCAN_CCCR_MON);
		    	break;
		}

		_can->CCCR = CCCR;

		// Configura el registre TEST
		// -Modus normal/loopback
		//
		if ((params->mode == Mode::internalLoopback) || (params->mode == Mode::externalLoopback))
			Bits::set(_can->TEST, FDCAN_TEST_LBCK);
		else
			Bits::clear(_can->TEST, FDCAN_TEST_LBCK);

		// Configura el registre NBTP
		//
		_can->NBTP =
			(((UInt32)params->nominalSyncJumpWidth - 1) << FDCAN_NBTP_NSJW_Pos) |
		    (((UInt32)params->nominalTimeSeg1 - 1) << FDCAN_NBTP_NTSEG1_Pos) |
		    (((UInt32)params->nominalTimeSeg2 - 1) << FDCAN_NBTP_NTSEG2_Pos) |
		    (((UInt32)params->nominalPrescaler - 1) << FDCAN_NBTP_NBRP_Pos);

		// Configura el registre DBTP
		//
		if (params->frameFormat == FrameFormat::fdBsr)
		    _can->DBTP =
		    	(((UInt32)params->dataSyncJumpWidth - 1) << FDCAN_DBTP_DSJW_Pos) |
		        (((UInt32)params->dataTimeSeg1 - 1) << FDCAN_DBTP_DTSEG1_Pos) |
		        (((UInt32)params->dataTimeSeg2 - 1) << FDCAN_DBTP_DTSEG2_Pos) |
		        (((UInt32)params->dataPrescaler - 1) << FDCAN_DBTP_DBRP_Pos);

		// Configura el registre TXBC
		// -Modus FIFO/QUEUE
		//
		if (params->qfMode == QFMode::queue)
			Bits::set(_can->TXBC, FDCAN_TXBC_TFQM);
		else
			Bits::clear(_can->TXBC, FDCAN_TXBC_TFQM);

		// Configura el registre RXGFC
		// -Modus sobresciptura del FIFO
		// -Nombre de filtres estandard
		// -Nombre de filtes extesos
		//
		auto RXGFC = _can->RXGFC;
		Bits::clear(RXGFC, FDCAN_RXGFC_F0OM | FDCAN_RXGFC_F1OM | FDCAN_RXGFC_LSS | FDCAN_RXGFC_LSE);
		Bits::set(RXGFC, (Math::min(params->stdFiltersNbr, absoluteMaxStandardFilters) << FDCAN_RXGFC_LSS_Pos) & FDCAN_RXGFC_LSS_Msk);
		Bits::set(RXGFC, (Math::min(params->extFiltersNbr, absoluteMaxExtendedFilters) << FDCAN_RXGFC_LSE_Pos) & FDCAN_RXGFC_LSE_Msk);
		_can->RXGFC = RXGFC;

		// Convenient borrar la ram dels filtres
		//
		clearFilters();

		_state = State::ready;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Desinicialitza el dispositiu.
///
CANDevice::Result CANDevice::deinitialize() {

	if (_state == State::ready) {

		stop();
		deactivate();

		_state = State::reset;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia la comunicacio.
/// \return   El resultat de l'operacio.
///
CANDevice::Result CANDevice::start() {

	if (_state == State::ready) {

		// Surt del modus INIT
		//
		Bits::clear(_can->CCCR, FDCAN_CCCR_INIT);
		while (Bits::isSet(_can->CCCR, FDCAN_CCCR_INIT))
			continue;

		_state = State::running;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Inicia la comunicacio per interrupcions.
/// \return   El resultat de l'operacio.
///
CANDevice::Result CANDevice::start_IRQ() {

	if (start().isOk()) {

		// Habilita interrupcions
		//
		Bits::set(_can->IE,
			FDCAN_IE_RF0NE |      // FIFO0 new message
			FDCAN_IE_RF1NE |      // FIFO1 new message
			FDCAN_IE_TCE |        // TxBuffer transmission completed
			FDCAN_IE_TCFE);       // TxBuffer transmission cancelada

		Bits::set(_can->ILE,
			FDCAN_ILE_EINT0);     // Linia INT0 habilitada

		return ErrorCode::ok;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Finalitza la comunicacio.
///
CANDevice::Result CANDevice::stop() {

	if (_state == State::running) {

		// Deshabilita les interrupcions
		//
		Bits::clear(_can->IE,
			FDCAN_IE_RF0NE |      // FIFO0 new message
			FDCAN_IE_RF1NE |      // FIFO1 new message
			FDCAN_IE_TCE |        // TxBuffer transmission completed
			FDCAN_IE_TCFE);       // TxBuffer transmission cancelada

		Bits::clear(_can->ILE,
			FDCAN_ILE_EINT0);     // Linia INT0 deshabilitada

		// Entra al modus INIT
		//
		Bits::set(_can->CCCR, FDCAN_CCCR_INIT);
		while (!Bits::isSet(_can->CCCR, FDCAN_CCCR_INIT))
			continue;

		// Permet canvis en la configuracio
		//
		Bits::set(_can->CCCR, FDCAN_CCCR_CCE);

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Afegeix un missatge al fifo/cua i el transmet.
/// @param    header: Capcelera de transmissio del missatge.
/// @param    data: Bloc de dades del missatge.
/// \\return  El resultat de l'operacio.
///
CANDevice::Result CANDevice::addTxMessage(
	const TxHeader *header,
	const UInt8 *data) {

	if (_state == State::running) {

		// Comprova que el fifo no estigui ple
		//
		if (isTxBufferFull())
			return ErrorCode::busy;

		// Obte el index d'insercio del FIFO
		//
		auto index = getTxBufferPutIndex();

		// Copia el missatge al FIFO
		//
		copyToTxBuffer(header, data, index);

		// Activa la transmissio del missatge afeigit
		//
		_can->TXBAR = 1 << index;

		// Espera que es faci efectiva l'operacio
		//
		while (!Bits::isSet(_can->TXBRP, (UInt32)(1 << index)))
			continue;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Obte un missatge del fifo.
/// @param    fifo: El fifo.
/// @param    header: Buffer per la capcelera de recepcio del missatge.
/// @param    data: Buffer per les dades del missatge.
/// @param    dataSize: Tamany del buffer de dades.
/// \return   El resultat de l'operacio.
///
CANDevice::Result CANDevice::getRxMessage(
	RxFifoSelection fifo,
	RxHeader *header,
	UInt8 *data,
	UInt32 dataSize) {

	if (_state == State::running) {

		if (isRxFifoNotEmpty(fifo)) {

			unsigned index = getRxFifoGetIndex(fifo);

			copyFromRxFifo(fifo, header, data, dataSize, index);

			if (fifo == RxFifoSelection::fifo0)
				_can->RXF0A = index;
			else
				_can->RXF1A = index;

			return ErrorCode::ok;
		}

		return ErrorCode::error;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'RxFifoNotEmpty'
/// @param    fifl: El fifo.
/// @param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseRxFifoNotEmptyNotification(
	RxFifoSelection fifo,
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id {NotificationID::rxFifoNotEmpty},
			.irq {irq},
			.rxFifoNotEmpty {
				.fifo {fifo}
			}
		};
		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'TxCompleted'
/// @param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseTxCompletedNotification(
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id {NotificationID::txCompleted},
			.irq {irq},
			.txCompleted {
			}
		};
		_notificationEventRaiser(this, &args);
	}
}

/// ----------------------------------------------------------------------
/// @brief    Genera un event de notificacio 'TxCancelled'
/// @param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseTxCancelledNotification(
	bool irq) {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id {NotificationID::txCancelled},
			.irq {irq},
			.txCancelled {
			}
		};
		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Aborta el missatge que esta en proces de transmissio.
///
CANDevice::Result CANDevice::abortTxBufferTransmission() {

	// Busca el buffer que esta transmetent
	//
	for (auto index = 0u; index < 3; index++) {

		UInt32 msk = 1 << index;
		if (Bits::isSet(_can->TXBRP, msk) && !Bits::isSet(_can->TXBTO, msk)) {

			// Cancela la transmissio
			//
			_can->TXBCR = msk;

			// Espera que es faci efectiva
			//
			while (!eos::Bits::isSet(_can->TXBCF, msk))
				continue;

			return ErrorCode::ok;
		}
	}

	return ErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les interrupcions
///
void CANDevice::interruptService() {

	auto IR = _can->IR & _can->IE; // Obte les interrupcions actives i habilitades
	if (IR != 0) {

		// Missatge rebut en RxFIFO0
		//
		if (eos::Bits::isSet(IR, FDCAN_IR_RF0N)) {
			eos::Bits::set(_can->IR, FDCAN_IR_RF0N);
			raiseRxFifoNotEmptyNotification(RxFifoSelection::fifo0, true);
		}

		// Missatge rebut en RxFIFO1
		//
		if (eos::Bits::isSet(IR, FDCAN_IR_RF1N)) {
			eos::Bits::set(_can->IR, FDCAN_IR_RF1N);
			raiseRxFifoNotEmptyNotification(RxFifoSelection::fifo1, true);
		}

		// Transmissio del missatge en TxBuffer completada
		//
		if (eos::Bits::isSet(IR, FDCAN_IR_TC)) {
			eos::Bits::set(_can->IR, FDCAN_IR_TC);
			raiseTxCompletedNotification(true);
		}

		// Transmissio del missatge en TxBuffer cancelada
		//
		if (eos::Bits::isSet(IR, FDCAN_IR_TCF)) {
			eos::Bits::set(_can->IR, FDCAN_IR_TCF);
			raiseTxCancelledNotification(true);
		}
	}
}


/// ----------------------------------------------------------------------
/// @brief    Obte l'index d'insercio del TxFIFO
/// \return   El resultat de l'operacio.
///
UInt32 CANDevice::getTxBufferPutIndex() const {

	return (_can->TXFQS & FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_Pos;
}


/// ----------------------------------------------------------------------
/// @brief    Obte l'index d'extraccio del RxFIFO.
/// @param    fifo: El fifo.
/// \return   El resultat de l'operacio.
///
UInt32 CANDevice::getRxFifoGetIndex(
	RxFifoSelection fifo) const {

	if (fifo == RxFifoSelection::fifo0)
		return (_can->RXF0S & FDCAN_RXF0S_F0GI_Msk) >> FDCAN_RXF0S_F0GI_Pos;
	else
		return (_can->RXF0S & FDCAN_RXF1S_F1GI_Msk) >> FDCAN_RXF1S_F1GI_Pos;
}


/// ----------------------------------------------------------------------
/// @brief    Obte el nombre de elements que es poden retirar de RxFIFO
/// \return   El resultat.
///
UInt32 CANDevice::getRxFifoFillLevel(
	RxFifoSelection fifo) const {

	if (fifo == RxFifoSelection::fifo0)
		return (_can->RXF0S & FDCAN_RXF0S_F0FL_Msk) >> FDCAN_RXF0S_F0FL_Pos;
	else
		return (_can->RXF1S & FDCAN_RXF1S_F1FL) >> FDCAN_RXF1S_F1FL_Pos;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si el txBuffer (FIFO/QUEUE) es ple.
/// \return   True si es ple.
///
bool CANDevice::isTxBufferFull() const {

	// Llegeix el bit TFQF, que ha de set 1
	//
	return eos::Bits::isSet(_can->TXFQS, FDCAN_TXFQS_TFQF);
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si el txBuffer (FIFO/QUEUE) es buit.
/// \return   True si es buit.
///
bool CANDevice::isTxBufferEmpty() const {

	// Esta buit quant el nombre d'elements lliures es 3
	//
	return (_can->TXFQS & FDCAN_TXFQS_TFFL_Msk) == 3;
}


/// ----------------------------------------------------------------------
/// @brief    Espera fins que el txBuffer (FIFO/QUEUE) no estigui ple.
/// @param    timeout: Tamps maxim d'espera.
/// \return   True si es correcte, false en cas de timeout.
///
CANDevice::Result CANDevice::waitTxBufferNotFull(
	Ticks blockTime) {

	if (blockTime.isInfinite()) {
		while (isTxBufferFull())
			continue;
	}
	else {
		auto expirationTime = Ticks::now() + blockTime;
		while (isTxBufferFull()) {
			if (expirationTime.hasExpiredNow())
				return ErrorCode::timeout;
		}
	}
    return ErrorCode::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Espera fins que el txBuffer (FIFO/QUEUE) estigui buit.
/// @param    timeout: Tamps maxim d'espera.
/// \return   True si es correcte, false en cas de timeout.
///
CANDevice::Result CANDevice::waitTxBufferEmpty(
	Ticks blockTime) {

	if (blockTime.isInfinite()) {
		while (!isTxBufferEmpty())
			continue;
	}
	else {
		auto expirationTime = Ticks::now() + blockTime;
		while (!isTxBufferEmpty()) {
			if (expirationTime.hasExpiredNow())
				return ErrorCode::timeout;
		}
	}

    return ErrorCode::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Copia el missatge al TxBuffer
/// @param    header: La capcelera del missatge.
/// @param    data: Les dades del missatge
///
void CANDevice::copyToTxBuffer(
	const TxHeader *header,
	const UInt8 *data,
	UInt32 index) {

	// Prepara l'element T0 de la capcelera
	//
	UInt32 T0 = 0;
	if (header->errorStateFlag == ErrorStateFlag::passive)
		Bits::set(T0, (1 << T0::ESI_Pos) & T0::ESI_Msk);
	if (header->idType == IdentifierType::extended)
		Bits::set(T0, (1 << T0::XTD_Pos) & T0::XTD_Msk);
	if (header->frameType == FrameType::remoteFrame)
		Bits::set(T0, (1 << T0::RTR_Pos) & T0::RTR_Msk);
	if (header->idType == IdentifierType::extended)
		Bits::set(T0, (header->id << T0::EID_Pos) & T0::EID_Msk);
	else
		Bits::set(T0, (header->id << T0::SID_Pos) & T0::SID_Msk);

	// Prepara l'element T1 de la capcelera
	//
	UInt32 T1 = 0;
	Bits::set(T1, (UInt32) (header->messageMarker << T1::MM_Pos) & T1::MM_Msk);
    if (header->txEventFifoControl == TxEventFifoControl::store)
    	Bits::set(T1, (1 << T1::EFC_Pos) & T1::EFC_Msk);
    if (header->fdFormat == FDFormat::fdcan)
    	Bits::set(T1, (1 << T1::FDF_Pos) & T1::FDF_Msk);
    if (header->bitrateSwitching == BitrateSwitching::on)
    	Bits::set(T1, (1 << T1::BRS_Pos) & T1::BRS_Msk);
    Bits::set(T1, (UInt32)((unsigned)header->dataLength << T1::DLC_Pos) & T1::DLC_Msk);

    // Escriu la capcelera en el buffer
    //
	auto pBuffer = getTxBufferAddr(index);
	pBuffer->T0 = T0;
	pBuffer->T1 = T1;

	// Escriu les dades en el buffer. Nomes permet escriptura en modus 32bits.
	//
	unsigned bytesRemain = __dataLengthTbl[(unsigned)header->dataLength];
	unsigned wordCount = 0;
	unsigned byteCount = 0;

	while (bytesRemain >= 4) {

		pBuffer->data[wordCount] =
			((UInt32)data[byteCount + 3] << 24) |
            ((UInt32)data[byteCount + 2] << 16) |
            ((UInt32)data[byteCount + 1] << 8)  |
             (UInt32)data[byteCount];

		byteCount += 4;
		wordCount += 1;

		bytesRemain -= 4;
	}
	switch (bytesRemain) {
		case 1:
			pBuffer->data[wordCount] = data[byteCount];
			break;

		case 2:
			pBuffer->data[wordCount] =
	            ((UInt32)data[byteCount + 1] << 8)  |
	             (UInt32)data[byteCount];
			break;

		case 3:
			pBuffer->data[wordCount] =
	            ((UInt32)data[byteCount + 2] << 16) |
	            ((UInt32)data[byteCount + 1] << 8)  |
	             (UInt32)data[byteCount];
			break;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Copia el missatge desde el RxFIFO
/// @param    fifo: El fifo.
/// @param    header: Buffer de la capcelera del missatge.
/// @param    data: Buffer de dades del missatge.
/// @param    dataSize: Tamany del buffer de dades en bytes.
/// @param    index: Index del fifo.
///
void CANDevice::copyFromRxFifo(
	RxFifoSelection fifo,
	RxHeader *header,
	UInt8 *data,
	UInt32 dataSize,
	UInt32 index) {

	auto *pBuffer = getRxFifoAddr(fifo, index);

	// Obte la capcelera
	//
	header->idType = ((pBuffer->R0 & R0::XTD_Msk) >> R0::XTD_Pos) == 0 ? IdentifierType::standard : IdentifierType::extended;
	if (header->idType == IdentifierType::extended)
		header->id = (pBuffer->R0 & R0::EID_Msk) >> R0::EID_Pos;
	else
		header->id = (pBuffer->R0 & R0::SID_Msk) >> R0::SID_Pos;
	header->errorStateFlag = ((pBuffer->R0 & R0::ESI_Msk) >> R0::ESI_Pos) == 0 ? ErrorStateFlag::active : ErrorStateFlag::passive;
	header->frameType = ((pBuffer->R0 & R0::RTR_Msk) >> R0::RTR_Pos) == 0 ? FrameType::dataFrame : FrameType::remoteFrame;
	header->filterIndex = (pBuffer->R1 & R1::FIDX_Msk) >> R1::FIDX_Pos;
	header->dataLength = (DataLength) ((pBuffer->R1 & R1::DLC_Msk) >> R1::DLC_Pos);
	header->bitrateSwitching = ((pBuffer->R1 & R1::BRS_Msk) >> R1::BRS_Pos) == 0 ? BitrateSwitching::off : BitrateSwitching::on;
	header->fdFormat = ((pBuffer->R1 & R1::FDF_Msk) >> R1::FDF_Pos) == 0 ? FDFormat::can : FDFormat::fdcan;

	// Obte les dades. Les lectures en mode 32bits son mes eficients.
	//
	UInt8 *p = (UInt8*) pBuffer->data;
	UInt32 ii = Math::min(dataSize, (UInt32)__dataLengthTbl[(pBuffer->R1 & R1::DLC_Msk) >> R1::DLC_Pos]);
	for (UInt32 i = 0; i < ii; i++)
		data[i] = p[i];
}


/// ----------------------------------------------------------------------
/// @brief    Obte el punter a un element del buffer de transmissio.
/// @param    index: Index del element.
/// \return   El resultat.
///
CANDevice::TxBufferElement* CANDevice::getTxBufferAddr(
	UInt32 index) const {

	return (TxBufferElement*) ((UInt32)_ram +
		offsetof(MessageRam, txBuffer) +
		sizeof(TxBufferElement) * index);
}


/// ----------------------------------------------------------------------
/// @brief    Obte el punter a un element del fifo de recepcio
/// @param    fifo: Seleccio del fifo.
/// @param    index: Index del element.
/// \return   El resultat.
///
CANDevice::RxFifoElement* CANDevice::getRxFifoAddr(
	RxFifoSelection fifo,
	UInt32 index) const {

	if (fifo == RxFifoSelection::fifo0)
		return (RxFifoElement*) ((UInt32)_ram +
			offsetof(MessageRam, rxFifo0) +
			index * sizeof(RxFifoElement));
	else
		return (RxFifoElement*) ((UInt32)_ram +
			offsetof(MessageRam, rxFifo1) +
			index * sizeof(RxFifoElement));
}
