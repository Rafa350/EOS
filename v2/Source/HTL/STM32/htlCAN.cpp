#include "HTL/htl.h"


#ifdef HTL_CANx_EXIST


#include "HTL/htlAtomic.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htlCAN.h"
#include "System/eosMath.h"


using namespace htl::bits;
using namespace htl::can;


constexpr unsigned absoluteMaxStandardFilters = 28;
constexpr unsigned absoluteMaxExtendedFilters = 8;


// Standard message filter element
//
struct SF {
	static constexpr uint32_t SFT_Pos = 30;
	static constexpr uint32_t SFT_Msk = 0b11 << SFT_Pos;

	static constexpr uint32_t SFEC_Pos = 27;
	static constexpr uint32_t SFEC_Msk = 0b111 << SFEC_Pos;

	static constexpr uint32_t SFID1_Pos = 16;
	static constexpr uint32_t SFID1_Msk = 0x7FF << SFID1_Pos;

	static constexpr uint32_t SFID2_Pos = 0;
	static constexpr uint32_t SFID2_Msk = 0x7FF << SFID2_Pos;
};


// Extended message filter element
//
struct EF0 {
	static constexpr uint32_t EFEC_Pos = 29;
	static constexpr uint32_t EFEC_Msk = 0b111 << EFEC_Pos;

	static constexpr uint32_t EFID1_Pos = 0;
	static constexpr uint32_t EFID1_Msk = 0x1FFFFFFF << EFID1_Pos;
};

struct EF1 {
	static constexpr uint32_t EFT_Pos = 30;
	static constexpr uint32_t EFT_Msk = 0b11 << EFT_Pos;

	static constexpr uint32_t EFID2_Pos = 0;
	static constexpr uint32_t EFID2_Msk = 0x1FFFFFFF << EFID2_Pos;
};


// Tx buffer element
//
struct T0 {
	static constexpr uint32_t ESI_Pos = 31;
	static constexpr uint32_t ESI_Msk = 0b1 << ESI_Pos;

	static constexpr uint32_t XTD_Pos = 30;
	static constexpr uint32_t XTD_Msk = 0b1 << XTD_Pos;

	static constexpr uint32_t RTR_Pos = 29;
	static constexpr uint32_t RTR_Msk = 0b1 << RTR_Pos;

	static constexpr uint32_t SID_Pos = 18;
	static constexpr uint32_t SID_Msk = 0x7FF << SID_Pos;

	static constexpr uint32_t EID_Pos = 0;
	static constexpr uint32_t EID_Msk = 0x1FFFFFFF << EID_Pos;
};

struct T1 {
	static constexpr uint32_t MM_Pos = 24;
	static constexpr uint32_t MM_Msk = 0xFF << MM_Pos;

	static constexpr uint32_t EFC_Pos = 23;
	static constexpr uint32_t EFC_Msk = 0b1 << EFC_Pos;

	static constexpr uint32_t FDF_Pos = 21;
	static constexpr uint32_t FDF_Msk = 0b1 << FDF_Pos;

	static constexpr uint32_t BRS_Pos = 20;
	static constexpr uint32_t BRS_Msk = 0b1 << BRS_Pos;

	static constexpr uint32_t DLC_Pos = 16;
	static constexpr uint32_t DLC_Msk = 0b1111 << DLC_Pos;
};


// RX Fifo element
//
struct R0 {
	static constexpr uint32_t ESI_Pos = 31;
	static constexpr uint32_t ESI_Msk = 0b1 << ESI_Pos;

	static constexpr uint32_t XTD_Pos = 30;
	static constexpr uint32_t XTD_Msk = 0b1 << XTD_Pos;

	static constexpr uint32_t RTR_Pos = 29;
	static constexpr uint32_t RTR_Msk = 0b1 << RTR_Pos;

	static constexpr uint32_t SID_Pos = 18;
	static constexpr uint32_t SID_Msk = 0x7FF << SID_Pos;

	static constexpr uint32_t EID_Pos = 0;
	static constexpr uint32_t EID_Msk = 0x1FFFFFFF << EID_Pos;
};

