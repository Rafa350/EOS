#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosKernel.h"
#include "eos_diginput_inputs.h"

#include <cmath>


using namespace eos;


constexpr const char *serviceName = "DigInputs";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 160;

constexpr unsigned minScanPeriod = 5;  // Periode d'exploracio minim en ms


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
/// \brief    Asigna l'event de notificacio.
/// \param    event: L'event.
/// \param    enabled: True per habiliotar el event.
///
void DigInputService::setNotificationEvent(
	INotificationEvent &event,
	bool enabled) {

	_erNotification.set(event, enabled);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event de notificacio
//
void DigInputService::enableNotifyEvent() {

	_erNotification.enable();
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'event de notificacio
//
void DigInputService::disableNotifyEvent() {

	_erNotification.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::raiseChangedNotification(
    DigInput *input) {

    if (_erNotification.isEnabled()) {

    	auto i = static_cast<Input*>(input);

    	NotificationEventArgs args = {
    		.id {NotificationID::changed},
			.changed {
    			.input {i},
				.value {i->getValue()}
    		}
    	};

    	_erNotification(this, &args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el inici del scaneig de les entrades.
///
void DigInputService::raiseBeforeScanNotification() {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::beforeScan}
		};

    	_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void DigInputService::raiseInitializeNotification(
	ServiceParams *params) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::initialize},
			.initialize {
				.params {params}
			}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Crea una entrada.
/// \param    pinDrv: El driver del pin.
/// \return   L'entrada.
///
DigInput * DigInputService::makeInput(
	PinDriver * pinDrv) {

    return new Input(pinDrv);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput *input) {

    Task::enterCriticalSection();

    auto inp = static_cast<Input*>(input);
    if (!_inputs.contains(inp))
		_inputs.pushFront(inp);

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput *input) {

    Task::enterCriticalSection();

    auto inp = static_cast<Input*>(input);
    if (_inputs.contains(inp))
        _inputs.remove(inp);

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

	raiseInitializeNotification(&params);
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei
///
void DigInputService::onExecute() {

    unsigned lastTick = Kernel::pInst->getTickCount();

    while (!stopSignal()) {

		Task::delay(_scanPeriod, lastTick);

		raiseBeforeScanNotification();

		for (auto input: _inputs) {
			auto inp = static_cast<Input*>(input);
			if (inp->scan())
				raiseChangedNotification(input);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \param    input: La entrada.
/// \return   True si esta en estat ACTIVE, false en cas contrari.
///
bool DigInputService::read(
    const DigInput *input) const {

    Task::enterCriticalSection();

    auto inp = static_cast<const Input*>(input);
    bool value = inp->getValue();

    Task::exitCriticalSection();

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de pulsos de l'entrada.
/// \param    input: La entrada.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
unsigned DigInputService::getEdges(
	DigInput *input,
	bool clear) const {

    Task::enterCriticalSection();

    auto inp = static_cast<Input*>(input);
    unsigned edges = inp->getCount(clear);

    Task::exitCriticalSection();

    return edges;
}
