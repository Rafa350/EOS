#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlINT.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"

#include <cmath>


#define PATTERN_MASK     0x0FFF
#define PATTERN_POSEDGE  0x07FF
#define PATTERN_NEGEDGE  0x0800
#define PATTERN_ON       0x0FFF
#define PATTERN_OFF      0x0000


using namespace eos;
using namespace htl::irq;


constexpr const char *serviceName = "DigInput";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 128;

constexpr unsigned minScanPeriod = 5;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \params   settings: Conmfigurationparameters.
///
DigInputService::DigInputService():
    Service(),
    _scanPeriod {minScanPeriod} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode d'escaneig.
/// \param    scanPeriod: El period en milisegons.
///
void DigInputService::setScanPeriod(
    unsigned scanPeriod) {

    _scanPeriod = std::max(scanPeriod, minScanPeriod);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::notifyChanged(
    DigInput *input) {

    if (_erNotify.isEnabled(NotifyID::changed)) {
    	NotifyEventArgs args = {
    		.changed {
    			.input = input
    		}
    	};
    	_erNotify.raise(NotifyID::changed, &args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el inici del scaneig de les entrades.
///
void DigInputService::notifyBeforeScan() {

	if (_erNotify.isEnabled(NotifyID::beforeScan))
    	_erNotify.raise(NotifyID::beforeScan);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void DigInputService::notifyInitialize(
	ServiceParams *params) {

	if (_erNotify.isEnabled(NotifyID::initialize)) {
		NotifyEventArgs args = {
			.initialize {
				.params = params
			}
		};
		_erNotify.raise(NotifyID::initialize, &args);
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
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void DigInputService::initService(
	ServiceParams &params) {

	params.name = serviceName;
	params.priority = servicePriority;
	params.stackSize = serviceStackSize;

	notifyInitialize(&params);
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei
///
void DigInputService::onExecute() {

    _weakTime = Task::getTickCount();

    while (!stopSignal()) {

		Task::delay(_scanPeriod, _weakTime);

		notifyBeforeScan();

		if (scanInputs()) {
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
	}
}


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
/// \brief    Constructor.
/// \param    service: The service.
/// \param    drv: El driver del pin
///
DigInput::DigInput(
    DigInputService *service,
    PinDriver *drv):

	_service {nullptr},
    _drv {drv},
    _scanMode {ScanMode::polling} {

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
