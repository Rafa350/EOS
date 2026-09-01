module;


#include "eos.h"
#include "eosEvents.h"
#include "eosTime.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosTask.h"


module Eos.Services.DigInput;


import Eos.Math;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::DigInputService::DigInputService():
    Service(),
    _scanPeriod {_minScanPeriod} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
eos::DigInputService::~DigInputService() {

    rtos::CriticalSection::enter();

	while (!_inputs.empty()) {
		auto input = _inputs.front();
		_inputs.remove(input);
		delete input;
	}

	rtos::CriticalSection::exit();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna i habilita l'event 'InputChanged'
/// \param    event: El event.
///
void eos::DigInputService::enableInputChangedEvent(
	IInputChangedEvent &event) {

	_inputChangedEventRaiser.enable(event);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita l'event 'InputChanged'
///
void eos::DigInputService::disableInputChangedEvent() {

	_inputChangedEventRaiser.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna i habilita l'event 'beforeScan'
/// \param    event: El event.
///
void eos::DigInputService::enableBeforeScanEvent(
	IBeforeScanEvent &event) {

	_beforeScanEventRaiser.enable(event);
}


/// ----------------------------------------------------------------------
/// \brief    Desabilita l'event 'BeforeScan'
///
void eos::DigInputService::disableBeforeScanEvent() {

	_beforeScanEventRaiser.disable();
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
    eos::DigInputImpl *input) {

	if (_inputChangedEventRaiser) {

    	InputChangedEventArgs args = {
   			.input {input},
			.value {input->getValue()}
    	};

    	_inputChangedEventRaiser(this, &args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event abans del inici de l'exploracio de
///           les entrades.
///
void eos::DigInputService::beforeScan() {

	if (_beforeScanEventRaiser)
		_beforeScanEventRaiser(this, nullptr);
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

    auto input = new DigInputImpl(drv, tag);

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
			auto inp = static_cast<DigInputImpl*>(input);

			// Escaneja una entrada i si hi canvis,
			// els notifica.
			//
			if (inp->scan())
				onInputChanged(static_cast<DigInputImpl*>(input));
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

    auto inp = static_cast<const DigInputImpl*>(input);
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

    auto inp = static_cast<DigInputImpl*>(input);
    auto edges = inp->getCount(clear);

    rtos::CriticalSection::exit();

    return edges;
}
