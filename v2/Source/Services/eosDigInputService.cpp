#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
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
    
    timer(initParams.timer),
    period(initParams.period),
    Service(application) {
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
    
    // Inicialitza el temporitzador
    //
	TMRInitializeInfo tmrInfo;
	tmrInfo.timer = timer;
#if defined(EOS_PIC32MX)
    tmrInfo.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64 | HAL_TMR_INTERRUPT_ENABLE;
    tmrInfo.period = ((halSYSGetPeripheralClockFrequency() * period) / 64000) - 1; 
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
    
    // Inicialitza el servei base
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void DigInputService::onTask() {

    // Espera indefinidament que hagi canvis en les entrades
    //
    if (semaphore.wait(-1)) {
        
        for (auto it = inputs.begin(); it != inputs.end(); it++) {        
            DigInput* input = *it;
          
            if (input->eventCallback != nullptr) {
                
                halINTDisableInterrupts();
                bool edge = input->edge;
                input->edge = false;
                halINTEnableInterrupts();

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
void DigInputService::onTick() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Captura la interrupcio del temporitzador.
///
void DigInputService::isrTimerFunction(
    TMRTimer timer,
    void* params) {
           
    DigInputService* service = static_cast<DigInputService*>(params);
    if (service != nullptr) {

        bool changed = false;
        
        // Procesa totes les entrades
        //
        for (auto it = service->inputs.begin(); it != service->inputs.end(); it++) {
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
            service->semaphore.releaseISR();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei.
/// \param    initParams: Parametres d'inicialitzacio.
///
DigInput::DigInput(
    DigInputService* service,
    const InitParams& initParams):

    port(initParams.port),                    
    pin(initParams.pin),
    eventCallback(initParams.eventCallback),
    eventParam(initParams.eventParam),
    service(nullptr) {
    
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


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat de l'entrada.
/// \return   El estat.
///
bool DigInput::read() const {

    halINTDisableInterrupts();
    bool result = value;
    halINTEnableInterrupts();
    return result;
}