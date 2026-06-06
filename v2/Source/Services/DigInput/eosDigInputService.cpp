#include "eos.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"
#include "Services/DigInput/eosDigInputService.h"
#include "eos_diginput_inputs.h"

#include <cmath>


using namespace eos;


constexpr const char *serviceName = "DigInputs";
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::normal;
constexpr unsigned serviceStackDepth = 160;

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
/// \brief    Genera un event que notifica un canvi en l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::raiseChangedNotificationEvent(
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
/// \brief    Genera un event que notifica l'inici del scaneig de les entrades.
///
void DigInputService::raiseBeforeScanNotificationEvent() {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::beforeScan}
		};

    	_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event que motifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void DigInputService::raiseInitializeNotificationEvent(
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
/// \brief    Afegeix una entrada el servei.
/// \param    drv: El driver del pin.
/// \param    tag: Etiqueta opcional
/// \return   L'entrada.
///
DigInput * DigInputService::addInput(
	PinDriver *drv,
	uint32_t tag) {

    auto input = new Input(drv, tag);

    rtos::Task::enterCriticalSection();
	_inputs.pushFront(input);
    rtos::Task::exitCriticalSection();

    return input;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'entrada amb el tag especificat.
/// \param    tag: El tag de l'entrada a buscar.
/// \return   L'entrada, o nullptr si no la troba.
///
DigInput *DigInputService::getInput(
	uint32_t tag) const {

	for (auto input: _inputs)
		if (input->getTag() == tag)
			return input;

	return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void DigInputService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.priority = servicePriority;
	params.stackDepth = serviceStackDepth;

	raiseInitializeNotificationEvent(&params);
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei
///
void DigInputService::onExecute() {

    while (!stopSignal()) {

		rtos::Task::delayUntil(rtos::Time::fromMiliseconds(_scanPeriod));

		// Notifica l'inici de l'escaneig d'entrades
		//
		raiseBeforeScanNotificationEvent();

		// Escaneja totes les entradas una a una
		//
		for (auto input: _inputs) {
			auto inp = static_cast<Input*>(input);

			// Escaneja una entrada i si hi canvis,
			// genera un event de notificacio.
			//
			if (inp->scan())
				raiseChangedNotificationEvent(input);
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

    rtos::Task::enterCriticalSection();

    auto inp = static_cast<const Input*>(input);
    bool value = inp->getValue();

    rtos::Task::exitCriticalSection();

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

    rtos::Task::enterCriticalSection();

    auto inp = static_cast<Input*>(input);
    unsigned edges = inp->getCount(clear);

    rtos::Task::exitCriticalSection();

    return edges;
}
