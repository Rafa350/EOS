#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlINT.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \param    settings: Configuration parameters.
///
DigOutputService::DigOutputService(
    Application *application):

	Service(application),
	_commandQueue(_commandQueueSize) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    while (!_outputs.isEmpty())
    	delete _outputs.peekBack();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
/// \remarks  Nomes es poden afeigir sortides, quan el servei no
///           esta inicialitzat.
///
void DigOutputService::addOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (output->_service == nullptr) {
        _outputs.pushBack(output);
        output->_service = this;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
/// \remarks  Nomes es poden eliminar sortides, quan el servei no
///           esta inicialitzat.
///
void DigOutputService::removeOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (output->_service == this) {
        _outputs.removeAt(_outputs.indexOf(output));
        output->_service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
/// \remarks  Nomes es poden eliminar sortides, quan el servei
///           no esta inicialitzat.
///
void DigOutputService::removeOutputs() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    while (!_outputs.isEmpty()) {
        DigOutput *output = _outputs.peekBack();
        _outputs.popBack();
        output->_service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ON
/// \param    output: La sortida.
///
void DigOutputService::set(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::set,
        .output = output
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat OFF
/// \param    output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::clear,
        .output = output
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un valor a la sortida.
/// \param    output: La sortida.
/// \param    value: El valor a asignar.
///
void DigOutputService::write(
    DigOutput *output,
    bool value) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = value ? OpCode::set : OpCode::clear,
        .output = output
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Conmuta l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::toggle,
        .output = output
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned width) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::pulse,
        .output = output,
        .param1 = Math::max(width, _minWidth)
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio retardat.
/// \param    output: La sortida.
///
void DigOutputService::delayedPulse(
    DigOutput *output,
    unsigned delay,
    unsigned width) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::delayedPulse,
        .output = output,
        .param1 = Math::max(delay, _minDelay),
        .param2 = Math::max(width, _minWidth)
    };
    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void DigOutputService::onInitialize() {

    // Inicialitza el servei base.
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle de proces del servei.
/// \param    task: L'objecte Task que executa el servei.
///
void DigOutputService::onTask(
	Task *task) {

    Command cmd;

    // Espera que arribi una comanda
    //
    while (_commandQueue.pop(cmd, unsigned(-1))) {

        // Procesa la comanda
        //
        switch (cmd.opCode) {
            case OpCode::set:
                cmdSet(cmd.output);
                break;

            case OpCode::clear:
                cmdClear(cmd.output);
                break;

            case OpCode::toggle:
                cmdToggle(cmd.output);
                break;

            case OpCode::pulse:
                cmdPulse(cmd.output, cmd.param1);
                break;

            case OpCode::delayedSet:
                cmdDelayedSet(cmd.output, cmd.param1);
                break;

            case OpCode::delayedClear:
                cmdDelayedClear(cmd.output, cmd.param1);
                break;

            case OpCode::delayedToggle:
                cmdDelayedToggle(cmd.output, cmd.param1);
                break;

            case OpCode::delayedPulse:
                cmdDelayedPulse(cmd.output, cmd.param1, cmd.param2);
                break;

            case OpCode::timeOut:
                cmdTimeOut(cmd.param1);
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio 'tick'.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
#if Eos_ApplicationTickEnabled
void DigOutputService::onTick() {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    output: La sortida.
///
void DigOutputService::cmdClear(
    DigOutput *output) {

    eosAssert(output != nullptr);

    output->_gpio.clear();
    output->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::cmdSet(
    DigOutput *output) {

    eosAssert(output != nullptr);

    output->_gpio.set();
    output->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::cmdToggle(
    DigOutput *output) {

    eosAssert(output != nullptr);

    output->_gpio.toggle();
    output->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::cmdPulse(
    DigOutput *output,
    unsigned width) {

    eosAssert(output != nullptr);

    if (output->_state == DigOutput::State::idle)
        output->_gpio.toggle();
    output->_state = DigOutput::State::pulse;
    output->_widthCnt = width;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedSet(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

    output->_state = DigOutput::State::delayedSet;
    output->_delayCnt = delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedClear(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

    output->_state = DigOutput::State::delayedClear;
    output->_delayCnt = delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedToggle(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

    output->_state = DigOutput::State::delayedToggle;
    output->_delayCnt = delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    width: L'amplada del puls.
///
void DigOutputService::cmdDelayedPulse(
    DigOutput *output,
    unsigned delay,
    unsigned width) {

    eosAssert(output != nullptr);

    output->_state = DigOutput::State::delayedPulse;
    output->_delayCnt = delay;
    output->_widthCnt = width;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'timeOut'
/// \param    time: El interval de temps.
///
void DigOutputService::cmdTimeOut(
    unsigned time) {

    for (auto it = _outputs.begin(); it != _outputs.end(); it++) {

        DigOutput *output = *it;

      	switch (output->_state) {
            case DigOutput::State::pulse:
                if (output->_widthCnt <= time) {
                    output->_gpio.toggle();
                    output->_state = DigOutput::State::idle;
                }
                else
                    output->_widthCnt -= time;
                break;

            case DigOutput::State::delayedSet:
            case DigOutput::State::delayedClear:
            case DigOutput::State::delayedToggle:
            case DigOutput::State::delayedPulse:
                if (output->_delayCnt <= time) {
                    switch (output->_state) {
                        case DigOutput::State::delayedSet:
                            output->_gpio.set();
                            output->_state = DigOutput::State::idle;
                            break;

                        case DigOutput::State::delayedClear:
                            output->_gpio.clear();
                            output->_state = DigOutput::State::idle;
                            break;

                        case DigOutput::State::delayedToggle:
                            output->_gpio.toggle();
                            output->_state = DigOutput::State::idle;
                            break;

                        case DigOutput::State::delayedPulse:
                            output->_gpio.toggle();
                            output->_state = DigOutput::State::pulse;
                            break;

                        default:
                            break;
                    }
                }
                else
                    output->_delayCnt -= time;
                break;

            default:
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temportitzador
/// \param    event: L'event que ha generat la interrupcio.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigOutputService::tmrInterruptFunction() {

    Command cmd = {
        .opCode = OpCode::timeOut,
        .param1 = 1
    };
    _commandQueue.pushISR(cmd);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei al que s'asignara la sortida.
/// \param    gpio: El GPIO.
///
DigOutput::DigOutput(
    DigOutputService *service,
    const htl::GPIOAdapter &gpio):

    _service(nullptr),
    _gpio(gpio),
    _state(State::idle),
	_delayCnt(0),
	_widthCnt(0) {

    if (service != nullptr)
        service->addOutput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigOutput::~DigOutput() {

    if (_service != nullptr)
        _service->removeOutput(this);
}
