export module Eos.Services.CanOpen._NMTMaster;

import Eos.Events;
import Eos.Services.CanOpen._Types;
import Eos.Services.CanOpen.Protocol;
import Eos.Result;
import Eos.Types;


export namespace eos {

    class NMTMaster final: private NonCopyableClass {
        public:
            struct TransmitFrameEventArgs {
                CobID cobId;
                const UInt8 *frame;
                UInt32 frameSize;
            };
    		using TransmitFrameEventRaiser = EventRaiser<NMTMaster, TransmitFrameEventArgs>;
			using ITransmitFrameEvent = TransmitFrameEventRaiser::IEvent;
			template <typename Instance_> using TransmitFrameEvent = TransmitFrameEventRaiser::Event<Instance_>;

        private:
            TransmitFrameEventRaiser _transmitFrameEventRaiser;

        private:
            void transmitFrame(CobID cobId, const UInt8 *frame, UInt32 frameSize);

        public:
            NMTMaster(ITransmitFrameEvent &event);

			void start(NodeID remoteId);
			void stop(NodeID remoteId);
			void enterPreOperational(NodeID remoteId);
			void resetNode(NodeID remoteId);
			void resetCommunication(NodeID remoteId);
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Contructor.
/// @param    event: L'event 'TransmitFrame'.
///
NMTMaster::NMTMaster(
    ITransmitFrameEvent &event) {

    _transmitFrameEventRaiser.enable(event);
}


/// ---------------------------------------------------------------------------
/// @brief    Posa un node en estat 'operational'.
/// @param    remoteId: Node remot.
///
void NMTMaster::start(
	NodeID remoteId) {

	// Emet la comanda NMT 'Start'
	//
	UInt8 frame[2];
	frame[0] = 0x01;
	frame[1] = remoteId;

    transmitFrame(CobID::makeNMT(), frame, sizeof(frame));
}


/// ---------------------------------------------------------------------------
/// @brief    Posar un node en estat 'stoped'
/// @param    remoteId: Node destinatati
///
void NMTMaster::stop(
	NodeID remoteId) {

	// Emet la comanda NMT 'Stop'
	//
	UInt8 frame[2];
	frame[0] = 0x02;
	frame[1] = remoteId;

    transmitFrame(CobID::makeNMT(), frame, sizeof(frame));
}


/// ---------------------------------------------------------------------------
/// @brief    Posar un node en estat 'pre-operational'.
/// @param    remoteId: Node destinatati
///
void NMTMaster::enterPreOperational(
	NodeID remoteId) {

	// Emet la comanda NMT 'Enter Pre-Operational'
	//
	UInt8 frame[2];
	frame[0] = 0x80;
	frame[1] = remoteId;

    transmitFrame(CobID::makeNMT(), frame, sizeof(frame));
}


/// ---------------------------------------------------------------------------
/// @brief    Reseteja un node..
/// @param    remoteId: Node destinatati
///
void NMTMaster::resetNode(
	NodeID remoteId) {

	// Emet la comanda NMT 'Reset Node'
	//
	UInt8 frame[2];
	frame[0] = 0x81;
	frame[1] = remoteId;

    transmitFrame(CobID::makeNMT(), frame, sizeof(frame));
}


/// ---------------------------------------------------------------------------
/// @brief    Reseteja les comunicacions d'un node.
/// @param    remoteId: Node destinatati
///
void NMTMaster::resetCommunication(
	NodeID remoteId) {

	// Emet la comanda NMT 'Reset Comunication'
	//
	UInt8 frame[2];
	frame[0] = 0x82;
	frame[1] = remoteId;

    transmitFrame(CobID::makeNMT(), frame, sizeof(frame));
}


/// --------------------------------------------------------------------------------
/// @brief    Transmet una trama.
/// @param    cobId: El COBID.
/// @param    frame: Les dades.
/// @param    frameSize: El tamany de les dades en bytes.
///
void NMTMaster::transmitFrame(
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
