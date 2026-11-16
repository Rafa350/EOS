export module Eos.Services.CanOpen._SDOServer;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Protocol;
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
            TransmitFrameEventRaiser _transmitFrameEventRaiser;

        private:
            void transmitFrame(CobID cobId, const UInt8 *frame, UInt32 frameSize);

            bool downloadExpedited(const UInt8 *frame, UInt32 frameSize);
            bool downloadInitiate(const UInt8 *frame, UInt32 frameSize);
            bool downloadSegment(const UInt8 *frame, UInt32 frameSize);

        public:
            SDOServer(ITransmitFrameEvent &event);

            bool start();
            bool stop();

            bool processClientRequest(const UInt8 *frame, UInt32 frameSize);
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @param    event : Event 'TransmitFrame'
///
SDOServer::SDOServer(
    ITransmitFrameEvent &event):

    _state {State::stop} {

    _transmitFrameEventRaiser.enable(event);
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

    return false;
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
