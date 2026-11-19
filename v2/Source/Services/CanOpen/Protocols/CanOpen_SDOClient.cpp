module;

#include <cstring>


export module Eos.Services.CanOpen.SDOClient;

import Eos.Events;
import Eos.Concepts;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Protocol;
import Eos.Services.CanOpen.SDOCommon;
import Eos.Result;
import Eos.Types;


export namespace eos {

    enum class SDOClientErrorCode {
        ok,
        error,
        errorParameter
    };
    using SDOClientResult = ComplexResult<SdoError, SDOClientErrorCode, SDOClientErrorCode::ok>;


    class SDOClient final: private NonCopyableClass {
        public:
            struct TransmitFrameEventArgs {
                CobID cobId;
                const UInt8 *frame;
                UInt32 frameSize;
            };
    		using TransmitFrameEventRaiser = EventRaiser<SDOClient, TransmitFrameEventArgs>;
			using ITransmitFrameEvent = TransmitFrameEventRaiser::IEvent;
			template <typename Instance_> using TransmitFrameEvent = TransmitFrameEventRaiser::Event<Instance_>;

        private:
            enum class State {
                idle,
                uploadExpedited,
                uploadSegment,
                uploadBlock,
                downloadExpedited,
                downloadSegment,
                downloadBlock
            };

        private:
            State _state;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;

            NodeID _serverId;
            bool _toggle;
            const UInt8 *_ptr;
            const UInt8 *_ptrEnd;

        private:
            void transmitFrame(CobID cobId, const UInt8 *frame, UInt32 frameSize);

            SDOClientResult downloadExpeditedResponse(const SdoDownloadInitiateResponse *frame);
            void downloadNextSegmentResponse();
            void downloadNextBlockResponse();
            void uploadExpeditedResponse();
            void uploadNextSegmentResponse();
            void uploadNextBlockResponse();

        public:
            SDOClient(ITransmitFrameEvent &event);

