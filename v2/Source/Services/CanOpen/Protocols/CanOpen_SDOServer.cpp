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

            enum class WriteRequestResult {
                unknown,
                validated,
                written,
                error
            };
            struct WriteRequestEventArgs {
                UInt16 index;
                UInt8 subIndex;
                UInt32 offset;
                const UInt8 *data;
                UInt32 dataSize;
                WriteRequestResult result;
            };
    		using WriteRequestEventRaiser = EventRaiser<SDOServer, WriteRequestEventArgs>;
			using IWriteRequestEvent = WriteRequestEventRaiser::IEvent;
			template <typename Instance_> using WriteRequestEvent = WriteRequestEventRaiser::Event<Instance_>;

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
            CobID _rxCobId;
            CobID _txCobId;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;
            WriteRequestEventRaiser _writeRequestEventRaiser;

        private:
            void transmitFrame(CobID cobId, const UInt8 *frame, UInt32 frameSize);
            WriteRequestResult writeRequest(UInt16 index, UInt8 subIndex, UInt32 offset, const UInt8 *data, UInt32 dataSize);

            bool downloadInitiate(const SdoDownloadInitiateRequest *request);
            bool downloadSegment(const SdoDownloadSegmentRequest *request);

        public:
            SDOServer(CanOpenDictionary *dictionary);

            void enableTransmitFrameEvent(ITransmitFrameEvent &event) {
                _transmitFrameEventRaiser.enable(event);
            }

            void enableWriteRequestEvent(IWriteRequestEvent &event) {
                _writeRequestEventRaiser.enable(event);
            }

            bool start(CobID rxCobId, CobID txCobId);
            bool stop();
            State getState() const { return _state; }

            bool canProcessClientRequest(CobID cobId) const;
            bool processClientRequest(const SdoFrame *frame);
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @param    dictionat: El diccionari CanOpen
///
SDOServer::SDOServer(
    CanOpenDictionary *dictionary):

    _state {State::stop},
    _dictionary {dictionary} {
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el servidor
/// @param    rxCobId: El COBID Client --> Server
/// @param    txCobId: el COBID Server --> Client
/// @return   True si tot es correcte.
///
bool SDOServer::start(
    CobID rxCobId,
    CobID txCobId) {

    if (_state == State::stop) {
        _state = State::wait;
        _rxCobId = rxCobId;
        _txCobId = txCobId;
    }

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
/// @brief    Comprova si pot procesar una solicitut d'un client SDO
/// @param    cobId: El DOBID
/// @return   Trus si es posible.
///
bool SDOServer::canProcessClientRequest(
    CobID cobId) const {

    return (cobId == _rxCobId) && (_state != State::stop);
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

    // Comprova que la entrada existeixi
    //
    auto entryId = _dictionary->find(request->index, request->subIndex);
    if (entryId == CanOpenDictionary::invalidEntryId)
        errorCode = SdoError::objectDoesNotExistInDictionary;

    else {
        // Comprova que el tamany de dades conincideixi
        //
        auto dataSize = 4 - request->unusedBytes;
        auto entryType = _dictionary->getType(entryId);
        if (((entryType == CoType::u8) && (dataSize != sizeof(UInt8))) ||
            ((entryType == CoType::u16) && (dataSize != sizeof(UInt16))) ||
            ((entryType == CoType::u32) && (dataSize != sizeof(UInt32))))
            errorCode = SdoError::dataTypeDoesNotMatch;

        else {

            // Expedited download.
            //
            if (request->expedited) {

                auto result = writeRequest(
                    request->index,
                    request->subIndex,
                    0,
                    request->data,
                    dataSize);

                if (result == WriteRequestResult::error)
                    errorCode = SdoError::generalError;
            }

            // Segmented download.
            //
            else {

            }
        }
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
        response.reserved[0] = ec& 0xFF;
        response.reserved[1] = (ec >> 8) & 0xFF;
        response.reserved[2] = (ec >> 16) & 0xFF;
        response.reserved[3] = (ec >> 24) & 0xFF;
    }

    UInt32 cobid;
    if (!_dictionary->readU32(0x1200, 0x02, cobid))
        return false;

    transmitFrame(
        _txCobId,
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
SDOServer::WriteRequestResult SDOServer::writeRequest(
    UInt16 index,
    UInt8 subIndex,
    UInt32 offset,
    const UInt8 *data,
    UInt32 dataSize) {

    if (_writeRequestEventRaiser) {
        WriteRequestEventArgs args = {
            .index {index},
            .subIndex {subIndex},
            .offset {offset},
            .data {data},
            .dataSize {dataSize},
            .result {WriteRequestResult::unknown}
        };
        _writeRequestEventRaiser(this, &args);

        return args.result;
    }

    return WriteRequestResult::unknown;
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

    if (_transmitFrameEventRaiser) {
        TransmitFrameEventArgs args = {
            .cobId {cobId},
            .frame {frame},
            .frameSize {frameSize}
        };
        _transmitFrameEventRaiser(this, &args);
    }
}
