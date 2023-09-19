#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlINT.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"


#define PATTERN_MASK     0x0FFF
#define PATTERN_POSEDGE  0x07FF
#define PATTERN_NEGEDGE  0x0800
#define PATTERN_ON       0x0FFF
#define PATTERN_OFF      0x0000


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \params   settings: Conmfigurationparameters.
///
DigInputService::DigInputService():
	Service() {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

	_inputs.clear();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (input->_service == nullptr) {
        _inputs.pushBack(input);
        input->_service = this;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput *input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (input->_service == this) {
        input->_service = nullptr;
        //_inputs.removeAt(_inputs.indexOf(input));
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    while (!_inputs.isEmpty()) {
        DigInput *input = _inputs.peekBack();
        //_inputs.popBack();
        input->_service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {

    // Inicialitza les entrades al valor actual
    //
    for (auto input: _inputs) {
        if (input->_drv->read()) {
            input->_pinState = htl::gpio::PinState::set;
            input->_pattern = PATTERN_ON;
        }
        else {
            input->_pinState = htl::gpio::PinState::clear;
            input->_pattern = PATTERN_OFF;
        }
        input->_pinPulses = 0;
        input->_edge = false;
    }

    // Inicialitza el servei base
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    // Repeteix indefinidament
    //
    while (true) {

        // Espera que es notifiquin canvis en les entrades
        //
        if (_changes.wait(unsigned(-1))) {

            // Procesa les entrades
            //
            for (auto input: _inputs) {

                if (input->_changedEventEnabled) {

                    bool saveIrq = irq::disableInterrupts();

                    bool edge = input->_edge;
                    input->_edge = false;

                    irq::restoreInterrupts(saveIrq);

                    if (edge) {

                        DigInput::ChangedEventArgs args = {
                        	.pinState = input->_pinState,
                            .pinPulses = input->_pinPulses
                        };

                        input->_changedEvent->execute(input, args);
                    }
                }
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio 'tick'.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
#if Eos_ApplicationmTickEnabled
void DigInputService::onTick() {

}
#endif


/// ---------------------------------------------------------------------
/// \brief    Escaneja l'estat de les entrades.
/// \return   True si s'han produit canvis en l'estat de les entrades.
///
bool DigInputService::scanInputs() {

    bool changed = false;

    // Procesa totes les entrades
    //
    for (auto input: _inputs) {

        if (input->_scanMode == DigInput::ScanMode::polling) {

            // Actualitza el patro
            //
            input->_pattern <<= 1;
            if (input->_drv->read())
                input->_pattern |= 1;

            // Analitza el patro per detectar un flanc positiu
            //
            if ((input->_pattern & PATTERN_MASK) == PATTERN_POSEDGE) {
                input->_pinState = htl::gpio::PinState::set;;
                input->_edge = 1;
                changed = true;
            }

            // Analitza el patro per detectar un flanc negatiu
            //
            else if ((input->_pattern & PATTERN_MASK) == PATTERN_NEGEDGE) {
                input->_pinState = htl::gpio::PinState::clear;
                input->_pinPulses += 1;
                input->_edge = 1;
                changed = true;
            }
        }
    }

    return changed;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \param    input: La entrada.
/// \return   El estat.
///
htl::gpio::PinState DigInputService::read(
    const DigInput *input) const {

    eosAssert(input != nullptr);
    eosAssert(input->_service == this);

    bool saveIrq = irq::disableInterrupts();
    htl::gpio::PinState pinState = input->_pinState;
    irq::restoreInterrupts(saveIrq);
    return pinState;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
/// \param    event: L'event que ha generat la interrupcio.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigInputService::tmrInterruptFunction() {

	if (scanInputs()) {

		// Notifica a la tasca que hi han canvis pendents per procesar
		//
        _changes.releaseISR();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: The service.
/// \param    drv: El driver del pin
///
DigInput::DigInput(
    DigInputService *service,
    PinDriver *drv):

	_service {nullptr},
    _drv {drv},
    _scanMode {ScanMode::polling},
    _changedEvent {nullptr},
	_changedEventEnabled {false} {

    if (service != nullptr)
        service->addInput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInput::~DigInput() {

    if (_service != nullptr)
        _service->removeInput(this);
}
