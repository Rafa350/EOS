#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlINT.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"

#include <cmath>


#define PATTERN_MASK     0x000000FF
#define PATTERN_POSEDGE  0x0000007F
#define PATTERN_NEGEDGE  0x00000080
#define PATTERN_ACTIVE   0x000000FF
#define PATTERN_IDLE     0x00000000


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

	removeInputs();
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
void DigInputService::onInitialize(
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

    unsigned lastWeakTime = Task::getTickCount();

    while (!stopSignal()) {

		Task::delay(_scanPeriod, lastWeakTime);

		notifyBeforeScan();

		if (scanInputs()) {
			for (auto input: _inputs) {

				bool ie = getInterruptState();
				if (ie)
					disableInterrupts();

				bool flag = input->_pinStatus.flag;
				input->_pinStatus.flag = false;

				if (ie)
					enableInterrupts();

				if (flag)
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
                input->_pinStatus.state = 1;
                input->_pinStatus.edges += 1;
                input->_pinStatus.flag = 1;
                changed = true;
            }

            // Analitza el patro per detectar un flanc negatiu
            //
            else if ((input->_pattern & PATTERN_MASK) == PATTERN_NEGEDGE) {
                input->_pinStatus.state = 0;
                input->_pinStatus.edges += 1;
                input->_pinStatus.flag = 1;
                changed = true;
            }
        }
    }

    return changed;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \param    input: La entrada.
/// \return   True si esta en estat ACTIVE, false en cas contrari.
///
bool DigInputService::read(
    const DigInput *input) const {

    eosAssert(input != nullptr);
    eosAssert(input->_service == this);

    Task::enterCriticalSection();

    bool value = input->_pinStatus.state == 1;

    Task::exitCriticalSection();

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de pulsos de l'entrada.
/// \param    input: La entrada.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
uint32_t DigInputService::getEdges(
	DigInput *input,
	bool clear) const {

    eosAssert(input != nullptr);
    eosAssert(input->_service == this);

    Task::enterCriticalSection();

    unsigned edges = input->_pinStatus.edges;
    if (clear)
    	input->_pinStatus.edges = 0;

    Task::exitCriticalSection();

    return edges;
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
        _pinStatus.state = 1;
        _pattern = PATTERN_ACTIVE;
    }
    else {
        _pinStatus.state = 0;
        _pattern = PATTERN_IDLE;
    }
    _pinStatus.edges = 0;
    _pinStatus.flag = false;

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
