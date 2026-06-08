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

constexpr uint32_t minScanPeriod = 5;  // Periode d'exploracio minim en ms


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DigInputService::DigInputService():
    Service(),
	_inputChangedEvent {nullptr},
	_beforeScanEvent {nullptr},
    _scanPeriod {minScanPeriod} {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode d'escaneig.
/// \param    scanPeriod: El period en milisegons.
///
void DigInputService::setScanPeriod(
    uint32_t scanPeriod) {

    _scanPeriod = std::max(scanPeriod, minScanPeriod);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event quant canvia l'estat d'una entrada.
/// \param    input: L'entrada.
///
void DigInputService::onInputChanged(
    DigInput *input) {

	if (_inputChangedEvent != nullptr) {

    	auto i = static_cast<Input*>(input);

    	InputChangedEventArgs args = {
   			.tag {i->getTag()},
			.value {i->getValue()}
    	};

    	_inputChangedEvent->execute(this, &args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event abans del inici de l'exploracio de
///           les entrades.
///
void DigInputService::beforeScan() {

	if (_beforeScanEvent != nullptr)
		_beforeScanEvent->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event que motifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void DigInputService::raiseInitializeNotificationEvent(
	ServiceParams *params) {

	/*if (_notificationEvent != nullptr) {

		NotificationEventArgs args = {
			.id {NotificationID::initialize},
			.initialize {
				.params {params}
			}
		};

		_notificationEvent->execute(this, &args);
	}
	*/
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

	DigInput *result = nullptr;

	rtos::Task::enterCriticalSection();
	for (auto input: _inputs)
		if (input->getTag() == tag) {
			result = input;
			break;
		}
	rtos::Task::exitCriticalSection();

	return result;
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
		beforeScan();

		// Escaneja totes les entradas una a una
		//
		for (auto input: _inputs) {
			auto inp = static_cast<Input*>(input);

			// Escaneja una entrada i si hi canvis,
			// genera un event de notificacio.
			//
			if (inp->scan())
				onInputChanged(input);
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
    auto value = inp->getValue();

    rtos::Task::exitCriticalSection();

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

    rtos::Task::enterCriticalSection();

    auto inp = static_cast<Input*>(input);
    auto edges = inp->getCount(clear);

    rtos::Task::exitCriticalSection();

    return edges;
}
