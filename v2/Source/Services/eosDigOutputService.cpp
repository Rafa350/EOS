#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio on afeigir el servei.
/// \param    initParams: Parametres d'inicialitzacio.
///
DigOutputService::DigOutputService(
    Application* application,
    const DigOutputService::InitParams& initParams):

    commandQueue(commandQueueSize),
    timer(initParams.timer),
    period(initParams.period),
    Service(application) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    while (!outputs.isEmpty()) {
    	DigOutput* output = outputs.getFirst();
    	removeOutput(output);
    	delete output;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
/// \remarks  Nomes es poden afeigir sortides, quan el servei no 
///           esta inicialitzat.
///
void DigOutputService::addOutput(
    DigOutput* output) {

    eosAssert(output != nullptr);
    eosAssert(output->service == nullptr);

    if (!isInitialized())
        if (output->service == nullptr) {    
            outputs.add(output);
            output->service = this;
        }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
/// \remarks  Nomes es poden eliminar sortides, quan el servei no 
///           esta inicialitzat.
///
void DigOutputService::removeOutput(
    DigOutput* output) {

    eosAssert(output != nullptr);
    eosAssert(output->service == this);

    if (!isInitialized())
        if (output->service == this) {
            outputs.remove(output);
            output->service = nullptr;
        }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
/// \remarks  Nomes es poden eliminar sortides, quan el servei 
///           no esta inicialitzat.
///
void DigOutputService::removeOutputs() {

    while (!outputs.isEmpty())
        removeOutput(outputs.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ON
/// \param    output: La sortida.
///
void DigOutputService::set(
    DigOutput* output) {
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);
    
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
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);

    Command cmd;
    cmd.opCode = OpCode::clear;
    cmd.output = output;
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Asigna un valor a la sortida.
/// \param    output: La sortida.
/// \param    value: El valor a asignar.
///
void DigOutputService::write(
    DigOutput* output,
    bool value) {
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);

    Command cmd;
    cmd.opCode = value ? OpCode::set : OpCode::clear;
    cmd.output = output;
    commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Conmuta l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput* output) {
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);

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
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);

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
    
    eosAssert(output != nullptr);
    eosAssert(output->service == this);

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
    
    // Inicialitza el temporitzador
    //
	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = timer;
#if defined(EOS_PIC32MX)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.period = ((80000 * period) / 64) - 1; 
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000L) - 1; // 1MHz
    tmrInfo.period = (1000 * period) - 1; 
	tmrInfo.irqPriority = 1;
	tmrInfo.irqSubPriority = 0;
#else
//#error CPU no soportada
#endif   
	tmrInfo.isrFunction = isrTimerFunction;
	tmrInfo.isrParams = this;
	halTMRInitialize(&tmrInfo);
    halTMRStartTimer(timer);

    // Inicialitza el servei base.
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void DigOutputService::onTerminate() {
    
    // Desactiva el temporitzador
    //
    halTMRStopTimer(timer);
    
    // Finalitza el servei base
    //
    Service::onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle de proces del servei.
///
void DigOutputService::onTask() {

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


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio 'tick'.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigOutputService::onTick() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    output: La sortida.
///
void DigOutputService::cmdClear(
    DigOutput* output) {
    
    halGPIOClearPin(output->port, output->pin);   
    output->state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::cmdSet(
    DigOutput* output) {

    halGPIOSetPin(output->port, output->pin);      
    output->state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::cmdToggle(
    DigOutput* output) {

    halGPIOTogglePin(output->port, output->pin);   
    output->state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::cmdPulse(
    DigOutput* output,
    unsigned width) {
    
    if (output->state == DigOutput::State::idle)
        halGPIOTogglePin(output->port, output->pin);   
    output->state = DigOutput::State::pulse;
    output->widthCnt = width;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedSet(
    DigOutput* output, 
    unsigned delay) {
    
    output->state = DigOutput::State::delayedSet;
    output->delayCnt = delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedClear(
    DigOutput* output, 
    unsigned delay) {
    
    output->state = DigOutput::State::delayedClear;
    output->delayCnt = delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::cmdDelayedToggle(
    DigOutput* output, 
    unsigned delay) {

    output->state = DigOutput::State::delayedToggle;
    output->delayCnt = delay;
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
    
    output->state = DigOutput::State::delayedPulse;
    output->delayCnt = delay;
    output->widthCnt = width;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'timeOut'
/// \param    time: El interval de temps.
///
void DigOutputService::cmdTimeOut(
    unsigned time) {

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
}


/// ----------------------------------------------------------------------
/// \brief    Captura la interrupcio del temporitzador.
///
void DigOutputService::isrTimerFunction(
	TMRTimer timer,
	void *param) {

	DigOutputService* service = static_cast<DigOutputService*>(param);
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
/// \param    initParams: Parametres d'inicialitzacio.
///
DigOutput::DigOutput(
    DigOutputService* service,
    const DigOutput::InitParams& initParams):

    service(nullptr),
    port(initParams.port),
    pin(initParams.pin),
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
