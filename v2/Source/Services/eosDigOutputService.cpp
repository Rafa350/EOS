#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosDigOutputService.h"
#include "System/eosMath.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio on afeigir el servei.
/// \param    timer: El temporitzador.
///
DigOutputService::DigOutputService(
    Application* application,
    TMRTimer timer):

    commandQueue(commandQueueSize),
    timer(timer),
    Service(application) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    Task::enterCriticalSection();
    
    while (!outputs.isEmpty()) {
    	DigOutput* output = outputs.getFirst();
    	removeOutput(output);
    	delete output;
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
///
void DigOutputService::addOutput(
    DigOutput* output) {

    eosAssert(output != nullptr);

    Task::enterCriticalSection();
    
    if (output->service == nullptr) {    
        outputs.add(output);
        output->service = this;
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
///
void DigOutputService::removeOutput(
    DigOutput* output) {

    eosAssert(output != nullptr);

    Task::enterCriticalSection();
    
    if (output->service == this) {
        outputs.remove(output);
        output->service = nullptr;
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
///
void DigOutputService::removeOutputs() {

    Task::enterCriticalSection();
    
    while (!outputs.isEmpty())
        removeOutput(outputs.getFirst());
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ON
/// \param    output: La sortida.
///
void DigOutputService::set(
    DigOutput* output) {
    
    Command cmd;
    cmd.opCode = OpCode::set;
    cmd.output = output;
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat OFF
/// \param    output: La sortida.
///
void DigOutputService::clear(
    DigOutput* output) {
    
    Command cmd;
    cmd.opCode = OpCode::clear;
    cmd.output = output;
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Conmuta l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput* output) {
    
    Command cmd;
    cmd.opCode = OpCode::toggle;
    cmd.output = output;
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
///
void DigOutputService::pulse(
    DigOutput* output,
    unsigned width) {
    
    Command cmd;
    cmd.opCode = OpCode::pulse;
    cmd.output = output;
    cmd.param1 = Math::max(width, minWidth);
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio retardat.
/// \param    output: La sortida.
///
void DigOutputService::delayedPulse(
    DigOutput* output,
    unsigned delay,
    unsigned width) {
    
    Command cmd;
    cmd.opCode = OpCode::delayedPulse;
    cmd.output = output;
    cmd.param1 = Math::max(delay, minDelay);
    cmd.param2 = Math::max(width, minWidth);
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void DigOutputService::onInitialize() {

    // Configura el temporitzador
    //
	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = timer;
#if defined(EOS_PIC32MX)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.period = (80000000L / 64L / 1000L) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000L) - 1; // 1MHz
    tmrInfo.period = 1000 - 1; // 1ms
	tmrInfo.irqPriority = 1;
	tmrInfo.irqSubPriority = 0;
#else
//#error CPU no soportada
#endif
    
	tmrInfo.irqCallback = timerInterrupt;
	tmrInfo.irqParam = this;
	halTMRInitialize(&tmrInfo);

    // Inicialitza les sortides
    //
    for (DigOutputListIterator it(outputs); it.hasNext(); it.next()) {
        DigOutput* output = it.getCurrent();
        
        if (((output->options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_OUTPUT_OD) ||
            ((output->options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_OUTPUT_PP)) {
            output->options &= ~HAL_GPIO_MODE_mask;
            output->options |= HAL_GPIO_MODE_OUTPUT_PP;
        }
        halGPIOInitializePin(output->port, output->pin, output->options, HAL_GPIO_AF_NONE);
    }

    // Inicia el temporitzador
    //
    halTMRStartTimer(timer);

    // Inicialitza el servei base.
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle de proces del servei.
///
void DigOutputService::onTask() {

    while (true) {
        Command cmd;
        while (commandQueue.pop(cmd, unsigned(-1))) {
                      
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
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    output: La sortida.
///
void DigOutputService::cmdClear(
    DigOutput* output) {
    
    Task::enterCriticalSection();
    
    halGPIOClearPin(output->port, output->pin);   
    output->state = DigOutput::State::idle;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::cmdSet(
    DigOutput* output) {

    Task::enterCriticalSection();
    
    halGPIOSetPin(output->port, output->pin);      
    output->state = DigOutput::State::idle;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::cmdToggle(
    DigOutput* output) {

    Task::enterCriticalSection();
    
    halGPIOTogglePin(output->port, output->pin);   
    output->state = DigOutput::State::idle;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::cmdPulse(
    DigOutput* output,
    unsigned width) {
    
    Task::enterCriticalSection();
    
    if (output->state == DigOutput::State::idle)
        halGPIOTogglePin(output->port, output->pin);   
    output->state = DigOutput::State::pulse;
    output->widthCnt = width;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedSet(
    DigOutput* output, 
    unsigned delay) {
    
    Task::enterCriticalSection();
    
    output->state = DigOutput::State::delayedSet;
    output->delayCnt = delay;
    
    Task::exitCriticalSection();
    
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedClear(
    DigOutput* output, 
    unsigned delay) {
    
    Task::enterCriticalSection();
    
    output->state = DigOutput::State::delayedClear;
    output->delayCnt = delay;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedToggle(
    DigOutput* output, 
    unsigned delay) {
    
    Task::enterCriticalSection();
    
    output->state = DigOutput::State::delayedToggle;
    output->delayCnt = delay;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    width: L'amplada del puls.
///
void DigOutputService::cmdDelayedPulse(
    DigOutput* output,
    unsigned delay,
    unsigned width) {
    
    Task::enterCriticalSection();
    
    output->state = DigOutput::State::delayedPulse;
    output->delayCnt = delay;
    output->widthCnt = width;
    
    Task::exitCriticalSection();
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'timeOut'
/// \param    time: El interval de temps.
///
void DigOutputService::cmdTimeOut(
    unsigned time) {

    Task::enterCriticalSection();    
    
    for (DigOutputListIterator it(outputs); it.hasNext(); it.next()) {
        
        DigOutput *output = it.getCurrent();

      	switch (output->state) {
            case DigOutput::State::pulse:
                if (output->widthCnt <= time) {
                    halGPIOTogglePin(output->port, output->pin);
                    output->state = DigOutput::State::idle;
                }
                else
                    output->widthCnt -= time;
                break;

            case DigOutput::State::delayedSet:
            case DigOutput::State::delayedClear:
            case DigOutput::State::delayedToggle:
            case DigOutput::State::delayedPulse:
                if (output->delayCnt <= time) {
                    switch (output->state) {
                        case DigOutput::State::delayedSet:
                            halGPIOSetPin(output->port, output->pin);
                            output->state = DigOutput::State::idle;
                            break;

                        case DigOutput::State::delayedClear:
                            halGPIOClearPin(output->port, output->pin);
                            output->state = DigOutput::State::idle;
                            break;

                        case DigOutput::State::delayedToggle:
                            halGPIOTogglePin(output->port, output->pin);
                            output->state = DigOutput::State::idle;
                            break;
                            
                        case DigOutput::State::delayedPulse:
                            halGPIOTogglePin(output->port, output->pin);
                            output->state = DigOutput::State::pulse;
                            break;
                            
                        default:
                            break;
                    }
                }
                else
                    output->delayCnt -= time;
                break;

            default:
                break;
        }
    }
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Captura la interrupcio del temporitzador.
///
void DigOutputService::timerInterrupt(
	TMRTimer timer,
	void *param) {

	DigOutputService* service = reinterpret_cast<DigOutputService*>(param);
    if (service != nullptr) {
        Command cmd;
        cmd.opCode = OpCode::timeOut;
        cmd.param1 = 1;
        service->commandQueue.pushISR(cmd);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei al que s'asignara la sortida.
/// \param    port: El port.
/// \param    pin: El pin.
/// \param    options: Opcions del pin.
///
DigOutput::DigOutput(
    DigOutputService* service,
    GPIOPort port,
    GPIOPin pin,
    GPIOOptions options) :

    service(nullptr),
    port(port),
    pin(pin),
    options(options),
    state(State::idle),
	delayCnt(0),
	widthCnt(0) {

    if (service != nullptr)
        service->addOutput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigOutput::~DigOutput() {

    if (service != nullptr)
        service->removeOutput(this);
}
