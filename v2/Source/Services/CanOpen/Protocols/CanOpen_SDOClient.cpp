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
        errorSDO,
        errorParameter,
        errorState
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

            struct TxContext {
                CobID cobId;
                UInt16 index;
                UInt8 subIndex;
                bool toggle;
                const UInt8 *ptr;
                const UInt8 *ptrEnd;
            };

        private:
            State _state;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;
            TxContext _txContext;

        private:
            void transmitFrame(CobID cobId, const SdoFrame *frame);

            SDOClientResult downloadExpeditedResponse(const SdoDownloadInitiateResponse *response);
            SDOClientResult downloadSegmentResponse(const SdoDownloadSegmentResponse *response);

            //void uploadExpeditedResponse(const SdoUploadInitiateResponse *response);
            //void uploadSegmentResponse(const SdoUploadSegmentResponse *response);

        public:
            SDOClient(ITransmitFrameEvent &event);

            template <typename T_>
            requires (sizeof(T_) >= 1 && sizeof(T_) <= 4)
                StdResult download(CobID cobId, UInt16 index, UInt8 subIndex, T_ data);
            StdResult download(CobID cobId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult upload(CobID cobId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult abort(SdoError errorCode);

            SDOClientResult processServerResponse(const SdoFrame *response);
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
/// @param    cobId: El COBID del servidor SDO
/// @param    index: L'index de l'entrada del disccionari
/// @param    subIndex: El subindex
/// @param    data: Les dades a transmetre.
/// @return   El resultat de l'operacio.
///
template <typename T_>
requires (sizeof(T_) >= 1 && sizeof(T_) <= 4)
StdResult SDOClient::download(
    CobID cobId,
    UInt16 index,
    UInt8 subIndex,
    T_ data) {

    if (_state != State::idle)
        return StdErrorCode::busy;

    SdoDownloadInitiateRequest request;
    std::memset(&request, 0, sizeof(request));
    request.ccs         = SdoCCS::initiateDownload;
    request.withSize    = true;
    request.expedited   = true;
    request.unusedBytes = 4 - sizeof(T_);
    request.index       = index;
    request.subIndex    = subIndex;
    std::memcpy(request.data, &data, sizeof(data));

    transmitFrame(
        cobId,
        reinterpret_cast<const SdoFrame*>(&request));

    _state = State::downloadExpedited;

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Transmissio de dades cap al servidor SDO.
/// @param    cobId: El COBID del servidos SDO.
/// @param    index: Index de la entrada del diccionari.
/// @param    subIndex: Subindex de l'entrada del diccionari.
/// @param    data: Dades a transmetre.
/// @param    dataSize: Tamany en bytes de les dades a transmetre.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::download(
    CobID cobId,
    UInt16 index,
    UInt8 subIndex,
    const UInt8 *data,
    UInt32 dataSize) {

    if (_state != State::idle)
        return StdErrorCode::busy;

    if ((data == nullptr) || (dataSize == 0))
        return StdErrorCode::errorParameter;

    _txContext.cobId = cobId;
    _txContext.ptr = data;
    _txContext.ptrEnd = data + (dataSize * sizeof(UInt8));

    // Si la longitut esta entre 0 i 4, utilitza la transmissio expeditiva
    //
    if (dataSize <= 4) {

        SdoDownloadInitiateRequest request;
        std::memset(&request, 0, sizeof(request));
        request.withSize    = true;
        request.expedited   = true;
        request.unusedBytes = 4 - dataSize;
        request.index       = index;
        request.subIndex    = subIndex;
        std::memcpy(request.data, data, dataSize);

        transmitFrame(cobId, reinterpret_cast<const SdoFrame*>(&request));

        _state = State::downloadExpedited;
    }

    // En cas contrari utilitza la transmissio segmentada
    //
    else {
        SdoDownloadInitiateRequest request;
        std::memset(&request, 0, sizeof(request));
        request.withSize    = true;
        request.expedited   = false;
        request.unusedBytes = 0;
        request.index       = index;
        request.subIndex    = subIndex;
        std::memcpy(request.data, &dataSize, sizeof(request.data));

        transmitFrame(cobId, reinterpret_cast<const SdoFrame*>(&request));

        /*
        UInt8 request[8];
        request[0] =
            SDO0::CCS_DN |
            SDO0::S_SIZE |
            SDO0::E_SEG;

        request[1] = index & 0xFF;
        request[2] = index >> 8;
        request[3] = subIndex;

        request[4] = (dataSize >> 0) & 0xFF;
        request[5] = (dataSize >> 8) & 0xFF;
        request[6] = (dataSize >> 16) & 0xFF;
        request[7] = (dataSize >> 24) & 0xFF;

        transmitFrame(CobID::makeSDO(serverId), request, sizeof(request));
        */

        _txContext.toggle = false;
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

    SdoAbortRequest request;
    std::memset(&request, 0, sizeof(request));
    request.cs        = SdoCS::abort;
    request.index     = _txContext.index;
    request.subIndex  = _txContext.subIndex;
    request.errorCode = errorCode;

    transmitFrame(_txContext.cobId, reinterpret_cast<const SdoFrame*>(&request));

    _state = State::idle;

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa les respostes del servidor SDO
/// @param    response: La resposta.
/// @return   El resultat de l'operacio.
///
SDOClientResult SDOClient::processServerResponse(
    const SdoFrame *response) {

    switch (_state) {
        case State::downloadExpedited:
            return downloadExpeditedResponse(reinterpret_cast<const SdoDownloadInitiateResponse*>(response));

        case State::downloadSegment:
            return downloadSegmentResponse(reinterpret_cast<const SdoDownloadSegmentResponse*>(response));
/*
        case State::downloadBlock:
            downloadNextBlockResponse();
            return SDOClientErrorCode::error;

        case State::uploadExpedited:
            uploadExpeditedResponse();
            return SDOClientErrorCode::error;

        case State::uploadSegment:
            uploadSegmentResponse();
            return SDOClientErrorCode::error;

        case State::uploadBlock:
            uploadBlockResponse();
            return SDOClientErrorCode::error;
*/
        default:
            return SDOClientErrorCode::errorState;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la resposta
/// @param    request: La trama de la resposta.
/// @return   El resultat de l'operacio.
///
SDOClientResult SDOClient::downloadExpeditedResponse(
    const SdoDownloadInitiateResponse *request) {

    switch (request->scs) {
        case SdoSCS::initiateDownload: {
            _state = State::idle;
            return SDOClientErrorCode::ok;
        }

        case SdoSCS::abort: {
            _state = State::idle;
            return {SDOClientErrorCode::errorSDO, (SdoError) *((UInt32*)&request->reserved)};
        }

        default: {
            _state = State::idle;
            return {SDOClientErrorCode::errorSDO, SdoError::commandSpecifierNotValid};
        }
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet el seguewnt segment.
///
SDOClientResult SDOClient::downloadSegmentResponse(
    const SdoDownloadSegmentResponse *response) {

    UInt32 dataSize = _txContext.ptrEnd - _txContext.ptr;
    if (dataSize > 0) {

        UInt8 request[8];
        request[0] =
            SDO0::CCS_DNSEG |
            (_txContext.toggle ? SDO0::T_ONE : SDO0::T_ZERO);

        request[1] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[2] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[3] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[4] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[5] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[6] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;
        request[7] = _txContext.ptr != _txContext.ptrEnd ? *_txContext.ptr++ : 0;

        _txContext.toggle = !_txContext.toggle;

        transmitFrame(_txContext.cobId, reinterpret_cast<const SdoFrame*>(&request));

        if (dataSize < 8)
            _state = State::idle;
    }

    return SDOClientErrorCode::error;
}


/*void SDOClient::uploadExpeditedResponse() {

    _state = State::idle;
}



void SDOClient::uploadSegmentResponse() {

}
*/


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama.
/// @param    cobId: El COBID.
/// @param    frame: Les trama a transmetre.
///
void SDOClient::transmitFrame(
    CobID cobId,
    const SdoFrame* frame) {

    TransmitFrameEventArgs args = {
        .cobId {cobId},
        .frame {reinterpret_cast<const UInt8*>(frame)},
        .frameSize {sizeof(SdoFrame)}
    };
    _transmitFrameEventRaiser(this, &args);
}
