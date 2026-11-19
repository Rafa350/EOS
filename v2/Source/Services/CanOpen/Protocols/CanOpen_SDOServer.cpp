export module Eos.Services.CanOpen.SDOServer;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Dictionary;
import Eos.Services.CanOpen.Protocol;
import Eos.Services.CanOpen.SDOCommon;
import Eos.Result;
import Eos.Types;


export namespace eos {

    class SDOServer final: private NonCopyableClass {
        public:
            struct TransmitFrameEventArgs {
                CobID cobId;
                const UInt8 *frame;
                UInt32 frameSize;
            };
    		using TransmitFrameEventRaiser = EventRaiser<SDOServer, TransmitFrameEventArgs>;
			using ITransmitFrameEvent = TransmitFrameEventRaiser::IEvent;
			template <typename Instance_> using TransmitFrameEvent = TransmitFrameEventRaiser::Event<Instance_>;

            struct WriteRequestEventArgs {
                UInt16 index;
                UInt8 subIndex;
                UInt32 offset;
                const UInt8 *data;
                UInt32 dataSize;
            };
    		using WriteRequestEventRaiser = EventRaiser<SDOServer, WriteRequestEventArgs>;
			using IWriteRequestEvent = WriteRequestEventRaiser::IEvent;
			template <typename Instance_> using WriteRequestEvent = WriteRequestEventRaiser::Event<Instance_>;

        private:
            enum class State {
                stop,
                wait,
                downloadSegment,
                downloadBlock,
                uploadSegment,
                uploadBlock
            };

        private:
            State _state;
            CanOpenDictionary * const _dictionary;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;
            WriteRequestEventRaiser _writeRequestEventRaiser;

        private:
            void transmitFrame(CobID cobId, const UInt8 *frame, UInt32 frameSize);
            void writeRequest(UInt16 index, UInt8 subIndex, UInt32 offset, const UInt8 *data, UInt32 dataSize);

            bool downloadExpedited(const UInt8 *frame, UInt32 frameSize);
            bool downloadInitiate(const UInt8 *frame, UInt32 frameSize);
            bool downloadSegment(const UInt8 *frame, UInt32 frameSize);

        public:
            SDOServer(CanOpenDictionary *dictionary, ITransmitFrameEvent &transmitFrameEvent, IWriteRequestEvent &writeRequestEvent);

            bool start();
            bool stop();

            bool processClientRequest(const UInt8 *frame, UInt32 frameSize);
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @param    transmitFrameEvent: transmitFrameEvent 'TransmitFrame'
/// @param    writeRequestEvent: writeRequestEvent 'WriteRequest'
///
SDOServer::SDOServer(
    CanOpenDictionary *dictionary,
    ITransmitFrameEvent &transmitFrameEvent,
    IWriteRequestEvent &writeRequestEvent):

    _state {State::stop},
    _dictionary {dictionary} {

    _transmitFrameEventRaiser.enable(transmitFrameEvent);
    _writeRequestEventRaiser.enable(writeRequestEvent);
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el servidor
/// @return   True si tot es correcte.
///
bool SDOServer::start() {

    if (_state == State::stop)
        _state = State::wait;

    return _state == State::wait;
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el servidor
/// @return   True si tot es correcte.
///
bool SDOServer::stop() {

    if (_state == State::wait)
        _state = State::stop;

    return _state == State::stop;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les solicituts del client SDO.
/// @param    frame: La trams.
/// @param    frameSize: Tamany de la trama en bytes.
/// @return   True si tot es correcte.
///
bool SDOServer::processClientRequest(
    const UInt8 *frame,
    UInt32 frameSize) {

    if (_state != State::stop) {
        switch (frame[0] & SDO0::CCS_Msk) {
            case SDO0::CCS_DN:
                if ((frame[0] & SDO0::E_Msk) == SDO0::E_EXP)
                    return downloadExpedited(frame, frameSize);
                else
                    return downloadInitiate(frame, frameSize);

            case SDO0::CCS_DNSEG:
                return downloadSegment(frame, frameSize);
        }
    }

    return false;
}


bool SDOServer::downloadExpedited(
    const UInt8 *frame,
    UInt32 frameSize) {

    SdoError errorCode;

    UInt16 index = frame[1] | (frame[2] << 8);
    UInt8 subIndex = frame[3];
    UInt8 dataSize = 4 - ((frame[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);

    writeRequest(index, subIndex, 0, &frame[4], dataSize);

    UInt8 response[8];
    response[1] = frame[1];
    response[2] = frame[2];
    response[3] = frame[3];
    if (errorCode == SdoError::none) {
        response[0] = SDO0::SCS_DN;
        response[4] = 0;
        response[5] = 0;
        response[6] = 0;
        response[7] = 0;
    }
    else {
        auto ec = (UInt32) errorCode;
		response[0] = SDO0::CCS_ABORT;
		response[4] = ec& 0xFF;
		response[5] = (ec >> 8) & 0xFF;
		response[6] = (ec >> 16) & 0xFF;
		response[7] = (ec >> 24) & 0xFF;
    }

	UInt32 nodeId;
	if (!_dictionary->readU32(0x1200, 0x02, nodeId))
        return false;

    transmitFrame(CobID::makeSDOr(nodeId), response, sizeof(response));

    return true;
}


bool SDOServer::downloadInitiate(
    const UInt8 *frame,
    UInt32 frameSize) {

    if ((frame[0] & SDO0::E_Msk) == SDO0::E_EXP) {

    }

    return true;
}


bool SDOServer::downloadSegment(
    const UInt8 *frame,
    UInt32 frameSize) {

    return true;
}


/// ---------------------------------------------------------------------------
/// @brief    Solicita l'escriptura en el diccionari
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex.
/// @param    offset: Offset
/// @param    data: Les dades.
/// @param    dataSize: Tamany de les dades en bytes.
///
void SDOServer::writeRequest(
    UInt16 index,
    UInt8 subIndex,
    UInt32 offset,
    const UInt8 *data,
    UInt32 dataSize) {

    WriteRequestEventArgs args = {
        .index {index},
        .subIndex {subIndex},
        .offset {offset},
        .data {data},
        .dataSize {dataSize}
    };

    _writeRequestEventRaiser(this, &args);
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama.
/// @param    cobId: El COBID.
/// @param    frame: Les dades.
/// @param    frameSize: El tamany de les dades en bytes.
///
void SDOServer::transmitFrame(
    CobID cobId,
    const UInt8 *frame,
    UInt32 frameSize) {

    TransmitFrameEventArgs args = {
        .cobId {cobId},
        .frame {frame},
        .frameSize {frameSize}
    };

    _transmitFrameEventRaiser(this, &args);
}
