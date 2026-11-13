export module Eos.Services.CanOpen._SDOClient;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Protocol;
import Eos.Result;
import Eos.Types;


export namespace eos {

    class SDOClient: private NonCopyableClass {
        public:
            struct TransmitFrameEventArgs {
                CobID cobId;
                const UInt8 *frame;
                UInt32 frameSize;
            };
    		using TransmitFrameEventRaiser = EventRaiser<SDOClient, TransmitFrameEventArgs>;
			using ITransmitFrameEvent = TransmitFrameEventRaiser::IEvent;
			template <typename Instance_> using TransmitFrameEvent = TransmitFrameEventRaiser::Event<Instance_>;

        public:
            enum class State {
                idle,
                uploading,
                downloading
            };

        private:
            State _state;
            TransmitFrameEventRaiser _transmitFrameEventRaiser;
            CobID _cobId;
            UInt16 _index;
            UInt8 _subIndex;
            bool _toggle;
            const UInt8 *_ptr;
            const UInt8 *_ptrEnd;

        private:
            void transmitFrame(const UInt8 *frame, UInt32 frameSize);

        public:
            SDOClient(ITransmitFrameEvent &event);

            StdResult download(NodeID nodeId, UInt16 index, UInt8 subIndex, const UInt8 *data, UInt32 dataLength);
            StdResult download();

            State getState() const { return _state; }
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Contructor.
/// @param    event: L'event 'TransmitFrame'.
///
SDOClient::SDOClient(
    ITransmitFrameEvent &event) :

    _state {State::idle},
    _cobId {CobID::make(0)} {

    _transmitFrameEventRaiser.enable(event);
}


/// ---------------------------------------------------------------------------
/// @brief    Transmissio de dades cap al servidor SDO.
/// @param    nodeId: El identificador del node del servvidor.
/// @param    index: Index de la entrada del diccionari.
/// @param    subIndex: Subindex de l'entrada del diccionari.
/// @param    data: Dades a transmetre.
/// @param    dataSize: Tamany en bytes de les dades a transmetre.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::download(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    const UInt8 *data,
    UInt32 dataSize) {

    if (_state != State::idle)
        return StdErrorCode::errorState;

    if ((data == nullptr) || (dataSize == 0))
        return StdErrorCode::errorParameter;

    _cobId = CobID::makeSDO(nodeId);

    _index = index;
    _subIndex = subIndex;

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

        frame[1] = _index & 0xFF;
        frame[2] = _index >> 8;
        frame[3] = _subIndex;

        frame[4] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[5] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[6] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[7] = _ptr != _ptrEnd ? *_ptr++ : 0;

        transmitFrame(frame, sizeof(frame));
    }

    // En cas contrari utilitza la transmissio segmentada
    //
    else {
        UInt8 frame[8];
        frame[0] =
            SDO0::CCS_DN |
            SDO0::S_SIZE |
            SDO0::E_SEG;

        frame[1] = _index & 0xFF;
        frame[2] = _index >> 8;
        frame[3] = _subIndex;

        frame[4] = (dataSize >> 0) & 0xFF;
        frame[5] = (dataSize >> 8) & 0xFF;
        frame[6] = (dataSize >> 16) & 0xFF;
        frame[7] = (dataSize >> 24) & 0xFF;

        transmitFrame(frame, sizeof(frame));

        _toggle = false;
        _state = State::uploading;
    }

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Continua amb la tramissio de dades pendent.
/// @return   El resultat de l'operacio.
///
StdResult SDOClient::download() {

    if (_state == State::idle)
        return StdErrorCode::errorState;

    UInt32 dataSize = _ptrEnd - _ptr;
    if (dataSize != 0) {

        UInt8 frame[8];
        frame[0] =
            SDO0::CCS_DN |
            (_toggle ? SDO0::T_ONE : SDO0::T_ZERO);

        frame[1] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[2] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[3] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[4] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[5] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[6] = _ptr != _ptrEnd ? *_ptr++ : 0;
        frame[7] = _ptr != _ptrEnd ? *_ptr++ : 0;

        _toggle = !_toggle;

        transmitFrame(frame, sizeof(frame));
    }

    return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama
/// @param    frame: La trama.
/// @param    frameSize: El tamany de la trama.
///
void SDOClient::transmitFrame(
    const UInt8 *frame,
    UInt32 frameSize) {

    TransmitFrameEventArgs args = {
        .cobId {_cobId},
        .frame {frame},
        .frameSize {frameSize}
    };
    _transmitFrameEventRaiser(this, &args);
}