struct R1 {
	static constexpr uint32_t ANMF_Pos = 31;
	static constexpr uint32_t ANMF_Msk = 0b1 << ANMF_Pos;

	static constexpr uint32_t FIDX_Pos = 24;
	static constexpr uint32_t FIDX_Msk = 0x7F << FIDX_Pos;

	static constexpr uint32_t FDF_Pos = 21;
	static constexpr uint32_t FDF_Msk = 0b1 << FDF_Pos;

	static constexpr uint32_t BRS_Pos = 20;
	static constexpr uint32_t BRS_Msk = 0b1 << BRS_Pos;

	static constexpr uint32_t DLC_Pos = 16;
	static constexpr uint32_t DLC_Msk = 0b1111 << DLC_Pos;

	static constexpr uint32_t RXTS_Pos = 0;
	static constexpr uint32_t RXTS_Msk = 0xFFFF << RXTS_Pos;
};


static const uint8_t __dataLengthTbl[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 12, 16, 20, 24, 32, 48, 64
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    can: Registres de hardware del dispositiu.
/// \param    ram: Ram de comunicacio del FDCAN
///
CANDevice::CANDevice(
	FDCAN_GlobalTypeDef *can,
	uint8_t *ram) :

	_can {can},
	_ram {ram},
	_state {State::reset} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    params: Parametres d'inicialitzacio.
///
eos::Result CANDevice::initialize(
	CANDevice::InitParams const * const params) {

	if (_state == State::reset) {

		activate();

		// Surt del modus sleep
		//
		clear(_can->CCCR, FDCAN_CCCR_CSR);
		while (isSet(_can->CCCR, FDCAN_CCCR_CSR))
			continue;

		// Selecciona modus INIT i espera que acabi
		//
		set(_can->CCCR, FDCAN_CCCR_INIT);
		while (!isSet(_can->CCCR, FDCAN_CCCR_INIT)) {
		}

		// Habilita el canvi de configuracio
		//
		set(_can->CCCR, FDCAN_CCCR_CCE);

		// Configura el registre del divisor del rellotge
		//
		if (_can == FDCAN1)
			FDCAN_CONFIG->CKDIV = (unsigned) params->clockDivider;

		// Configura el registre CCCR
		//
		auto CCCR = _can->CCCR;

		clear(CCCR, FDCAN_CCCR_DAR | FDCAN_CCCR_TXP | FDCAN_CCCR_PXHD |
			FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM |
			FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE);

		if (!params->autoRetransmission)
			set(CCCR, FDCAN_CCCR_DAR);

		if (params->transmitPause)
			set(CCCR, FDCAN_CCCR_TXP);

		if (!params->protocolException)
			set(CCCR, FDCAN_CCCR_PXHD);

		switch (params->frameFormat) {
			case FrameFormat::classic:
				break;

			case FrameFormat::fdNoBsr:
				set(CCCR, FDCAN_CCCR_FDOE);
				break;

			case FrameFormat::fdBsr:
				set(CCCR, FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE);
				break;
		}

		switch (params->mode) {
			case Mode::normal:
				break;

			case Mode::restricted:
			    set(CCCR, FDCAN_CCCR_ASM);
			    break;

			case Mode::internalLoopback:
		    	set(CCCR, FDCAN_CCCR_TEST);
	    		set(CCCR, FDCAN_CCCR_MON);
				break;

			case Mode::externalLoopback:
	    		set(CCCR, FDCAN_CCCR_TEST);
				break;

			case Mode::busMonitoring:
		    	set(CCCR, FDCAN_CCCR_MON);
		    	break;
		}

		_can->CCCR = CCCR;

		// Configura el registre TEST
		// -Modus normal/loopback
		//
		if ((params->mode == Mode::internalLoopback) || (params->mode == Mode::externalLoopback))
	    	set(_can->TEST, FDCAN_TEST_LBCK);
		else
			clear(_can->TEST, FDCAN_TEST_LBCK);

		// Configura el registre NBTP
		//
		_can->NBTP =
			(((uint32_t)params->nominalSyncJumpWidth - 1) << FDCAN_NBTP_NSJW_Pos) |
		    (((uint32_t)params->nominalTimeSeg1 - 1) << FDCAN_NBTP_NTSEG1_Pos) |
		    (((uint32_t)params->nominalTimeSeg2 - 1) << FDCAN_NBTP_NTSEG2_Pos) |
		    (((uint32_t)params->nominalPrescaler - 1) << FDCAN_NBTP_NBRP_Pos);

		// Configura el registre DBTP
		//
		if (params->frameFormat == FrameFormat::fdBsr)
		    _can->DBTP =
		    	(((uint32_t)params->dataSyncJumpWidth - 1) << FDCAN_DBTP_DSJW_Pos) |
		        (((uint32_t)params->dataTimeSeg1 - 1) << FDCAN_DBTP_DTSEG1_Pos) |
		        (((uint32_t)params->dataTimeSeg2 - 1) << FDCAN_DBTP_DTSEG2_Pos) |
		        (((uint32_t)params->dataPrescaler - 1) << FDCAN_DBTP_DBRP_Pos);

		// Configura el registre TXBC
		// -Modus FIFO/QUEUE
		//
		if (params->qfMode == QFMode::queue)
			set(_can->TXBC, FDCAN_TXBC_TFQM);
		else
			clear(_can->TXBC, FDCAN_TXBC_TFQM);

		// Configura el registre RXGFC
		// -Modus sobresciptura del FIFO
		// -Nombre de filtres estandard
		// -Nombre de filtes extesos
		//
		auto RXGFC = _can->RXGFC;
		clear(RXGFC, FDCAN_RXGFC_F0OM | FDCAN_RXGFC_F1OM | FDCAN_RXGFC_LSS | FDCAN_RXGFC_LSE);
		set(RXGFC, (eos::min(params->stdFiltersNbr, absoluteMaxStandardFilters) << FDCAN_RXGFC_LSS_Pos) & FDCAN_RXGFC_LSS_Msk);
		set(RXGFC, (eos::min(params->extFiltersNbr, absoluteMaxExtendedFilters) << FDCAN_RXGFC_LSE_Pos) & FDCAN_RXGFC_LSE_Msk);
		_can->RXGFC = RXGFC;

		// Convenient borrar la ram dels filtres
		//
		clearFilters();

		_state = State::ready;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
eos::Result CANDevice::deinitialize() {

	if (_state == State::ready) {

		stop();
		deactivate();

		_state = State::reset;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la comunicacio.
/// \return   El resultat de l'operacio.
///
eos::Result CANDevice::start() {

	if (_state == State::ready) {

		// Surt del modus INIT
		//
		clear(_can->CCCR, FDCAN_CCCR_INIT);
		while (isSet(_can->CCCR, FDCAN_CCCR_INIT))
			continue;

		_state = State::running;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la comunicacio per interrupcions.
/// \return   El resultat de l'operacio.
///
eos::Result CANDevice::start_IRQ() {

	if (start().isSuccess()) {

		// Habilita interrupcions
		//
		set(_can->IE,
			FDCAN_IE_RF0NE |      // FIFO0 new message
			FDCAN_IE_RF1NE |      // FIFO1 new message
			FDCAN_IE_TCE |        // TxBuffer transmission completed
			FDCAN_IE_TCFE);       // TxBuffer transmission cancelada

		set(_can->ILE,
			FDCAN_ILE_EINT0);     // Linia INT0 habilitada

		return eos::Result::ErrorCodes::success;
	}
	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la comunicacio.
///
eos::Result CANDevice::stop() {

	if (_state == State::running) {

		// Deshabilita les interrupcions
		//
		clear(_can->IE,
			FDCAN_IE_RF0NE |      // FIFO0 new message
			FDCAN_IE_RF1NE |      // FIFO1 new message
			FDCAN_IE_TCE |        // TxBuffer transmission completed
			FDCAN_IE_TCFE);       // TxBuffer transmission cancelada

		clear(_can->ILE,
			FDCAN_ILE_EINT0);     // Linia INT0 deshabilitada

		// Entra al modus INIT
		//
		set(_can->CCCR, FDCAN_CCCR_INIT);
		while (!isSet(_can->CCCR, FDCAN_CCCR_INIT))
			continue;

		// Permet canvis en la configuracio
		//
		set(_can->CCCR, FDCAN_CCCR_CCE);

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Borra tots els filtres
//
void CANDevice::clearFilters() {

	auto pStandardFilter = getStandardFilterAddr(0);
	unsigned maxStandardFilters = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	while (maxStandardFilters-- > 0) {
		pStandardFilter->SF = 0;
		pStandardFilter++;
	}

	auto pExtendedFilter = getExtendedFilterAddr(0);
	unsigned maxExtendedFilters = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	while (maxExtendedFilters-- > 0) {
		pExtendedFilter->EF0 = 0;
		pExtendedFilter->EF1 = 0;
		pExtendedFilter++;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura un filtre
/// \param    filder: Parametres del filtre..
/// \param    index: Index del filtre.
/// \return   El resultat de l'operacio.
///
eos::Result CANDevice::setFilter(
	Filter *filter,
	unsigned index) {

	if (_state == State::ready) {

		// IDs standard 11bits
		//
	    if (filter->idType == IdentifierType::standard) {

	    	uint8_t maxIndex = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	    	if (index >= maxIndex)
	    		return eos::Result::ErrorCodes::error;

	    	uint32_t SF = 0;
	    	set(SF, ((uint32_t)filter->type << SF::SFT_Pos) & SF::SFT_Msk);
	    	set(SF, ((uint32_t)filter->config << SF::SFEC_Pos) & SF::SFEC_Msk);
	    	set(SF, (filter->id1 << SF::SFID1_Pos) & SF::SFID1_Msk);
	    	set(SF, (filter->id2 << SF::SFID2_Pos) & SF::SFID2_Msk);

	    	auto pFilter = getStandardFilterAddr(index);
	    	pFilter->SF = SF;
	    }

	    // ID's extesos 29bits
	    //
	    else {

	    	uint8_t maxIndex = (_can->RXGFC & FDCAN_RXGFC_LSE_Msk) >> FDCAN_RXGFC_LSE_Pos;
	    	if (index >= maxIndex)
	    		return eos::Result::ErrorCodes::error;

	    	uint32_t EF0 = 0;
	    	set(EF0, ((uint32_t) filter->config << EF0::EFEC_Pos) & EF0::EFEC_Msk);
	    	set(EF0, (filter->id1 << EF0::EFID1_Pos) & EF0::EFID1_Msk);

	    	uint32_t EF1 = 0;
	    	set(EF1, ((uint32_t) filter->type << EF1::EFT_Pos) & EF1::EFT_Msk);
	    	set(EF1, (filter->id2 << EF1::EFID2_Pos) & EF1::EFID2_Msk);

	    	auto pFilter = getExtendedFilterAddr(index);
	    	pFilter->EF0 = EF0;
	    	pFilter->EF1 = EF1;
	    }

	    return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Configura els filtres globals.
/// \param    nonMatchingStd:
/// \param    nonMatchingExt:
/// \param    rejectRemoteStd:
/// \param    rejectRemoteExt:
/// \return   El resultat de l'operacio.
///
eos::Result CANDevice::setGlobalFilter(
	NonMatchingFrames nonMatchingStd,
	NonMatchingFrames nonMatchingExt,
	RejectRemoteFrames rejectRemoteStd,
	RejectRemoteFrames rejectRemoteExt) {

	if (_state == State::ready) {

		auto RXGFC = _can->RXGFC;
		clear(RXGFC, FDCAN_RXGFC_ANFS | FDCAN_RXGFC_ANFE | FDCAN_RXGFC_RRFS | FDCAN_RXGFC_RRFE);
		set(RXGFC, ((uint32_t)nonMatchingStd << FDCAN_RXGFC_ANFS_Pos) & FDCAN_RXGFC_ANFS_Msk);
		set(RXGFC, ((uint32_t)nonMatchingExt << FDCAN_RXGFC_ANFE_Pos) & FDCAN_RXGFC_ANFE_Msk);
		set(RXGFC, ((uint32_t)rejectRemoteStd << FDCAN_RXGFC_RRFS_Pos) & FDCAN_RXGFC_RRFS_Msk);
		set(RXGFC, ((uint32_t)rejectRemoteExt << FDCAN_RXGFC_RRFE_Pos) & FDCAN_RXGFC_RRFE_Msk);
		_can->RXGFC = RXGFC;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un missatge al fifo/cua i el transmet.
/// \param    header: Capcelera de transmissio del missatge.
/// \param    data: Bloc de dades del missatge.
/// \\return  El resultat de l'operacio.
///
eos::Result CANDevice::addTxMessage(
	const TxHeader *header,
	const uint8_t *data) {

	if (_state == State::running) {

		// Comprova que el fifo no estigui ple
		//
		if (isTxBufferFull())
			return eos::Result::ErrorCodes::busy;

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
		while (!isSet(_can->TXBRP, (uint32_t)(1 << index)))
			continue;

		return eos::Result::ErrorCodes::success;
	}

	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta el missatge que esta en proces de transmissio.
///
eos::Result CANDevice::abortTxTransmitingMessage() {

	for (auto index = 0u; index < 3; index++) {

		uint32_t msk = 1 << index;
		if (isSet(_can->TXBRP, msk) && isSet(_can->TXBTO, msk)) {

			_can->TXBCR = msk;

			while (!isSet(_can->TXBCF, msk))
				continue;

			return eos::Result::ErrorCodes::success;
		}
	}

	return eos::Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un missatge del fifo.
/// \param    fifo: El fifo.
/// \param    header: Buffer per la capcelera de recepcio del missatge.
/// \param    data: Buffer per les dades del missatge.
/// \param    dataSize: Tamany del buffer de dades.
/// \return   El resultat de l'operacio.
///
eos::Result CANDevice::getRxMessage(
	RxFifoSelection fifo,
	RxHeader *header,
	uint8_t *data,
	unsigned dataSize) {

	if (_state == State::running) {

		if (isRxFifoNotEmpty(fifo)) {

			unsigned index = getRxFifoGetIndex(fifo);

			copyFromRxFifo(fifo, header, data, dataSize, index);

			if (fifo == RxFifoSelection::fifo0)
				_can->RXF0A = index;
			else
				_can->RXF1A = index;

			return eos::Result::ErrorCodes::success;
		}

		return eos::Result::ErrorCodes::error;
	}
	else
		return eos::Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event de notificacio 'RxFifoNotEmpty'
/// \param    fifl: El fifo.
/// \param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseRxFifoNotEmptyNotification(
	RxFifoSelection fifo,
	bool irq) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::rxFifoNotEmpty},
			.irq {irq},
			.rxFifoNotEmpty {
				.fifo {fifo}
			}
		};
		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event de notificacio 'TxCompleted'
/// \param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseTxCompletedNotification(
	bool irq) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::txCompleted},
			.irq {irq},
			.txCompleted {
			}
		};
		_erNotification(this, &args);
	}
}

/// ----------------------------------------------------------------------
/// \brief    Genera un event de notificacio 'TxCancelled'
/// \param    irq: Indica wqu nla notificacio s'ha produit d'ins d'una interrupcio
///
void CANDevice::raiseTxCancelledNotification(
	bool irq) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::txCancelled},
			.irq {irq},
			.txCancelled {
			}
		};
		_erNotification(this, &args);
	}
}

/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions
///
void CANDevice::interruptService() {

	auto IR = _can->IR & _can->IE; // Obte les intrerrupcions actives i habilitades
	if (IR != 0) {

		// Missatge rebut en RxFIFO0
		//
		if (isSet(IR, FDCAN_IR_RF0N)) {
			set(_can->IR, FDCAN_IR_RF0N);
			raiseRxFifoNotEmptyNotification(RxFifoSelection::fifo0, true);
		}

		// Missatge rebut en RxFIFO1
		//
		if (isSet(IR, FDCAN_IR_RF1N)) {
			set(_can->IR, FDCAN_IR_RF1N);
			raiseRxFifoNotEmptyNotification(RxFifoSelection::fifo1, true);
		}

		// Transmissio del missatge en TxBuffer completada
		//
		if (isSet(IR, FDCAN_IR_TC)) {
			set(_can->IR, FDCAN_IR_TC);
			raiseTxCompletedNotification(true);
		}

		// Transmissio del missatge en TxBuffer cancelada
		//
		if (isSet(IR, FDCAN_IR_TCF)) {
			set(_can->IR, FDCAN_IR_TCF);
			raiseTxCancelledNotification(true);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'index d'insercio del TxFIFO
/// \return   El resultat de l'operacio.
///
unsigned CANDevice::getTxBufferPutIndex() const {

	return (_can->TXFQS & FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_Pos;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'index d'extraccio del RxFIFO.
/// \param    fifo: El fifo.
/// \return   El resultat de l'operacio.
///
unsigned CANDevice::getRxFifoGetIndex(
	RxFifoSelection fifo) const {

	if (fifo == RxFifoSelection::fifo0)
		return (_can->RXF0S & FDCAN_RXF0S_F0GI_Msk) >> FDCAN_RXF0S_F0GI_Pos;
	else
		return (_can->RXF0S & FDCAN_RXF1S_F1GI_Msk) >> FDCAN_RXF1S_F1GI_Pos;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre de elements que es poden retirar de RxFIFO
/// \return   El resultat.
///
unsigned CANDevice::getRxFifoFillLevel(
	RxFifoSelection fifo) const {

	if (fifo == RxFifoSelection::fifo0)
		return (_can->RXF0S & FDCAN_RXF0S_F0FL_Msk) >> FDCAN_RXF0S_F0FL_Pos;
	else
		return (_can->RXF1S & FDCAN_RXF1S_F1FL) >> FDCAN_RXF1S_F1FL_Pos;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el txBuffer (FIFO/QUEUE) es ple.
/// \return   True si es ple.
///
bool CANDevice::isTxBufferFull() const {

	return isSet(_can->TXFQS, FDCAN_TXFQS_TFQF);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el txBuffer (FIFO/QUEUE) es buit.
/// \return   True si es buit.
///
bool CANDevice::isTxBufferEmpty() const {

	return (_can->TXFQS & FDCAN_TXFQS_TFFL_Msk) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el txBuffer (FIFO/QUEUE) no estigui ple.
/// \param    timeout: Tamps maxim d'espera.
/// \return   True si es correcte, false en cas de timeout.
///
bool CANDevice::waitTxBufferNotFull(
	unsigned timeout) {

	auto expireTime = htl::getTick() + timeout;
    while (isTxBufferFull()) {
    	if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Espera fins que el txBuffer (FIFO/QUEUE) estigui buit.
/// \param    timeout: Tamps maxim d'espera.
/// \return   True si es correcte, false en cas de timeout.
///
bool CANDevice::waitTxBufferEmpty(
	unsigned timeout) {

	auto expireTime = htl::getTick() + timeout;

    while (!isTxBufferEmpty()) {
    	if (hasTickExpired(expireTime))
            return false;
    }

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Copia el missatge al TxBuffer
/// \param    header: La capcelera del missatge.
/// \param    data: Les dades del missatge
///
void CANDevice::copyToTxBuffer(
	const TxHeader *header,
	const uint8_t *data,
	unsigned index) {

	// Prepara l'element T0 de la capcelera
	//
	uint32_t T0 = 0;
	if (header->errorStateFlag == ErrorStateFlag::passive)
		set(T0, (1 << T0::ESI_Pos) & T0::ESI_Msk);
	if (header->idType == IdentifierType::extended)
		set(T0, (1 << T0::XTD_Pos) & T0::XTD_Msk);
	if (header->frameType == FrameType::remoteFrame)
		set(T0, (1 << T0::RTR_Pos) & T0::RTR_Msk);
	if (header->idType == IdentifierType::extended)
		set(T0, (header->id << T0::EID_Pos) & T0::EID_Msk);
	else
		set(T0, (header->id << T0::SID_Pos) & T0::SID_Msk);

	// Prepara l'element T1 de la capcelera
	//
	uint32_t T1 = 0;
    set(T1, (uint32_t) (header->messageMarker << T1::MM_Pos) & T1::MM_Msk);
    if (header->txEventFifoControl == TxEventFifoControl::store)
    	set(T1, (1 << T1::EFC_Pos) & T1::EFC_Msk);
    if (header->fdFormat == FDFormat::fdcan)
    	set(T1, (1 << T1::FDF_Pos) & T1::FDF_Msk);
    if (header->bitrateSwitching == BitrateSwitching::on)
    	set(T1, (1 << T1::BRS_Pos) & T1::BRS_Msk);
    set(T1, (uint32_t)((unsigned)header->dataLength << T1::DLC_Pos) & T1::DLC_Msk);

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
			((uint32_t)data[byteCount + 3] << 24) |
            ((uint32_t)data[byteCount + 2] << 16) |
            ((uint32_t)data[byteCount + 1] << 8)  |
             (uint32_t)data[byteCount];

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
	            ((uint32_t)data[byteCount + 1] << 8)  |
	             (uint32_t)data[byteCount];
			break;

		case 3:
			pBuffer->data[wordCount] =
	            ((uint32_t)data[byteCount + 2] << 16) |
	            ((uint32_t)data[byteCount + 1] << 8)  |
	             (uint32_t)data[byteCount];
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Copia el missatge desde el RxFIFO
/// \param    fifo: El fifo.
/// \param    header: Buffer de la capcelera del missatge.
/// \param    data: Buffer de dades del missatge.
/// \param    dataSize: Tamany del buffer de dades en bytes.
/// \param    index: Index del fifo.
///
void CANDevice::copyFromRxFifo(
	RxFifoSelection fifo,
	RxHeader *header,
	uint8_t *data,
	unsigned dataSize,
	unsigned index) {

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
	uint8_t *p = (uint8_t*) pBuffer->data;
	unsigned ii = eos::min(dataSize, (unsigned)__dataLengthTbl[(pBuffer->R1 & R1::DLC_Msk) >> R1::DLC_Pos]);
	for (unsigned i = 0; i < ii; i++)
		data[i] = p[i];
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter a un element del buffer de transmissio.
/// \param    index: Index del element.
/// \return   El resultat.
///
CANDevice::TxBufferElement* CANDevice::getTxBufferAddr(
	unsigned index) const {

	return (TxBufferElement*) ((unsigned)_ram +
		offsetof(MessageRam, txBuffer) +
		sizeof(TxBufferElement) * index);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter a un element del fifo de recepcio
/// \param    fifo: Seleccio del fifo.
/// \param    index: Index del element.
/// \return   El resultat.
///
CANDevice::RxFifoElement* CANDevice::getRxFifoAddr(
	RxFifoSelection fifo,
	unsigned index) const {

	if (fifo == RxFifoSelection::fifo0)
		return (RxFifoElement*) ((unsigned)_ram +
			offsetof(MessageRam, rxFifo0) +
			index * sizeof(RxFifoElement));
	else
		return (RxFifoElement*) ((unsigned)_ram +
			offsetof(MessageRam, rxFifo1) +
			index * sizeof(RxFifoElement));
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter a un filtre.
/// \param    index: Index del filtre.
/// \return   El resultat.
///
CANDevice::StandardFilterElement* CANDevice::getStandardFilterAddr(
	unsigned index) const {

	return (StandardFilterElement*)((unsigned) _ram +
		offsetof(MessageRam, standardFilter) +
		index * sizeof(StandardFilterElement));
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter a un filtre.
/// \param    index: Index del filtre.
/// \return   El resultat.
///
CANDevice::ExtendedFilterElement* CANDevice::getExtendedFilterAddr(
	unsigned index) const {

	return (ExtendedFilterElement*)((unsigned)_ram +
		offsetof(MessageRam, extendedFilter) +
		index * sizeof(ExtendedFilterElement));
}


#endif // defined(HTL_CANx_EXIST)