            template <typename T_>
            requires (sizeof(T_) >= 1 && sizeof(T_) <= 4)
                StdResult download(NodeID serverId, UInt16 index, UInt8 subIndex, T_ data);
            StdResult download(NodeID serverId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult upload(NodeID serverId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult abort(SdoError errorCode);

            SDOClientResult processServerResponse(const UInt8 *frame, UInt32 frameSize);
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Contructor.
/// @param    event: L'event 'TransmitFrame'.
///
SDOClient::SDOClient(
    ITransmitFrameEvent &event) :

    _state {State::idle} {

    _transmitFrameEventRaiser.enable(event);
}


/// ---------------------------------------------------------------------------
/// @brief    Transmissio de dades cap a un servidor SDO.
///           Aquesta versio genera una trasmisio expeditiva i serveis per
///           tot tipus de valors enters.
/// @tparam   T_: Tipus de dades (Entre 1 i 4 bytes de longitut suportada)
/// @param    serverId: Id del servidor SDO
/// @param    index: L'index de l'entrada del disccionari
/// @param    subIndex: El subindex
/// @param    data: Les dades a transmetre.
/// @return   El resultat de l'operacio.
///
template <typename T_>
requires (sizeof(T_) >= 1 && sizeof(T_) <= 4)
StdResult SDOClient::download(
    NodeID serverId,
    UInt16 index,
    UInt8 subIndex,
    T_ data) {

    if (_state != State::idle)
        return StdErrorCode::busy;

    SdoDownloadInitiateRequest frame;
    frame.ccs         = SdoCCS::initiateDownload;
    frame.withSize    = true;
    frame.expedited   = true;
    frame.unusedBytes = 4 - sizeof(T_);
    frame.index       = index;
    frame.subIndex    = subIndex;
    std::memcpy(frame.data, &data, sizeof(data));

    transmitFrame(
        CobID::makeSDO(serverId),
        reinterpret_cast<const UInt8*>(&frame),
        sizeof(frame));

    _state = State::downloadExpedited;

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Transmissio de dades cap al servidor SDO.
/// @param    serverId: El identificador del node del servvidor.
/// @param    index: Index de la entrada del diccionari.
/// @param    subIndex: Subindex de l'entrada del diccionari.
/// @param    data: Dades a transmetre.
/// @param    dataSize: Tamany en bytes de les dades a transmetre.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::download(
    NodeID serverId,
    UInt16 index,
    UInt8 subIndex,
    const UInt8 *data,
    UInt32 dataSize) {

    if (_state != State::idle)
        return StdErrorCode::busy;

    if ((data == nullptr) || (dataSize == 0))
        return StdErrorCode::errorParameter;

    _serverId = serverId;
    _ptr = data;
    _ptrEnd = data + (dataSize * sizeof(UInt8));

    // Si la longitut esta entre 0 i 4, utilitza la transmissio expeditiva
    //
    if (dataSize <= 4) {

        SdoDownloadInitiateRequest frame;
        std::memset(&frame, 0, sizeof(frame));
        frame.withSize    = true;
        frame.expedited   = true;
        frame.unusedBytes = 4 - dataSize;
        frame.index       = index;
        frame.subIndex    = subIndex;
        std::memcpy(frame.data, data, dataSize);

        transmitFrame(
            CobID::makeSDO(serverId),
            reinterpret_cast<const UInt8*>(&frame),
            sizeof(frame));

        _state = State::downloadExpedited;
    }

    // En cas contrari utilitza la transmissio segmentada
    //
    else {
        SdoDownloadInitiateRequest frame;
        std::memset(&frame, 0, sizeof(frame));
        frame.withSize    = true;
        frame.expedited   = false;
        frame.unusedBytes = 0;
        frame.index       = index;
        frame.subIndex    = subIndex;
        std::memcpy(frame.data, &dataSize, sizeof(frame.data));

        transmitFrame(
            CobID::makeSDO(serverId),
            reinterpret_cast<const UInt8*>(&frame),
            sizeof(frame));

        /*
        UInt8 frame[8];
        frame[0] =
            SDO0::CCS_DN |
            SDO0::S_SIZE |
            SDO0::E_SEG;

        frame[1] = index & 0xFF;
        frame[2] = index >> 8;
        frame[3] = subIndex;

        frame[4] = (dataSize >> 0) & 0xFF;
        frame[5] = (dataSize >> 8) & 0xFF;
        frame[6] = (dataSize >> 16) & 0xFF;
        frame[7] = (dataSize >> 24) & 0xFF;

        transmitFrame(CobID::makeSDO(serverId), frame, sizeof(frame));
        */

        _toggle = false;
        _state = State::downloadSegment;
    }

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Aborta la transmissio.
/// @param    errorCode: Codi d'error SDO.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::abort(
    SdoError errorCode) {

    if (_state == State::idle)
        return StdErrorCode::errorState;

    SdoAbort frame;
    std::memset(&frame, 0, sizeof(frame));
    frame.cs        = SdoCS::abort;
    frame.index     = _index;
    frame.subIndex  = _subIndex
    frame.errorCode = errorCode;

    transmitFrame(
        CobID::makeSDO(serverId),
        reinterpret_cast<const UInt8*>(&frame),
        sizeof(frame));

    _state = State::idle;

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les respostes del servidor SDO
/// @param    frame: La resposta.
/// @param    frameSize: Tamany de lka resposta en bytes;
/// @return   El resultat de l'operacio.
///
SDOClientResult SDOClient::processServerResponse(
    const UInt8 *frame,
    UInt32 frameSize) {

    if (frameSize != sizeof(SdoFrame))
        return SDOClientErrorCode::errorParameter;

    switch (_state) {
        case State::downloadExpedited:
            return downloadExpeditedResponse(reinterpret_cast<const SdoDownloadInitiateResponse*>(frame));

        case State::downloadSegment:
            downloadNextSegmentResponse();
            break;

        case State::downloadBlock:
            downloadNextBlockResponse();
            break;

        case State::uploadExpedited:
            uploadExpeditedResponse();
            break;

        case State::uploadSegment:
            uploadNextSegmentResponse();
            break;

        case State::uploadBlock:
            uploadNextBlockResponse();
            break;
    }

    return SDOClientErrorCode::error;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la resposta
/// @param    frame: La trama de la resposta.
/// @return   El resultat de l'operacio.
///
SDOClientResult SDOClient::downloadExpeditedResponse(
    const SdoDownloadInitiateResponse *frame) {

    _state = State::idle;

    switch (frame->scs) {
        case SdoSCS::initiateDownload:
            return SDOClientErrorCode::ok;

        case SdoSCS::abort:
            return {SDOClientErrorCode::error, (SdoError) *((UInt32*)&frame->reserved)};
    }

    return {SDOClientErrorCode::error, SdoError::commandSpecifierNotValid};
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet el seguewnt segment.
///
void SDOClient::downloadNextSegmentResponse() {

    UInt32 dataSize = _ptrEnd - _ptr;
    if (dataSize > 0) {

        UInt8 frame[8];
        frame[0] =
            SDO0::CCS_DNSEG |
            (_toggle ? SDO0::T_ONE : SDO0::T_ZERO);

        frame[1] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[2] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[3] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[4] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[5] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[6] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[7] = _ptr != _ptrEnd ? *_ptr++ : 0;

        _toggle = !_toggle;

        transmitFrame(CobID::makeSDO(_serverId), frame, sizeof(frame));

        if (dataSize < 8)
            _state = State::idle;
    }
}


void SDOClient::uploadExpeditedResponse() {

    _state = State::idle;
}


void SDOClient::downloadNextBlockResponse() {

}


void SDOClient::uploadNextSegmentResponse() {

}


void SDOClient::uploadNextBlockResponse() {

}


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama.
/// @param    cobId: El COBID.
/// @param    frame: Les dades.
/// @param    frameSize: El tamany de les dades en bytes.
///
void SDOClient::transmitFrame(
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
