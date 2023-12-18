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
using namespace htl::irq;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \params   settings: Conmfigurationparameters.
///
DigInputService::DigInputService():
    Service(),
    _changedEvent {nullptr},
    _changedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

}


/// ----------------------------------------------------------------------
/// \brief    Configura el event 'Changed'
/// \param    event: El event.
/// \param    enabled: True si es vol habilitar.
///
void DigInputService::setChangedEvent(
    IChangedEvent &event,
    bool enabled) {

    _changedEvent = &event;
    _changedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'Changed'
///
void DigInputService::enableChangedEvent() {

    _changedEventEnabled = _changedEvent != nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'event 'Changed'
///
void DigInputService::disableChangedEvent() {

    _changedEventEnabled = false;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::notifyChanged(
    DigInput *input) {

    if (_changedEventEnabled) {
        ChangedEventArgs args = {
            .input = input
        };
        _changedEvent->execute(this, args);
    }

    if (input->_changedEventEnabled) {
        DigInput::ChangedEventArgs args = {
            .pinState = input->_pinState,
            .pinPulses = input->_pinPulses
        };
        input->_changedEvent->execute(input, args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *input) {

    eosAssert(input != nullptr);
    eosAssert(input->_service == nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Afegeix l'entrada a la llista
    //
    if (input->_service == nullptr) {
        input->_service = this;
        _inputs.pushFront(input);
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
    eosAssert(input->_service == this);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (input->_service == this) {
        _inputs.remove(input);
        input->_service = nullptr;
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

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio. Es crida repetidament.
/// \return   True per continuar el bucle, false per finalitzar.
///
bool DigInputService::onTask() {

    while (_changes.wait(unsigned(-1))) {

        for (auto input: _inputs) {

            bool ie = getInterruptState();
            if (ie)
                disableInterrupts();

            bool edge = input->_edge;
            input->_edge = false;

            if (ie)
                enableInterrupts();

            if (edge)
                notifyChanged(input);
        }
    }

    return true;
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
                input->_pinState = true;
                input->_edge = 1;
                changed = true;
            }

            // Analitza el patro per detectar un flanc negatiu
            //
            else if ((input->_pattern & PATTERN_MASK) == PATTERN_NEGEDGE) {
                input->_pinState = false;
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
bool DigInputService::read(
    const DigInput *input) const {

    eosAssert(input != nullptr);
    eosAssert(input->_service == this);

    Task::enterCriticalSection();

    bool pinState = input->_pinState;

    Task::exitCriticalSection();

    return pinState;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de pulsos de l'entrada.
/// \param    input: La entrada.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
uint32_t DigInputService::readPulses(
	DigInput *input,
	bool clear) const {

    eosAssert(input != nullptr);
    eosAssert(input->_service == this);

    Task::enterCriticalSection();

    uint32_t pinPulses = input->_pinPulses;
    if (clear)
    	input->_pinPulses = 0;

    Task::exitCriticalSection();

    return pinPulses;
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

    if (_drv->read()) {
        _pinState = true;
        _pattern = PATTERN_ON;
    }
    else {
        _pinState = false;
        _pattern = PATTERN_OFF;
    }
    _pinPulses = 0;
    _edge = false;

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


/// ----------------------------------------------------------------------
/// \brief    Configura el event 'Changed'
/// \param    event: El event.
/// \param    enabled: True si es vol habilitar.
///
void DigInput::setChangedEvent(
	IChangedEvent &event,
	bool enabled) {

    _changedEvent = &event;
    _changedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'Changed'
///
void DigInput::enableChangedEvent() {

	_changedEventEnabled = _changedEvent != nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'event 'Changed'
///
void DigInput::disableChangedEvent() {

	_changedEventEnabled = false;
}
