#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "OSAL/osalKernel.h"
#include "Services/eosDigOutputService.h"


using namespace eos;


static DigOutputServiceConfiguration defaultConfiguration = {
    .serviceConfiguration = {
        .serviceName = "DigOutputService",
        .stackSize = 512,
        .priority = TaskPriority::normal
    }
};


#define lockSection()    osalEnterCritical()
#define unlockSection()  osalExitCritical()


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio on afeigir el servei.
///
DigOutputService::DigOutputService(
    Application *application):
    
    DigOutputService(application, defaultConfiguration) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio on afeigir el servei..
/// \param    configuration: Parametres de configuracio.
///
DigOutputService::DigOutputService(
    Application *application,
    const DigOutputServiceConfiguration &configuration):

    Service(application, configuration.serviceConfiguration) {

    //timer = pInfo->timer;
	timer = HAL_TMR_TIMER_2;
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

    // Precondicions
    //
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

    // Precondicions
    //
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

}


/// ----------------------------------------------------------------------
/// \brief    Procesa el timeout del temporitzador.
///
void DigOutputService::timeOut() {

    for (auto output: outputs)
        output->timeOut();
}


/// ----------------------------------------------------------------------
/// \brief    Captura la interrupcio del temporitzador.
///
void DigOutputService::timerInterrupt(
	TMRTimer timer,
	void *pParam) {

    // Precondicions
    //
    eosAssert(pParam != nullptr);

	DigOutputService *service = reinterpret_cast<DigOutputService*>(pParam);
    eosAssert(service != nullptr);
	service->timeOut();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei al que s'asignara la sortida.
/// \param    configuration: Parametres de configuracio.
///
DigOutput::DigOutput(
    DigOutputService *service,
    const DigOutputConfiguration &configuration):

    service(nullptr),
    state(State::Idle),
	delayCnt(0),
	widthCnt(0) {

    if (service != nullptr)
        service->addOutput(this);

    port = configuration.port;
    pin = configuration.pin;
    options =
        (configuration.openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (configuration.initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
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
void DigOutput::clear() {

	lockSection();

    halGPIOClearPin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief    Activa una sortida
///
void DigOutput::set() {

	lockSection();

    halGPIOSetPin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix una sortida.
///
void DigOutput::toggle() {

	lockSection();

    halGPIOTogglePin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls.
/// \param    width: Amplada del puls.
///
void DigOutput::pulse(
	unsigned width) {

	lockSection();

	if (state == State::Idle)
        halGPIOTogglePin(port, pin);

	widthCnt = width;
    state = State::Pulse;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls retardat.
/// \param    delay: Retard fins a l'inici del puls.
/// \param    width: Amplada del puls.
///
void DigOutput::delayedPulse(
	unsigned delay,
	unsigned width) {

	lockSection();

	delayCnt = delay;
    widthCnt = width;
    state = State::DelayedPulse;

    unlockSection();
}
