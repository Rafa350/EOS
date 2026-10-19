module Eos.Services.DigOutput;

import Eos.System.Core.CriticalSection;
import Eos.Types;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
DigOutputService::DigOutputService():
	_messageQueue {_messageQueueSize},
	_scanPeriod {_minScanPeriod} {

}


/// ---------------------------------------------------------------------------
/// @brief    Crea i afegeix una sortida.
/// @param    pinDrv: El driver del pin
/// @param    tag: Etiqueta opcional
/// @return   La sortida.
///
DigOutput* eos::DigOutputService::addOutput(
    PinDriver *drv,
	UInt32 tag) {

    CriticalSection::enter();

    auto output = new DigOutputImpl(drv, tag);
	_outputs.pushFront(output);

    CriticalSection::exit();

    return output;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la sortida pertany al servei.
/// @param    output: La sortida.
/// @return   True si pertany, false en cas contrari.
///
bool DigOutputService::containsOutput(
	DigOutput *output) const {

	bool result = false;

	if (output != nullptr) {

		CriticalSection::enter();

		result = _outputs.contains(output);

		CriticalSection::exit();
	}

	return result;
}


/// ---------------------------------------------------------------------------
/// @brief    Selecciona el periode s'exploracio.
/// @param    scanPeriod : El valor.
///
void DigOutputService::setScanPeriod(
	Ticks scanPeriod) {

    _scanPeriod = Math::max(scanPeriod, _minScanPeriod);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte la sortida amb el tag especificat.
/// @param    tag: El tag de l'entrada a buscar.
/// @return   La sortida, o nullptr si no la troba.
///
DigOutput *DigOutputService::getOutput(
	UInt32 tag) const {

	DigOutput *result = nullptr;

	CriticalSection::enter();

	for (auto output: _outputs)
		if (output->getTag() == tag) {
			result = output;
			break;
		}

	CriticalSection::exit();

	return result;
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quant la sortida especificada ha canviat el
///           seu valor. Genera un event 'OutputChanged'
/// @param    output: La sortida.
///
void DigOutputService::onOutputChanged(
	DigOutputImpl *output) {

	if (_outputChangedEventRaiser) {

    	OutputChangedEventArgs args = {
			.output {output},
			.value {output->getValue()}
		};

		_outputChangedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Posa la sortida en estat ACTIVE.
/// @param    output: La sortida.
/// @param    blocTime: Temps maxim de bloqueig.
///
void DigOutputService::set(
    DigOutput *output,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::set},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Posa la sortida en estat IDLE.
/// @param    output: La sortida.
/// @param    blockTime: Temps maxim de bloqueig.
///
void DigOutputService::clear(
    DigOutput *output,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::clear},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Inverteix l'estat de la sortida.
/// @param    output: La sortida.
/// @param    blockTime: Temps maxim de bloqueig.
///
void DigOutputService::toggle(
    DigOutput *output,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::toggle},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Asigna l'estat de la sortida.
/// @param    output: La sortida.
/// @param    state: L'estat a asignar.
/// @param    blockTime: Temps maxim de bloqueig.
///
void DigOutputService::write(
    DigOutput *output,
    bool state,
	Ticks blockTime) {

	Message message = {
		.id {state ? MessageID::set : MessageID::clear},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Genera un puls de conmutacio.
/// @param    output: La sortida.
/// @param    width: L'amplada del puls.
/// @param    blockTime: Temps maxim de bloqueig.
///
void DigOutputService::pulse(
    DigOutput *output,
    Ticks pulse,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::pulse},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()},
			.pulse {Math::max(pulse, minPulseWidth)}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Genera un puls de conmutacio retardat.
/// @param    output: La sortida.
/// @param    delay: El retard del puls.
/// @param    pulse: L'amplada del puls.
/// @param    blockTime: Temps maxim de bloqueig.
///
void DigOutputService::delayedPulse(
    DigOutput *output,
    Ticks delay,
    Ticks pulse,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::delayedPulse},
		.output {static_cast<DigOutputImpl*>(output)},
		.timing {
			.now {Ticks::now()},
			.delay {eos::Math::max(delay, minDelay)},
			.pulse {eos::Math::max(pulse, minPulseWidth)}
		}
	};

	_messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Llegeix el valor d'una sortida.
/// @param    output: La sortida.
/// @return   L'estat de la sortida.
///
bool DigOutputService::read(
	DigOutput *output) {

	CriticalSection::enter();

	auto out = static_cast<DigOutputImpl*>(output);
	bool value = out->getValue();

	CriticalSection::exit();

	return value;
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitza els parametres del servei.
/// @param    params: Els parametres.
///
void DigOutputService::onInitialize(
	Service::ServiceParams &params) {

	params.name = _serviceName;
	params.stackDepth = _serviceStackDepth;
	params.priority = _servicePriority;
}


/// ----------------------------------------------------------------------
/// @brief    Tasca del servei.
///
void DigOutputService::onExecute() {

	while (!stopSignal()) {
		Message message;
		while (_messageQueue.pop(message, Ticks::infinite()))
			processMessage(message);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa les accions.
/// @param    message: L'accio.
///
void DigOutputService::processMessage(
	const Message &message) {

    switch (message.id) {
        case MessageID::set:
            processSet(message.output);
            break;

        case MessageID::clear:
            processClear(message.output);
            break;

        case MessageID::toggle:
            processToggle(message.output);
            break;

        case MessageID::pulse:
            processPulse(message.output, message.timing);
            break;

        case MessageID::delayedSet:
            processDelayedSet(message.output, message.timing);
            break;

        case MessageID::delayedClear:
            processDelayedClear(message.output, message.timing);
            break;

        case MessageID::delayedToggle:
            processDelayedToggle(message.output, message.timing);
            break;

        case MessageID::delayedPulse:
            processDelayedPulse(message.output, message.timing);
            break;

        case MessageID::tick:
            processTick();
            break;
    }
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'clear'
/// @param    output: La sortida.
///
void DigOutputService::processClear(
    DigOutputImpl *output) {

	if (output->getValue()) {
		output->clear();
		onOutputChanged(output);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'set'
/// @param    output: La sortida.
///
void DigOutputService::processSet(
    DigOutputImpl *output) {

	if (!output->getValue()) {
		output->set();
		onOutputChanged(output);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'toggle'
/// @param    output: La sortida.
///
void DigOutputService::processToggle(
    DigOutputImpl *output) {

	output->toggle();
	onOutputChanged(output);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'pulse'.
/// @param    output: La sortida.
/// @param    timing: Parametres de temporitzacio.
///
void DigOutputService::processPulse(
    DigOutputImpl *output,
	const Timing &timing) {

	bool oldValue = output->getValue();
	output->pulse(timing.now, timing.pulse);
	if (oldValue != output->getValue())
		onOutputChanged(output);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'delayedSet'.
/// @param    output: La sortida.
/// @param    timing: Parametres de temporitzacio.
///
void DigOutputService::processDelayedSet(
    DigOutputImpl *output,
 	const Timing &timing) {

}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'delayedClear'.
/// @param    output: La sortida.
/// @param    timing: Parametres de temporitzacio.
///
void DigOutputService::processDelayedClear(
    DigOutputImpl *output,
	const Timing &timing) {

}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'delayedToggle'.
/// @param    output: La sortida.
/// @param    timing: Parametres de temporitzacio.
///
void DigOutputService::processDelayedToggle(
    DigOutputImpl *output,
	const Timing &timing) {

}


/// ----------------------------------------------------------------------
/// @brief    Procesa la comanda 'delayedPulse'.
/// @param    output: La sortida.
/// @param    timing: Parametres de temporitzacio.
///
void DigOutputService::processDelayedPulse(
    DigOutputImpl *output,
	const Timing &timing) {

	output->delayedPulse(timing.now, timing.delay, timing.pulse);
}


/// ---------------------------------------------------------------------
/// @brief    Procesa la comanda 'tick'
///
void DigOutputService::processTick() {

	for (auto o: _outputs) {

    	auto output = static_cast<DigOutputImpl*>(o);
		if (output->getState() != DigOutputImpl::State::idle) {

			if (output->tick())
				onOutputChanged(output);
		}
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa la interrupcio del temportitzador
/// \remarks  ATENCIO: Es procesa dins d'una interrupcio.
///
void DigOutputService::tickISR() {

    Message message = {
        .id {MessageID::tick}
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
    _messageQueue.pushISR(message);
}
