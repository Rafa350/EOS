#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halTMR.h"
#include "Services/eosDigInputService.h"
#include "System/Core/eosTask.h"


using namespace eos;


#define PATTERN_MASK     0x0FFF
#define PATTERN_POSEDGE  0x07FF
#define PATTERN_NEGEDGE  0x0800
#define PATTERN_ON       0x0FFF
#define PATTERN_OFF      0x0000


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany
/// \params   initParams: Parametres d'inicialitzacio.
///
DigInputService::DigInputService(
    Application* application,
    const InitParams& initParams):
    
	Service(application),
    timer(initParams.timer) {
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
    
    // Inicialitza les entrades
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

    // Activa el temporitzador
    //
    halTMRSetInterruptFunction(timer, tmrInterruptFunction, this);
    halTMRClearInterruptFlag(timer);
    halTMREnableInterrupt(timer);
    halTMRStartTimer(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void DigInputService::onTerminate() {
    
    // Desactiva el temporitzador
    //
    halTMRStopTimer(timer);
    halTMRDisableInterrupt(timer);
       
    // Finalitza el servei base
    //
    Service::onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    // Espera que es notifiquin canvis en les entrades
    //
    semaphore.wait(-1);

    // Procesa les entrades
    //
    for (auto it = inputs.begin(); it != inputs.end(); it++) {        
        DigInput* input = *it;

        if (input->eventCallback != nullptr) {

            bool ie = halTMRDisableInterrupt(timer);

            bool edge = input->edge;
            input->edge = false;

            if (ie)
            	halTMREnableInterrupt(timer);

            if (edge) {

                DigInput::EventArgs args;
                args.input = input;
                args.param = input->eventParam;

                input->eventCallback->execute(args);
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

    halTMRDisableInterrupt(timer);
    bool result = input->value;
    halTMREnableInterrupt(timer);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigInputService::tmrInterruptFunction() {
           
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
        semaphore.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temporitzador.
/// \param    timer: Identificador del temporitzador.
/// \param    params: Handler del servei.
///
void DigInputService::tmrInterruptFunction(
    TMRTimer timer,
    void* params) {
           
    DigInputService* service = static_cast<DigInputService*>(params);
    if (service != nullptr) 
        service->tmrInterruptFunction();
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    initParams: Parametres d'inicialitzacio.
///
DigInput::DigInput(
    DigInputService* service,
    const InitParams& initParams):

	service(nullptr),
    port(initParams.port),                    
    pin(initParams.pin),
    eventCallback(initParams.eventCallback),
    eventParam(initParams.eventParam) {
    
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
