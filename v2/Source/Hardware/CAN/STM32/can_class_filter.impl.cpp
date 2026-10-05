module;


#include "HTL/htl.h"


module Eos.Hardware.CAN;


import Eos.Bits;
import Eos.Hardware.CAN.__INTERNAL;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::can;
using namespace eos::hardware::can::internal;


/// ---------------------------------------------------------------------------
/// @brief    Borra tots els filtres
//
void CANDevice::clearFilters() {

	auto pStandardFilter = getStandardFilter(0);
	auto maxStandardFilters = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	while (maxStandardFilters-- > 0) {
		pStandardFilter->SF = 0;
		pStandardFilter++;
	}

	auto pExtendedFilter = getExtendedFilter(0);
	auto maxExtendedFilters = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	while (maxExtendedFilters-- > 0) {
		pExtendedFilter->EF0 = 0;
		pExtendedFilter->EF1 = 0;
		pExtendedFilter++;
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Configura un filtre
/// @param    filder: Parametres del filtre..
/// @param    index: Index del filtre.
/// \return   El resultat de l'operacio.
///
CANDevice::Result CANDevice::setFilter(
	Filter *filter,
	UInt32 index) {

	if (_state == State::ready) {

		// IDs standard 11bits
		//
	    if (filter->idType == IdentifierType::standard) {

	    	UInt8 maxIndex = (_can->RXGFC & FDCAN_RXGFC_LSS_Msk) >> FDCAN_RXGFC_LSS_Pos;
	    	if (index >= maxIndex)
	    		return ErrorCode::error;

	    	UInt32 SF = 0;
	    	Bits::set(SF, ((UInt32)filter->type << SF::SFT_Pos) & SF::SFT_Msk);
	    	Bits::set(SF, ((UInt32)filter->config << SF::SFEC_Pos) & SF::SFEC_Msk);
	    	Bits::set(SF, (filter->id1 << SF::SFID1_Pos) & SF::SFID1_Msk);
	    	Bits::set(SF, (filter->id2 << SF::SFID2_Pos) & SF::SFID2_Msk);

	    	auto pFilter = getStandardFilter(index);
	    	pFilter->SF = SF;
	    }

	    // ID's extesos 29bits
	    //
	    else {

	    	UInt8 maxIndex = (_can->RXGFC & FDCAN_RXGFC_LSE_Msk) >> FDCAN_RXGFC_LSE_Pos;
	    	if (index >= maxIndex)
	    		return ErrorCode::error;

	    	UInt32 EF0 = 0;
	    	Bits::set(EF0, ((UInt32) filter->config << EF0::EFEC_Pos) & EF0::EFEC_Msk);
	    	Bits::set(EF0, (filter->id1 << EF0::EFID1_Pos) & EF0::EFID1_Msk);

	    	UInt32 EF1 = 0;
	    	Bits::set(EF1, ((UInt32) filter->type << EF1::EFT_Pos) & EF1::EFT_Msk);
	    	Bits::set(EF1, (filter->id2 << EF1::EFID2_Pos) & EF1::EFID2_Msk);

	    	auto pFilter = getExtendedFilter(index);
	    	pFilter->EF0 = EF0;
	    	pFilter->EF1 = EF1;
	    }

	    return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// ---------------------------------------------------------------------------
/// @brief    Configura els filtres globals.
/// @param    nonMatchingStd:
/// @param    nonMatchingExt:
/// @param    rejectRemoteStd:
/// @param    rejectRemoteExt:
/// \return   El resultat de l'operacio.
///
CANDevice::Result CANDevice::setGlobalFilter(
	NonMatchingFrames nonMatchingStd,
	NonMatchingFrames nonMatchingExt,
	RejectRemoteFrames rejectRemoteStd,
	RejectRemoteFrames rejectRemoteExt) {

	if (_state == State::ready) {

		auto RXGFC = _can->RXGFC;
		Bits::clear(RXGFC, FDCAN_RXGFC_ANFS | FDCAN_RXGFC_ANFE | FDCAN_RXGFC_RRFS | FDCAN_RXGFC_RRFE);
		Bits::clear(RXGFC, FDCAN_RXGFC_F0OM | FDCAN_RXGFC_F1OM);
		Bits::set(RXGFC, ((UInt32)nonMatchingStd << FDCAN_RXGFC_ANFS_Pos) & FDCAN_RXGFC_ANFS_Msk);
		Bits::set(RXGFC, ((UInt32)nonMatchingExt << FDCAN_RXGFC_ANFE_Pos) & FDCAN_RXGFC_ANFE_Msk);
		Bits::set(RXGFC, ((UInt32)rejectRemoteStd << FDCAN_RXGFC_RRFS_Pos) & FDCAN_RXGFC_RRFS_Msk);
		Bits::set(RXGFC, ((UInt32)rejectRemoteExt << FDCAN_RXGFC_RRFE_Pos) & FDCAN_RXGFC_RRFE_Msk);
		_can->RXGFC = RXGFC;

		return ErrorCode::ok;
	}

	else
		return ErrorCode::errorState;
}


/// --------------------------------------------------------------------------------
/// @brief    Obte el punter a un filtre.
/// @param    index: Index del filtre.
/// \return   El resultat.
///
CANDevice::StandardFilterElement* CANDevice::getStandardFilter(
	UInt32 index) const {

	return (StandardFilterElement*)((UInt32) _ram +
		offsetof(MessageRam, standardFilter) +
		index * sizeof(StandardFilterElement));
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el punter a un filtre.
/// @param    index: Index del filtre.
/// \return   El resultat.
///
CANDevice::ExtendedFilterElement* CANDevice::getExtendedFilter(
	UInt32 index) const {

	return (ExtendedFilterElement*)((UInt32)_ram +
		offsetof(MessageRam, extendedFilter) +
		index * sizeof(ExtendedFilterElement));
}
