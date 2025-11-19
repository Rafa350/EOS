#include "eos.h"
#include "Services/CanOpen/eosCanOpenSDOServer.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"
#include "Services/CanOpen/eosCanOpenProtocols.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    dictionary: Diccionary
///
CanOpenSDOServer::CanOpenSDOServer(
	CanOpenDictionary *dictionary):

	_dictionary {dictionary},
	_state {State::idle} {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa SDO
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::process(
	const uint8_t *query,
	uint8_t *response) {

	// Initiate SDO download (Expedited)
	//
	if ((query[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP))
		processInitiateDownloadExpedited(query, response);

	// Initiate SDO download (Normal)
	//
	else if ((query[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_SEG))
		processInitiateDownloadNormal(query, response);

	// Download segment
	//
	else if ((query[0] & SDO0::CCS_Msk) == SDO0::CCS_DNSEG)
		processDownloadSegment(query, response);

	// Initiate SDO upload
	//
	else if ((query[0] & SDO0::CCS_Msk) == SDO0::CCS_UP)
		processInitiateUpload(query, response);

	// Upload segment
	//
	else if ((query[0] & SDO0::CCS_Msk) == SDO0::CCS_UPSEG)
		processUploadSegment(query, response);

	// Error SDO malformat
	//
	else {
		unsigned errorCode = SdoError::commandSpecifierNotValid;
		response[0] = SDO0::CCS_ABORT;
		response[1] = query[1];
		response[2] = query[2];
		response[3] = query[3];
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un download directe
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::processInitiateDownloadExpedited(
	const uint8_t *query,
	uint8_t *response) {

	uint32_t errorCode = SdoError::none;

	uint16_t index = query[1] | (query[2] << 8);
	uint8_t subIndex = query[3];

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1) {

		uint8_t size = 4 - ((query[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
		uint32_t value = query[4];
		if (size > 1)
			value |= query[5] << 8;
		if (size > 2)
			value |= query[6] << 16;
		if (size > 3)
			value |= query[7] << 24;

		if (!_dictionary->write(entryId, value))
			errorCode = SdoError::attemptToWriteReadOnlyObject;
	}
	else
		errorCode = SdoError::objectDoesNotExistInDictionary;

	response[1] = query[1];
	response[2] = query[2];
	response[3] = query[3];
	if (errorCode == SdoError::none) {
		response[0] = SDO0::SCS_DL;
		response[4] = 0;
		response[5] = 0;
		response[6] = 0;
		response[7] = 0;
	}
	else {
		response[0] = SDO0::CCS_ABORT;
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un download standard
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::processInitiateDownloadNormal(
	const uint8_t *query,
	uint8_t *response) {

	uint32_t errorCode = SdoError::none;

	uint16_t index = query[1] | (query[2] << 8);
	uint8_t subIndex = query[3];

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1) {

		_state = State::downloading;
		_maxCount = query[4] | (query[5] << 8) | (query[6] << 16) | (query[7] << 24);
		_count = 0;
		_toggle = false;
	}
	else
		errorCode = SdoError::objectDoesNotExistInDictionary;

	response[1] = query[1];
	response[2] = query[2];
	response[3] = query[3];
	if (errorCode == SdoError::none) {
		response[0] = SDO0::SCS_DL;
		response[4] = 0;
		response[5] = 0;
		response[6] = 0;
		response[7] = 0;
	}
	else {
		response[0] = SDO0::CCS_ABORT;
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un download d'un segment
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::processDownloadSegment(
	const uint8_t *query,
	uint8_t *response) {
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un download
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::processInitiateUpload(
	const uint8_t *query,
	uint8_t *response) {

	uint32_t errorCode = SdoError::none;

	uint16_t index = query[1] | (query[2] << 8);
	uint8_t subIndex = query[3];

	unsigned value;
	unsigned length;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1) {
		if (_dictionary->canRead(entryId)) {
			_dictionary->read(entryId, value);
			length = _dictionary->getDataLength(entryId);
		}
		else
			errorCode = SdoError::attemptToWriteReadOnlyObject;
	}
	else
		errorCode = SdoError::objectDoesNotExistInDictionary;

	response[1] = query[1];
	response[2] = query[2];
	response[3] = query[3];
	if (errorCode == SdoError::none) {
		if (length <= 4) {
			response[0] = SDO0::SCS_UL | SDO0::E_EXP | SDO0::S_SIZE | (((4 - length) << SDO0::SIZE_Pos) & SDO0::SIZE_Msk);
			response[4] = value & 0xFF;
			response[5] = (value >> 8) & 0xFF;
			response[6] = (value >> 16) & 0xFF;
			response[7] = (value >> 24) & 0xFF;
		}
	}
	else {
		response[0] = SDO0::CCS_ABORT;
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un download d'un segment
/// \param    query: La consulta
/// \param    response: La resposta
///
void CanOpenSDOServer::processUploadSegment(
	const uint8_t *query,
	uint8_t *response) {
}
