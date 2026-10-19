module Eos.Services.DigInput;

import Eos.Events;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.Ticks;
import Eos.Types;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
DigInputService::DigInputService():
    Service(),
    _scanPeriod {_minScanPeriod} {
}


/// ---------------------------------------------------------------------------
/// @brief    Destructor.
///
DigInputService::~DigInputService() {

    CriticalSection::enter();

	while (!_inputs.isEmpty()) {
		auto input = _inputs.getFirst();
		_inputs.remove(input);
		delete input;
	}

	CriticalSection::exit();
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna i habilita l'event 'InputChanged'
/// @param    event: El event.
///
void DigInputService::enableInputChangedEvent(
	IInputChangedEvent &event) {

	_inputChangedEventRaiser.enable(event);
}


/// ---------------------------------------------------------------------------
/// @brief    Desabilita l'event 'InputChanged'
///
void DigInputService::disableInputChangedEvent() {

	_inputChangedEventRaiser.disable();
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna i habilita l'event 'beforeScan'
/// @param    event: El event.
///
void DigInputService::enableBeforeScanEvent(
	IBeforeScanEvent &event) {

	_beforeScanEventRaiser.enable(event);
}


/// ---------------------------------------------------------------------------
/// @brief    Desabilita l'event 'BeforeScan'
///
void DigInputService::disableBeforeScanEvent() {

	_beforeScanEventRaiser.disable();
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el periode d'escaneig.
/// @param    scanPeriod: El period en milisegons.
///
void DigInputService::setScanPeriod(
    Ticks scanPeriod) {

    _scanPeriod = Math::max(scanPeriod, _minScanPeriod);
}


/// ---------------------------------------------------------------------------
/// @brief    Genera un event quant canvia l'estat d'una entrada.
/// @param    input: L'entrada.
///
void DigInputService::onInputChanged(
    DigInputImpl *input) {

	if (_inputChangedEventRaiser) {

    	InputChangedEventArgs args = {
   			.input {input},
			.value {input->getValue()}
    	};

    	_inputChangedEventRaiser(this, &args);
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Genera un event abans del inici de l'exploracio de
///           les entrades.
///
void DigInputService::beforeScan() {

	if (_beforeScanEventRaiser)
		_beforeScanEventRaiser(this, nullptr);
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix una entrada el servei.
/// @param    drv: El driver del pin.
/// @param    tag: Etiqueta opcional
/// \return   L'entrada.
///
DigInput * eos::DigInputService::addInput(
	PinDriver *drv,
	UInt32 tag) {

    auto input = new DigInputImpl(drv, tag);

    CriticalSection::enter();
	_inputs.pushFront(input);
    CriticalSection::exit();

    return input;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'entrada amb el tag especificat.
/// @param    tag: El tag de l'entrada a buscar.
/// @return   L'entrada, o nullptr si no la troba.
///
DigInput *DigInputService::getInput(
	UInt32 tag) const {

	DigInput *result = nullptr;

	CriticalSection::enter();

	for (auto input: _inputs)
		if (input->getTag() == tag) {
			result = input;
			break;
		}

	CriticalSection::exit();

	return result;
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza els parametres del servei.
/// @param    params: Els parametres.
///
void DigInputService::onInitialize(
	ServiceParams &params) {

	params.name = _serviceName;
	params.priority = _servicePriority;
	params.stackDepth = _serviceStackDepth;
}


/// ---------------------------------------------------------------------------
/// @brief    Tasca del servei
///
void DigInputService::onExecute() {

    while (!stopSignal()) {

		Task::delayUntil(_scanPeriod);

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


/// ---------------------------------------------------------------------------
/// @brief    Obte l'estat de l'entrada.
/// @param    input: La entrada.
/// \return   True si esta en estat ACTIVE, false en cas contrari.
///
bool DigInputService::read(
    const DigInput *input) const {

    CriticalSection::enter();

    auto inp = static_cast<const DigInputImpl*>(input);
    auto value = inp->getValue();

    CriticalSection::exit();

    return value;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el contador de pulsos de l'entrada.
/// @param    input: La entrada.
/// @param    clear: Indica si cal borrar el contador.
/// \return   El nombre de pulsos fins al moment de la lectura.
///
UInt32 DigInputService::getEdges(
	DigInput *input,
	bool clear) const {

    CriticalSection::enter();

    auto inp = static_cast<DigInputImpl*>(input);
    auto edges = inp->getCount(clear);

    CriticalSection::exit();

    return edges;
}
