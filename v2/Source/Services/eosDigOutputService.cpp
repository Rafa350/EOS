#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigOutputService.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"
#include "osal/osalKernel.h"


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
/// \brief Constructor.
/// \param pApplication: L'aplicacio on afeigir el servei.
///
DigOutputService::DigOutputService(
    Application *pApplication):
    
    DigOutputService(pApplication, defaultConfiguration) {
    
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: L'aplicacio on afeigir el servei..
/// \param configuration: Parametres de configuracio.
///
DigOutputService::DigOutputService(
    Application *pApplication,
    const DigOutputServiceConfiguration &configuration):

    Service(pApplication, configuration.serviceConfiguration) {

    //timer = pInfo->timer;
	timer = HAL_TMR_TIMER_2;
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    // Elimina totes les sortides
    //
    removeOutputs();
}


/// ----------------------------------------------------------------------
/// \brief Afegeig una sortida al servei.
/// \param pOutput: La sortida a afeigir.
///
void DigOutputService::addOutput(
    DigOutput *pOutput) {

    // Precondicions
    //
    eosAssert(pOutput != nullptr);
    eosAssert(pOutput->pService == nullptr);

    outputs.add(pOutput);
    pOutput->pService = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina una sortida del servei.
/// \param pOutput: La sortida a eliminar.
///
void DigOutputService::removeOutput(
    DigOutput *pOutput) {

    // Precondicions
    //
    eosAssert(pOutput != nullptr);
    eosAssert(pOutput->pService == this);

    outputs.remove(pOutput);
    pOutput->pService = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Elimina totes les sortides del servei.
///
void DigOutputService::removeOutputs() {
    
    while (!outputs.isEmpty())
        outputs.remove(outputs.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el servei.
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
	tmrInfo.pIrqCall = timerInterrupt;
	tmrInfo.pIrqParams = this;
	halTMRInitialize(&tmrInfo);

    // Inicialitza les sortides
    //
    for (DigOutputListIterator it(outputs); it.hasNext(); it.next())
        it.current()->initialize();

    // Inicia el temporitzador
    //
    halTMRStartTimer(timer);
    
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Bucle de proces del servei.
///
void DigOutputService::onTask() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa el timeout del temporitzador.
///
void DigOutputService::timeOut() {

    for (DigOutputListIterator it(outputs); it.hasNext(); it.next())
        it.current()->timeOut();
}


/// ----------------------------------------------------------------------
/// \brief Captura la interrupcio del temporitzador.
///
void DigOutputService::timerInterrupt(
	TMRTimer timer,
	void *pParam) {

    // Precondicions
    //
    eosAssert(pParam != nullptr);

	DigOutputService *pService = reinterpret_cast<DigOutputService*>(pParam);
    eosAssert(pService != nullptr);
	pService->timeOut();
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pService: El servei al que s'asignara la sortida.
/// \param configuration: Parametres de configuracio.
///
DigOutput::DigOutput(
    DigOutputService *pService,
    const DigOutputConfiguration &configuration):

    pService(nullptr),
    state(State::Idle),
	delayCnt(0),
	widthCnt(0) {

    if (pService != nullptr)
        pService->addOutput(this);

    port = configuration.port;
    pin = configuration.pin;
    options =
        (configuration.openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (configuration.initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::~DigOutput() {

    if (pService != nullptr)
        pService->removeOutput(this);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio de la sortida.
///
void DigOutput::initialize() {

    halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio del temporitzador.
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
/// \brief Obte actual l'estat d'una sortida.
/// \return L'estat de la sortida.
///
bool DigOutput::get() const {

	return halGPIOReadPin(port, pin);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva una sortida.
///
void DigOutput::clear() {

	lockSection();

    halGPIOClearPin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief Activa una sortida
///
void DigOutput::set() {

	lockSection();

    halGPIOSetPin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief Inverteix una sortida.
///
void DigOutput::toggle() {

	lockSection();

    halGPIOTogglePin(port, pin);
    state = State::Idle;

    unlockSection();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls.
/// \param width: Amplada del puls.
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
/// \brief Genera un puls retardat.
/// \param delay: Retard fins a l'inici del puls.
/// \param width: Amplada del puls.
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
