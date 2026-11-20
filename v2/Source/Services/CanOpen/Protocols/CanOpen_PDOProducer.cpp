export module Eos.Services.CanOPen.PDOProducer;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Dictionary;
import Eos.Result;
import Eos.Types;


export namespace eos {

    class PDOProducer final: private NonCopyableClass {
        public:
            struct TransmitFrameEventArgs {
                CobID cobId;
                const UInt8 *frame;
                UInt32 frameSize;
            };
    		using TransmitFrameEventRaiser = EventRaiser<PDOProducer, TransmitFrameEventArgs>;
			using ITransmitFrameEvent = TransmitFrameEventRaiser::IEvent;
			template <typename Instance_> using TransmitFrameEvent = TransmitFrameEventRaiser::Event<Instance_>;

            enum class State {
                stop,
                active
            };

		private:
			static constexpr UInt32 maxPdoId = 4;

        private:
            State _state;
            CanOpenDictionary * const _dictionary;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;

        private:
            bool isEntryMapped(UInt8 tpdoId, UInt32 entryId);
            void transmitPDO(UInt8 tpdoId);
            void transmitFrame(CobID cobId, const UInt8* frame, UInt32 frameSize);

        public:
            PDOProducer(CanOpenDictionary *dictionary);

            void enableTransmitFrameEvent(ITransmitFrameEvent &event) {
                _transmitFrameEventRaiser.enable(event);
            }

            bool start();
            bool stop();
			State getState() const { return _state; }

			StdResult processChange(UInt16 index, UInt8 subIndex);
            StdResult processChange(UInt32 entryId);
            StdResult processSync();
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    dictionary: El diccionari
///
PDOProducer::PDOProducer(
    CanOpenDictionary *dictionary):

