#include "eos.h"
#include "Services/CanOpen/eos_canopen_tpdo_transmitter.h"
#include "Services/CanOpen/eos_canopen_dictionary.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    dictionary: El diccionari.
///
CanOpenTPDOTransmitter::CanOpenTPDOTransmitter(
	CanOpenDictionary *dictionary):

	_dictionary {dictionary} {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa una peticio.
/// \param    tpdoId: El PDO solicitat.
/// \param    response: Buffer on deixar la resposta.
/// \return   El resultatd e l'operacio.
///
eos::Result CanOpenTPDOTransmitter::process(
	unsigned tpdoId,
	uint8_t *response) {

	unsigned entryId;
	unsigned maxTPDO;

	// Obte el maxim nombre de TPDO's definits
	//
	entryId = _dictionary->find(0x1A00, 0x00);
	if (entryId == (unsigned) -1)
		return eos::Result::ErrorCodes::error;
	if (!_dictionary->read(entryId, maxTPDO))
		return eos::Result::ErrorCodes::error;

	// Comprova la llista si hi han TPDO per enviar
	//
	for (auto tpdoId = 0u; tpdoId < maxTPDO; tpdoId++) {

		// Comprova les entrades 0x1800 0x02
		//
		auto entryId = _dictionary->find(0x1800 | (tpdoId & 0xFF), 0x02);
		if (entryId != (unsigned) -1) {

			// Existeix una entrada pel TPDO.
			//
			uint8_t value;
			if (_dictionary->readU8(entryId, value)) {

				// Comprova si es sincrona, alesores genera un TPDO
				//
				if ((value >= 1) && (value <= 240)) {

					//buildTPDO(tpdoId, response);
				}
			}
		}
	}

	return eos::Result::ErrorCodes::success;
}
