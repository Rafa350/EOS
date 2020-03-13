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
/// \param    timer: El temporitzador.
///
DigOutputService::DigOutputService(
    Application *application,
    TMRTimer timer):

    commandQueue(10),
    timer(timer),
    Service(application) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    while (!outputs.isEmpty()) {
    	DigOutput *output = outputs.getFirst();
    	removeOutput(output);
    	delete output;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
///
void DigOutputService::addOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->service == nullptr);

    outputs.add(output);
    output->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
///
void DigOutputService::removeOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->service == this);

    outputs.remove(output);
    output->service = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
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
    
    Command cmd;
    
    cmd.opCode = OpCode::set;
    cmd.output = output;
    commandQueue.put(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat OFF
/// \param    outout: La sortida.
///
void DigOutputService::clear(
    DigOutput* output) {
    
    Command cmd;
    
    cmd.opCode = OpCode::clear;
    cmd.output = output;
    commandQueue.put(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Conmuta l'estat de la sortida.
/// \param    outout: La sortida.
///
void DigOutputService::toggle(
    DigOutput* output) {
    
    Command cmd;
    
    cmd.opCode = OpCode::toggle;
    cmd.output = output;
    commandQueue.put(cmd, unsigned(-1));
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
    tmrInfo.period = (40000000L / 64L / 1000L) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000L) - 1; // 1MHz
    tmrInfo.period = 1000 - 1; // 1ms
	tmrInfo.irqPriority = 1;
	tmrInfo.irqSubPriority = 0;
#else
#error CPU no soportada
#endif
    
	tmrInfo.irqCallback = timerInterrupt;
	tmrInfo.irqParam = this;
	halTMRInitialize(&tmrInfo);

    // Inicialitza les sortides
    //
    for (auto output: outputs)
        output->initialize();

    // Inicia el temporitzador
    //
    halTMRStartTimer(timer);

    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle de proces del servei.
///
void DigOutputService::onTask() {

    while (true) {
        Command cmd;
        while (commandQueue.get(cmd, unsigned(-1))) {
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
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    outpout: La sortida.
///
void DigOutputService::cmdClear(
    DigOutput* output) {
    
    halGPIOClearPin(output->port, output->pin);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    outpout: La sortida.
///
void DigOutputService::cmdSet(
    DigOutput* output) {

    halGPIOSetPin(output->port, output->pin);   
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    outpout: La sortida.
///
void DigOutputService::cmdToggle(
    DigOutput* output) {

    halGPIOTogglePin(output->port, output->pin);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el timeout del temporitzador.
///
void DigOutputService::timeOut() {

    for (DigOutputListIterator it(outputs); it.hasNext(); it.next()) {
        DigOutput *output = it.getCurrent();
        output->timeOut();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Captura la interrupcio del temporitzador.
///
void DigOutputService::timerInterrupt(
	TMRTimer timer,
	void *param) {

    eosAssert(param != nullptr);

	DigOutputService* service = reinterpret_cast<DigOutputService*>(param);
    eosAssert(service != nullptr);
	service->timeOut();
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
    state(State::Idle),
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


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio de la sortida.
///
void DigOutput::initialize() {

    if (((options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_OUTPUT_OD) ||
        ((options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_OUTPUT_PP)) {
        options &= ~HAL_GPIO_MODE_mask;
        options |= HAL_GPIO_MODE_OUTPUT_PP;
    }
    halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
///
void DigOutput::timeOut() {

	switch (state) {
		case State::Pulse:
			if (widthCnt > 0) {
				widthCnt--;
				if (widthCnt == 0) {
					halGPIOTogglePin(port, pin);
					state = State::Idle;
				}
			}
			break;

		case State::DelayedPulse:
			if (delayCnt > 0) {
				delayCnt--;
				if (delayCnt == 0) {
					halGPIOTogglePin(port, pin);
					state = State::Pulse;
				}
			}
			break;

        default:
            break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte actual l'estat d'una sortida.
/// \return   L'estat de la sortida.
///
bool DigOutput::get() const {

	return halGPIOReadPin(port, pin);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva una sortida.
///
/*void DigOutput::clear() {

	Task::enterCriticalSection();

    halGPIOClearPin(port, pin);
    state = State::Idle;

    Task::exitCriticalSection();
}
*/

/// ----------------------------------------------------------------------
/// \brief    Activa una sortida
///
/*void DigOutput::set() {

	Task::enterCriticalSection();

    halGPIOSetPin(port, pin);
    state = State::Idle;

    Task::exitCriticalSection();
}
*/

/// ----------------------------------------------------------------------
/// \brief    Inverteix una sortida.
///
/*void DigOutput::toggle() {

	Task::enterCriticalSection();

    halGPIOTogglePin(port, pin);
    state = State::Idle;

    Task::exitCriticalSection();
}
*/

/// ----------------------------------------------------------------------
/// \brief    Genera un puls.
/// \param    width: Amplada del puls.
///
void DigOutput::pulse(
	unsigned width) {

	Task::enterCriticalSection();

	if (state == State::Idle)
        halGPIOTogglePin(port, pin);

	widthCnt = width;
    state = State::Pulse;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls retardat.
/// \param    delay: Retard fins a l'inici del puls.
/// \param    width: Amplada del puls.
///
void DigOutput::delayedPulse(
	unsigned delay,
	unsigned width) {

	Task::enterCriticalSection();

	delayCnt = delay;
    widthCnt = width;
    state = State::DelayedPulse;

    Task::exitCriticalSection();
}