    _state {State::stop},
    _dictionary {dictionary} {

}


/// ---------------------------------------------------------------------------
/// @brief    Inicia el productor.
/// @return   True si s'ha iniciat correctament.
///
bool PDOProducer::start() {

    if (_state == State::stop)
        _state = State::active;

    return _state == State::active;
}


/// ---------------------------------------------------------------------------
/// @brief    Para el productor.
/// @return   True si s'ha parat correctament.
///
bool PDOProducer::stop() {

    if (_state == State::active)
        _state = State::stop;

    return _state == State::stop;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa el canvi en una entrada del diccionari
/// @param    indec: L'index.
/// @param    subIndex: El subindex.
/// @return   El resultat de l'operacio.
///
StdResult PDOProducer::processChange(
	UInt16 index,
	UInt8 subIndex) {

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId == CanOpenDictionary::invalidEntryId)
		return StdErrorCode::errorParameter;
	else
		return processChange(entryId);
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa el canvi en una entrada del diccionari
/// @param    entryId: Identificador de l'entrada.
/// @return   El resultat de l'operacio.
///
StdResult PDOProducer::processChange(
    UInt32 entryId) {

    if (_state != State::active)
        return StdErrorCode::errorState;

    // Comprova les entrades 0x1800 per si hi ha TPDO asincrones
    //
    for (UInt8 pdoId = 0; pdoId < maxPdoId; pdoId++) {

        // Verifica que la entrada, estigui mapejada en un TPDO
        //
        if (isEntryMapped(pdoId, entryId)) {

            UInt32 flags;
            UInt8 transmissionType;

            if (_dictionary->readU32(0x1800 + pdoId, 0x01, flags) &&
                _dictionary->readU8(0x1800 + pdoId, 0x02, transmissionType)) {

                if ((transmissionType == 254) && ((flags & (1 << 31)) == 0))
                    transmitPDO(pdoId);
            }
        }
    }

    return StdErrorCode::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Procesa un senyal de sincronitzacio
/// @return   El resultat de l'operacio.
///
StdResult PDOProducer::processSync() {

    if (_state != State::active)
        return StdErrorCode::errorState;

    // Comprova les  entrades 0x1800 per si hi han TPDOs sincrons
    // per enviar
    //
    for (UInt8 pdoId = 0; pdoId < maxPdoId; pdoId++) {

        UInt32 flags;
        UInt8 transmissionType;

        if (_dictionary->readU32(0x1800 + pdoId, 0x01, flags) &&
            _dictionary->readU8(0x1800 + pdoId, 0x02, transmissionType)) {

            if ((transmissionType <= 240) && ((flags & (1 << 31)) == 0))
                transmitPDO(pdoId);
        }
    }

    return StdErrorCode::ok;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si una entrada esta mapejada en un TPDO
/// @param    pdoId: El TPDO
/// @param    entryId: El identificador de l'entrada.
/// @return   True si esta mapejada.
///
bool PDOProducer::isEntryMapped(
	UInt8 pdoId,
	UInt32 entryId) {

	UInt8 numMaps;
	if (_dictionary->readU8(0x1A00 + pdoId, 0, numMaps)) {
		for (auto i = 0; i < numMaps; i++) {

			UInt32 map;
			if (_dictionary->readU32(0x1A00 + pdoId, i + 1, map)) {

				UInt16 mapIndex = (map >> 16) & 0xFFFF;
				UInt8 mapSubIndex = (map >> 8) & 0xFF;
				if (entryId == _dictionary->find(mapIndex, mapSubIndex))
					return true;
			}
		}
	}

	return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet un PDO
/// @param    tpdoId: Identificador del TPDO
///
void PDOProducer::transmitPDO(
    UInt8 tpdoId) {

	UInt8 maxCount;
	if (_dictionary->readU8(0x1A00 + tpdoId, 0x00, maxCount) && maxCount > 0) {

		UInt8 frame[8];
		UInt8 *pData = frame;
		UInt8 dataLen = 0;

		// Mapeja els elements un a un
		//
		bool ok = true;
		for (auto count = 0; (count < maxCount) && ok; count++) {

			UInt32 mapInfo;
			ok = _dictionary->readU32(0x1A00 + tpdoId, count + 1, mapInfo);
			if (ok) {

				UInt16 mapIndex = (mapInfo >> 16) & 0xFFFF;
				UInt8 mapSubIndex = (mapInfo >> 8) & 0xFF;
				unsigned mapLength = (mapInfo & 0xFF) / 8;

				auto entryId = _dictionary->find(mapIndex, mapSubIndex);
				ok = entryId != CanOpenDictionary::invalidEntryId;
				if (ok) {
					switch (mapLength) {
						case 1:
							ok = (dataLen + sizeof(UInt8)) < sizeof(frame);
							if (ok) {
								UInt8 value;
								ok = _dictionary->readU8(entryId, value);
								if (ok) {
									*(pData++) = value;
									dataLen += sizeof(UInt8);
								}
							}
							break;

						case 2:
							ok = (dataLen + sizeof(UInt16)) < sizeof(frame);
							if (ok) {
								UInt16 value;
								ok = _dictionary->readU16(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									dataLen += sizeof(UInt16);
								}
							}
							break;

						case 4:
							ok = (dataLen + sizeof(UInt32)) < sizeof(frame);
							if (ok) {
								UInt32 value;
								ok = _dictionary->readU32(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									*(pData++) = (value >> 16) & 0xFF;
									*(pData++) = (value >> 24) & 0xFF;
									dataLen += sizeof(UInt32);
								}
							}
							break;

						default:
							ok = false;
							break;
					}
				}
			}
		}

		if (ok) {
			UInt32 cobid;
			if (_dictionary->readU32(0x1800 + tpdoId, 0x01, cobid))
				transmitFrame(CobID::make(cobid), frame, dataLen);
		}
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama PDO.
/// @param    cobId: El COBID.
/// @param    frame: Les trama a transmetre.
/// @param    frameSize: El tasmanyd e la trama
///
void PDOProducer::transmitFrame(
    CobID cobId,
    const UInt8* frame,
	UInt32 frameSize) {

    if (_transmitFrameEventRaiser) {
        TransmitFrameEventArgs args = {
            .cobId {cobId},
            .frame {reinterpret_cast<const UInt8*>(frame)},
            .frameSize {frameSize}
        };
        _transmitFrameEventRaiser(this, &args);
    }
}
