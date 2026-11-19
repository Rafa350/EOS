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

            bool downloadInitiate(const SdoDownloadInitiateRequest *request);
            bool downloadSegment(const SdoDownloadSegmentRequest *request);

        public:
            SDOServer(CanOpenDictionary *dictionary, ITransmitFrameEvent &transmitFrameEvent, IWriteRequestEvent &writeRequestEvent);

            bool start();
            bool stop();

            bool processClientRequest(const SdoFrame *frame);
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
    const SdoFrame *frame) {

    if (_state != State::stop) {
        switch (frame->requestHeader.ccs) {
            case SdoCCS::initiateDownload:
                return downloadInitiate(&frame->downloadInitiateRequest);

            case SdoCCS::downloadSegment:
                return downloadSegment(&frame->downloadSegmentRequest);
        }
    }

    return false;
}


bool SDOServer::downloadInitiate(
    const SdoDownloadInitiateRequest *request) {

    auto errorCode = SdoError::none;

    // Expedited download.
    //
    if (request->expedited) {

        writeRequest(
            request->index,
            request->subIndex,
            0,
            request->data,
            4 - request->unusedBytes);

    }

    // Segmented download.
    //
    else {

    }

    SdoDownloadInitiateResponse response;
    response.index = request->index;
    response.subIndex = request->subIndex;
    if (errorCode == SdoError::none) {
        response.scs = SdoSCS::initiateDownload;
        response.reserved[0] = 0;
        response.reserved[1] = 0;
        response.reserved[2] = 0;
        response.reserved[3] = 0;
    }
    else {
        auto ec = (UInt32) errorCode;
        response.scs = SdoSCS::abort;
        response.reserved[4] = ec& 0xFF;
        response.reserved[5] = (ec >> 8) & 0xFF;
        response.reserved[6] = (ec >> 16) & 0xFF;
        response.reserved[7] = (ec >> 24) & 0xFF;
    }

    UInt32 nodeId;
    if (!_dictionary->readU32(0x1200, 0x02, nodeId))
        return false;

    transmitFrame(
        CobID::makeSDOr(nodeId),
        reinterpret_cast<const UInt8*>(&response),
        sizeof(response));

    return true;
}


bool SDOServer::downloadSegment(
    const SdoDownloadSegmentRequest *request) {

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
