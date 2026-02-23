#include "eos.h"
#include "Services/CanOpen/eos_canopen_dictionary.h"
#include "Services/CanOpen/eos_canopen_sdoserver.h"
#include "Services/CanOPen/eos_canopen_protocols.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SDOServer::SDOServer(
	CanOpenDictionary *dictionary):

	_dictionary {dictionary} {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la trama rebuda.
/// \param    request: La sol·licitut.
/// \param    response: La resposta.
///
void SDOServer::processFrame(
	const uint8_t *request,
	uint8_t *response) {

	// Expedited download
	//
	if ((request[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP))
		download(request, response);

	// Initiate download
	//
	else if ((request[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_SEG))
		downloadStart(request, response);

	// Download segment
	//
	else if ((request[0] & SDO0::CCS_Msk) == SDO0::CCS_DNSEG)
		downloadSegment(request, response);

	// Expedited upload
	//
	else if ((request[0] & SDO0::CCS_Msk) == SDO0::CCS_UP)
		upload(request, response);

	// Upload segment
	//
	else if ((request[0] & SDO0::CCS_Msk) == SDO0::CCS_UPSEG)
		uploadSegment(request, response);

	// Error SDO
	//
	else {
		uint32_t errorCode = SdoError::commandSpecifierNotValid;
		response[0] = SDO0::CCS_ABORT;
		response[1] = request[1];
		response[2] = request[2];
		response[3] = request[3];
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}
}


/// -----------------------------------------------------------------------
/// \brief    Descarrega de dades en forma expeditiva.
/// \param    request: La sol·licitut.
/// \param    response: La resposta.
///
void SDOServer::download(
	const uint8_t *request,
	uint8_t *response) {

	uint32_t errorCode = SdoError::none;

	uint16_t index = request[1] | (request[2] << 8);
	uint8_t subIndex = request[3];

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId == (unsigned) -1)
		errorCode = SdoError::objectDoesNotExistInDictionary;

	else {
		if (!_dictionary->canWrite(entryId))
			errorCode = SdoError::attemptToWriteReadOnlyObject;

		else {
			uint8_t size = 4 - ((request[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
			CoType type = _dictionary->getType(entryId);
			switch (type) {
				case CoType::unsigned8: {
					if (size == sizeof(uint8_t)) {
						uint8_t value = request[4];
						raiseWriteU8RequestEvent(index, subIndex, value);
					}
					else
						errorCode = SdoError::dataTypeDoesNotMatch;
					break;
				}

				case CoType::unsigned16: {
					if (size == sizeof(uint16_t)) {
						uint16_t value = (request[4] << 8) | (request[5] << 16);
						raiseWriteU16RequestEvent(index, subIndex, value);
					}
					else
						errorCode = SdoError::dataTypeDoesNotMatch;
					break;
				}

				case CoType::unsigned32: {
					if (size == sizeof(uint32_t)) {
						uint32_t value = request[4] | (request[5] << 8) | (request[6] << 16) | (request[7] << 24);
						raiseWriteU32RequestEvent(index, subIndex, value);
					}
					else
						errorCode = SdoError::dataTypeDoesNotMatch;
					break;
				}

				default:
					errorCode = SdoError::dataTypeDoesNotMatch;
					break;
			}
		}
	}

	// Prepara la resposta
	//
	response[1] = request[1];
	response[2] = request[2];
	response[3] = request[3];
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
/// \brief    Inicia una descarrega de dades segmentada.
/// \param    request: La sol·licitut.
/// \param    response: La resposta.
///
void SDOServer::downloadStart(
	const uint8_t *request,
	uint8_t *response) {

}


/// ----------------------------------------------------------------------
/// \brief    Descarrega un segment de dades.
/// \param    request: La sol·licitut.
/// \param    response: La resposta.
///
void SDOServer::downloadSegment(
	const uint8_t *request,
	uint8_t *response) {

}


/// ----------------------------------------------------------------------
/// \brief    Llegeix una entrada del diccionari de forma expeditiva.
/// \param    request: La sol·licitut.
/// \param    response: La resposta.
///
void SDOServer::upload(
	const uint8_t *request,
	uint8_t *response) {

	uint32_t errorCode = SdoError::none;

	uint16_t index = request[1] | (request[2] << 8);
	uint8_t subIndex = request[3];
	unsigned length = 0;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId == (unsigned) -1)
		errorCode = SdoError::objectDoesNotExistInDictionary;
	else {
		if (!_dictionary->canRead(entryId))
			errorCode = SdoError::attemptToWriteReadOnlyObject;
		else {
			CoType type = _dictionary->getType(entryId);
			switch (type) {
				case CoType::unsigned8: {
					uint8_t value;
					_dictionary->readU8(entryId, value);
					response[4] = value;
					break;
				}

				case CoType::unsigned16: {
					uint16_t value;
					_dictionary->readU16(entryId, value);
					response[4] = value & 0xFF;
					response[5] = (value >> 8) & 0xFF;
					break;
				}

				case CoType::unsigned32: {
					uint32_t value;
					_dictionary->readU32(entryId, value);
					response[4] = value & 0xFF;
					response[5] = (value >> 8) & 0xFF;
					response[6] = (value >> 16) & 0xFF;
					response[7] = (value >> 24) & 0xFF;
					break;
				}

				default:
					errorCode = SdoError::dataTypeDoesNotMatch;
					break;
			}
		}
	}

	if (errorCode == SdoError::none) {

		// Comprova la longitut per seleccionar el tipus de transmissio
		//
		if (length <= 4) {

			// Expedited
			//
			response[0] = SDO0::SCS_UL | SDO0::E_EXP | SDO0::S_SIZE | (((4 - length) << SDO0::SIZE_Pos) & SDO0::SIZE_Msk);
		}
		else {

			// Segmented
			//
			response[0] = SDO0::SCS_UL | SDO0::E_SEG | SDO0::S_SIZE;
			response[4] = length & 0xFF;
			response[5] = (length >> 8) & 0xFF;
			response[6] = (length >> 16) & 0xFF;
			response[7] = (length >> 24) & 0xFF;
		}
	}
}


void SDOServer::uploadSegment(
	const uint8_t *request,
	uint8_t *response) {

}

