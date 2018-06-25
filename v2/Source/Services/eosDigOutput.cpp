#include "eos.h"
#include "Services/eosDigOutput.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"
#include "osal/osalTask.h"


using namespace eos;


class DigOutputService::Implementation {
	private:
    	TMRTimer timer;
    	DigOutput *pFirst;

	private:
    	static void timerInterrupt(TMRTimer timer, void *pParam);
    	void onTimeout();
    	void startTimerAction(DigOutput *output);
    	void stopTimerAction(DigOutput *output);

	public:
    	Implementation(const DigOutputServiceInitializeInfo *pInfo);
    	~Implementation();

    	void add(DigOutput *output);
    	void remove(DigOutput *output);
};


class DigOutput::Implementation {
	private:
		enum class State {
			Done,
			DelayedPulse,
			Pulse
		};

	private:
	    GPIOPort port;
		GPIOPin pin;
		State state;
		unsigned delayCnt;
		unsigned widthCnt;

	public:
		Implementation(const DigOutputInitializeInfo *info);
		~Implementation();

		void set();
		void clear();
		void toggle();
		void pulse(uint16_t width);
		void delayedPulse(uint16_t delay, uint16_t width);
		bool get() const;

		void onTimeout();
};


static const char *serviceName = "DigOutputService";
static const unsigned taskStackSize = 512;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: L'aplicacio a la que pertany.
/// \param pInfo: Parametres d'inicialitzacio.
///
DigOutputService::DigOutputService(
    Application *application,
    const DigOutputServiceInitializeInfo *pInfo):

    Service(application, serviceName, taskStackSize, taskPriority),
	pImpl(new DigOutputService::Implementation(pInfo)) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

	delete pImpl;
}


/// ----------------------------------------------------------------------
/// \brief Afegeig una sortida al servei.
/// \param output: La sortida a afeigir.
///
void DigOutputService::add(
    DigOutput *output) {

	pImpl->add(output);
}


/// ----------------------------------------------------------------------
/// \brief Elimina una sortida del servei.
/// \param output: La sortida a eliminar.
///
void DigOutputService::remove(
    DigOutput *output) {

	pImpl->remove(output);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei al que s'asignara la sortida.
/// \param info: Parametres d'inicialitzacio.
///
DigOutput::DigOutput(
    DigOutputService *service,
    const DigOutputInitializeInfo *info):

    service(nullptr),
	pImpl(new Implementation(info)) {

    if (service != nullptr)
        service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::~DigOutput() {

    if (service != nullptr)
        service->remove(this);

    delete pImpl;
}


/// ----------------------------------------------------------------------
/// \brief Obte actual l'estat d'una sortida.
/// \return L'estat de la sortida.
///
bool DigOutput::get() const {

    return pImpl->get();
}


/// ----------------------------------------------------------------------
/// \brief Desactiva una sortida.
///
void DigOutput::clear() {

	pImpl->clear();
}


/// ----------------------------------------------------------------------
/// \brief Activa una sortida
///
void DigOutput::set() {

	pImpl->set();
}


/// ----------------------------------------------------------------------
/// \brief Inverteix una sortida.
///
void DigOutput::toggle() {

	pImpl->toggle();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls.
/// \param width: Amplada del puls.
///
void DigOutput::pulse(
	unsigned width) {

	pImpl->pulse(width);
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls retardat.
/// \param delay: Retard fins a l'inici del puls.
/// \param width: Amplada del puls.
///
void DigOutput::delayedPulse(
	unsigned delay,
	unsigned width) {

	pImpl->delayedPulse(delay, width);
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
DigOutputService::Implementation::Implementation(
	const DigOutputServiceInitializeInfo *pInfo) {

	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = pInfo->timer;
	tmrInfo.pIrqCall = timerInterrupt;
	tmrInfo.pIrqParams = this;
	halTMRInitialize(&tmrInfo);
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::Implementation::~Implementation() {
}


void DigOutputService::Implementation::startTimerAction(
	DigOutput *output) {

	halTMRStartTimer(timer);
}


void DigOutputService::Implementation::stopTimerAction(
	DigOutput *output) {

	halTMRStopTimer(timer);
}

/// ----------------------------------------------------------------------
/// \brief Procesa el timeout del temporitzador.
///
void DigOutputService::Implementation::onTimeout() {


}


/// ----------------------------------------------------------------------
/// \brief Captura la interrupcio del temporitzador.
///
void DigOutputService::Implementation::timerInterrupt(
	TMRTimer timer,
	void *pParam) {

	DigOutputService::Implementation *pImpl = reinterpret_cast<DigOutputService::Implementation*>(pParam);
	pImpl->onTimeout();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'objecte.
/// \param info: Parametres d'inicialitzacio.
///
DigOutput::Implementation::Implementation(
	const DigOutputInitializeInfo *info):

	port(info->port),
	pin(info->pin),
	state(State::Done) {

    GPIOInitializePinInfo pinInfo;
    pinInfo.port = port;
    pinInfo.pin = pin;
    pinInfo.options =
        (info->openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (info->initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
    halGPIOInitializePins(&pinInfo, 1);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::Implementation::~Implementation() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio del temporitzador.
///
void DigOutput::Implementation::onTimeout() {

	switch (state) {
		case State::Done:
			break;

		case State::Pulse:
			if (widthCnt > 0) {
				widthCnt--;
				if (widthCnt == 0) {
					halGPIOTogglePin(port, pin);
					state = State::Done;
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
/// \brief Obte el valor de la sortida.
/// \return El valor obtingut.
///
bool DigOutput::Implementation::get() const {

	return halGPIOReadPin(port, pin);
}


/// ----------------------------------------------------------------------
/// \brief Asigna una sortida al valor actiu.
///
void DigOutput::Implementation::set() {

	osalEnterCritical();

    halGPIOSetPin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Asigna una sortida al valor no actiu.
///
void DigOutput::Implementation::clear() {

	osalEnterCritical();

    halGPIOClearPin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Inverteix una sortida.
///
void DigOutput::Implementation::toggle() {

	osalEnterCritical();

    halGPIOTogglePin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls. Inverteix la sortida durant el temps especificad,
///        despres retorna al seu valor original.
/// \param width: Amplada del puls.
///
void DigOutput::Implementation::pulse(
	uint16_t width) {

	osalEnterCritical();

	if (state == State::Done)
        halGPIOTogglePin(port, pin);

	widthCnt = width;
    state = State::Pulse;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls retardat. Inverteix la sortida durant el temps
///        especificad, despres retorna al seu valor original.
/// \param delay: Retard fins l'inici del puls.
/// \param width: Amplada del puls.
///
void DigOutput::Implementation::delayedPulse(
	uint16_t delay,
	uint16_t width) {

	osalEnterCritical();

	delayCnt = delay;
    widthCnt = width;
    state = State::DelayedPulse;

    osalExitCritical();
}
