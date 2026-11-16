export module Eos.Services.CanOpen._SDOClient;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Protocol;
import Eos.Result;
import Eos.Types;


export namespace eos {

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
                uploadSegment,
                uploadBlock,
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

            void downloadNextSegment();
            void downloadNextBlock();
            void uploadNextSegment();
            void uploadNextBlock();

        public:
            SDOClient(ITransmitFrameEvent &event);

            StdResult download(NodeID serverId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult upload(NodeID serverId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);

            StdResult processServerResponse(const UInt8 *frame, UInt32 frameSize);
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

    	UInt8 frame[8];
        frame[0] =
            SDO0::CCS_DN |
            SDO0::S_SIZE |
            SDO0::E_EXP |
            (((4 - dataSize) << SDO0::S_Pos) & SDO0::S_Msk);

        frame[1] = index & 0xFF;
        frame[2] = index >> 8;
        frame[3] = subIndex;

        frame[4] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[5] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[6] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[7] = _ptr != _ptrEnd ? *_ptr++ : 0;

        transmitFrame(CobID::makeSDO(_serverId), frame, sizeof(frame));
    }

    // En cas contrari utilitza la transmissio segmentada
    //
    else {
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

        transmitFrame(CobID::makeSDO(_serverId), frame, sizeof(frame));

        _toggle = false;
        _state = State::downloadSegment;
    }

    return StdErrorCode::ok;
}


/*
/// ---------------------------------------------------------------------------
/// @brief    Aborta la transmissio.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::abort() {

    if (_state == State::idle)
        return StdErrorCode::errorState;

    UInt8 frame[8];
    frame[0] = SDO0::CCS_ABORT;
    frame[1] = _index & 0xFF;
    frame[2] = _index >> 8;
    frame[3] = _subIndex;
    frame[4] = 0;
    frame[5] = 0;
    frame[6] = 0;
    frame[7] = 0;

    transmitFrame(CobID::makeSDO(_serverId), frame, sizeof(frame));

    _state = State::idle;

    return StdErrorCode::ok;
}
*/

/// ---------------------------------------------------------------------------
/// @brief    Procesa les respostes del servidor SDO
/// @param    frame: La resposta.
/// @param    frameSize: Tamany de lka resposta en bytes;
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::processServerResponse(
    const UInt8 *frame,
    UInt32 frameSize) {

    switch (frame[0] & SDO0::SCS_Msk) {
        case SDO0::SCS_DN:
        case SDO0::SCS_DNSEG:
            switch (_state) {
                case State::downloadSegment:
                    downloadNextSegment();
                    break;

                    case State::downloadBlock:
                    downloadNextBlock();
                    break;
            }
            break;

        case SDO0::SCS_UP:
        case SDO0::SCS_UPSEG:
            switch (_state) {
                case State::uploadSegment:
                    uploadNextSegment();
                    break;

                case State::uploadBlock:
                    uploadNextBlock();
                    break;
            }
            break;

        default:
            return StdErrorCode::error;
    }

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet el seguewnt segment.
///
void SDOClient::downloadNextSegment() {

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


void SDOClient::uploadNextSegment() {

}


void SDOClient::uploadNextBlock() {

}


void SDOClient::downloadNextBlock() {

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
