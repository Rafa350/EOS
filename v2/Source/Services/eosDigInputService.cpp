#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halTMR.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"


#define PATTERN_MASK     0x0FFF
#define PATTERN_POSEDGE  0x07FF
#define PATTERN_NEGEDGE  0x0800
#define PATTERN_ON       0x0FFF
#define PATTERN_OFF      0x0000


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: The application.
/// \params   settings: Conmfigurationparameters.
///
DigInputService::DigInputService(
    Application *application,
    const Settings &settings):

	Service(application),
    hTimer(settings.hTimer) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

    while (!inputs.isEmpty())
        delete inputs.getBack();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (input->service == nullptr) {
        inputs.pushBack(input);
        input->service = this;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (input->service == this) {
        input->service = nullptr;
        inputs.removeAt(inputs.indexOf(input));
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    while (!inputs.isEmpty()) {
        DigInput* input = inputs.getBack();
        inputs.popBack();
        input->service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {

    // Inicialitza les entrades al valor actual
    //
    for (auto it = inputs.begin(); it != inputs.end(); it++) {
        DigInput* input = *it;
        input->value = halGPIOReadPin(input->port, input->pin);
        input->edge = false;
        input->pattern = input->value ? PATTERN_ON : PATTERN_OFF;
    }

    // Inicialitza el servei base
    //
    Service::onInitialize();

    // Habilita les interrupcions del temporitzador
    //
    halTMRSetInterruptFunction(hTimer, tmrInterruptFunction, this);

    halTMRClearInterruptFlags(hTimer, HAL_TMR_EVENT_UPDATE);
    halTMREnableInterrupts(hTimer, HAL_TMR_EVENT_UPDATE);

    // Activa el temporitzador
    //
    halTMRStartTimer(hTimer);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void DigInputService::onTerminate() {

    // Desactiva el temporitzador
    //
    halTMRStopTimer(hTimer);

    // Deshabilita les interrupcions del temporitzador
    //
    halTMRSetInterruptFunction(hTimer, NULL, NULL);

    halTMRDisableInterrupts(hTimer, HAL_TMR_EVENT_ALL);

    // Finalitza el servei base
    //
    Service::onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
/// \param    task: La tasca que executa el servei.
///
void DigInputService::onTask(
	Task *task) {

    // Espera que es notifiquin canvis en les entrades
    //
    if (changes.wait(unsigned(-1))) {

		// Procesa les entrades
		//
		for (auto it = inputs.begin(); it != inputs.end(); it++) {
			DigInput* input = *it;

			if (input->eventCallback != nullptr) {

				uint32_t state = halTMRDisableInterrupts(hTimer, HAL_TMR_EVENT_UPDATE);

				bool edge = input->edge;
				input->edge = false;

				if (state)
					halTMREnableInterrupts(hTimer, state);

				if (edge) {

					DigInput::EventArgs args;
					args.input = input;
					args.param = input->eventParam;

					input->eventCallback->execute(args);
				}
			}
		}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio 'tick'.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
#if Eos_ApplicationmTickEnabled
void DigInputService::onTick() {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \param    input: La entrada.
/// \return   El estat.
///
bool DigInputService::read(
    const DigInput* input) const {

    eosAssert(input != nullptr);
    eosAssert(input->service == this);

    uint32_t state = halTMRDisableInterrupts(hTimer, HAL_TMR_EVENT_UPDATE);
    bool result = input->value;
    if (state)
    	halTMREnableInterrupts(hTimer, HAL_TMR_EVENT_UPDATE);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
/// \param    event: L'event que ha generat la interrupcio.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigInputService::tmrInterruptFunction(
	uint32_t event) {

    bool changed = false;

    // Procesa totes les entrades
    //
    for (auto it = inputs.begin(); it != inputs.end(); it++) {

        DigInput* input = *it;

        // Actualitza el patro
        //
        input->pattern <<= 1;
        if (halGPIOReadPin(input->port, input->pin))
            input->pattern |= 1;

        // Analitza el patro per detectar un flanc positiu
        //
        if ((input->pattern & PATTERN_MASK) == PATTERN_POSEDGE) {
            input->value = 1;
            input->edge = 1;
            changed = true;
        }

        // Analitza el patro per detectar un flanc negatiu
        //
        else if ((input->pattern & PATTERN_MASK) == PATTERN_NEGEDGE) {
            input->value = 0;
            input->edge = 1;
            changed = true;
        }
    }

    // Notifica a la tasca que hi han canvis pendents per procesar
    //
    if (changed)
        changes.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    params: Handler del servei.
/// \param    event: El event que ha generat la interrupcio.
///
void DigInputService::tmrInterruptFunction(
    TMRHandler handler,
    void* params,
	uint32_t event) {

    DigInputService* service = static_cast<DigInputService*>(params);
    if (service != nullptr)
        service->tmrInterruptFunction(event);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: The service.
/// \param    settings: Configuration settings
///
DigInput::DigInput(
    DigInputService* service,
    const Settings &settings):

	service(nullptr),
    port(settings.port),
    pin(settings.pin),
    eventCallback(settings.eventCallback),
    eventParam(settings.eventParam) {

    if (service != nullptr)
        service->addInput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInput::~DigInput() {

    if (service != nullptr)
        service->removeInput(this);
}
