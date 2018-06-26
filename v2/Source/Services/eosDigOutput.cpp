#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigOutput.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"
#include "osal/osalTask.h"


using namespace eos;


static const char *serviceName = "DigOutputService";
static const unsigned taskStackSize = 512;
static const TaskPriority taskPriority = TaskPriority::normal;


#define lockSection()    osalEnterCritical()
#define unlockSection()  osalExitCritical()


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: L'aplicacio a la que pertany.
/// \param pInfo: Parametres d'inicialitzacio.
///
DigOutputService::DigOutputService(
    Application *pApplication,
    const DigOutputServiceInitializeInfo *pInfo):

    Service(pApplication, serviceName, taskStackSize, taskPriority) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

    while (outputs.getCount() > 0)
        remove(outputs.getTop());
}


/// ----------------------------------------------------------------------
/// \brief Afegeig una sortida al servei.
/// \param pOutput: La sortida a afeigir.
///
void DigOutputService::add(
    DigOutput *pOutput) {

    eosArgumentIsNotNull(pOutput);

    eosAssert(pOutput != nullptr);
    eosAssert(pOutput->pService == nullptr);

    outputs.add(pOutput);
    pOutput->pService = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina una sortida del servei.
/// \param output: La sortida a eliminar.
///
void DigOutputService::remove(
    DigOutput *pOutput) {

    eosArgumentIsNotNull(pOutput);

    eosAssert(pOutput != nullptr);
    eosAssert(pOutput->pService == this);

    pOutput->pService = nullptr;
	outputs.remove(pOutput);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el servei.
///
void DigOutputService::onSetup() {
    
/*	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = pInfo->timer;
	tmrInfo.pIrqCall = timerInterrupt;
	tmrInfo.pIrqParams = this;
	halTMRInitialize(&tmrInfo);*/

    OutputListIterator iterator(outputs);
    while (iterator.hasNext()) {
        iterator.current()->onSetup();
        iterator.next();
    }
}


/// ----------------------------------------------------------------------
/// \brief Bucle de proces del servei.
///
void DigOutputService::onLoop() {
    
    onTimeOut();
    Task::delay(10);
}


/// ----------------------------------------------------------------------
/// \brief Procesa el timeout del temporitzador.
///
void DigOutputService::onTimeOut() {

    OutputListIterator iterator(outputs);
    while (iterator.hasNext()) {
        iterator.current()->onTimeOut();
        iterator.next();
    }
}


/// ----------------------------------------------------------------------
/// \brief Captura la interrupcio del temporitzador.
///
void DigOutputService::timerInterrupt(
	TMRTimer timer,
	void *pParam) {

    eosAssert(pParam != nullptr);
    
	DigOutputService *pService = reinterpret_cast<DigOutputService*>(pParam);
	pService->onTimeOut();
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei al que s'asignara la sortida.
/// \param info: Parametres d'inicialitzacio.
///
DigOutput::DigOutput(
    DigOutputService *pService,
    const DigOutputInitializeInfo *pInfo):

    pService(nullptr),
    state(State::Idle) {

    eosArgumentIsNotNull(pInfo);

    if (pService != nullptr)
        pService->add(this);

    port = pInfo->port;
    pin = pInfo->pin;
    options = 
        (pInfo->openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (pInfo->initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::~DigOutput() {

    if (pService != nullptr)
        pService->remove(this);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio de la sortida.
///
void DigOutput::onSetup() {

    halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);    
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio del temporitzador.
///
void DigOutput::onTimeOut() {

	switch (state) {
		case State::Idle:
			break;

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

	widthCnt = width / 10;
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

	delayCnt = delay / 10;
    widthCnt = width / 10;
    state = State::DelayedPulse;

    unlockSection();
}
