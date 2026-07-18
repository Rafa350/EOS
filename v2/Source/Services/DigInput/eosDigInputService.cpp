#include "eos.h"
#include "eosMath.h"
#include "eosTime.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosTask.h"
#include "Services/DigInput/eosDigInputService.h"
#include "eos_diginput_inputs.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::DigInputService::DigInputService():
    Service(),
	_inputChangedEvent {nullptr},
	_beforeScanEvent {nullptr},
    _scanPeriod {_minScanPeriod} {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el periode d'escaneig.
/// \param    scanPeriod: El period en milisegons.
///
void eos::DigInputService::setScanPeriod(
    eos::Time scanPeriod) {

    _scanPeriod = Math::max(scanPeriod, _minScanPeriod);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event quant canvia l'estat d'una entrada.
/// \param    input: L'entrada.
///
void eos::DigInputService::onInputChanged(
    eos::DigInput *input) {

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
void eos::DigInputService::beforeScan() {

	if (_beforeScanEvent != nullptr)
		_beforeScanEvent->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event que motifica la inicialitzacio del servei.
/// \param    args: Parametres d'inicialitzacio.
///
void eos::DigInputService::raiseInitializeNotificationEvent(
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
eos::DigInput * eos::DigInputService::addInput(
	eos::PinDriver *drv,
	uint32_t tag) {

    auto input = new Input(drv, tag);

    rtos::CriticalSection::enter();
	_inputs.pushFront(input);
    rtos::CriticalSection::exit();

    return input;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'entrada amb el tag especificat.
/// \param    tag: El tag de l'entrada a buscar.
/// \return   L'entrada, o nullptr si no la troba.
///
eos::DigInput *eos::DigInputService::getInput(
	uint32_t tag) const {

	eos::DigInput *result = nullptr;

	rtos::CriticalSection::enter();

	for (auto input: _inputs)
		if (input->getTag() == tag) {
			result = input;
			break;
		}

	rtos::CriticalSection::exit();

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void eos::DigInputService::onInitialize(
	ServiceParams &params) {

	params.name = _serviceName;
	params.priority = _servicePriority;
	params.stackDepth = _serviceStackDepth;

	raiseInitializeNotificationEvent(&params);
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei
///
void eos::DigInputService::onExecute() {

    while (!stopSignal()) {

		rtos::Task::delayUntil(_scanPeriod);

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
bool eos::DigInputService::read(
    const eos::DigInput *input) const {

    rtos::CriticalSection::enter();

    auto inp = static_cast<const Input*>(input);
    auto value = inp->getValue();

    rtos::CriticalSection::exit();

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de pulsos de l'entrada.
/// \param    input: La entrada.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
uint32_t eos::DigInputService::getEdges(
	eos::DigInput *input,
	bool clear) const {

    rtos::CriticalSection::enter();

    auto inp = static_cast<Input*>(input);
    auto edges = inp->getCount(clear);

    rtos::CriticalSection::exit();

    return edges;
}
