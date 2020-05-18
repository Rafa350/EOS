#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
#include "HAL/halTMR.h"
#include "Services/eosDigInputService.h"


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

    while (!inputs.isEmpty()) {
        DigInput* input = inputs.getFront();
        removeInput(input);       
        delete input;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una entrada al servei.
/// \param    input: L'entrada a afeigir.
///
void DigInputService::addInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    if (!isInitialized())
        if (input->service == nullptr) {
            inputs.pushBack(input);
            input->service = this;
        }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una entrada del servei.
/// \param    input: La entrada a eliminar.
///
void DigInputService::removeInput(
    DigInput* input) {

    eosAssert(input != nullptr);

    if (!isInitialized())
        if (input->service == this) {
            input->service = nullptr;
            inputs.removeAt(inputs.indexOf(input));
        }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {
    
    while (!inputs.isEmpty())
        removeInput(inputs.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
    
    // Inicialitza les entrades
    //
    for (auto it = inputs.getIterator(); it.hasNext(); it.next()) {
        DigInput* input = it.getCurrent();
        input->state = halGPIOReadPin(input->port, input->pin);
        input->pattern = input->state ? PATTERN_ON : PATTERN_OFF;
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
        
        for (auto it = inputs.getIterator(); it.hasNext(); it.next()) {
        
            DigInput* input = it.getCurrent();
          
            // Analitza el patro
            //
            if ((input->pattern & PATTERN_MASK) == PATTERN_POSEDGE)
                input->state = 1;           
            else if ((input->pattern & PATTERN_MASK) == PATTERN_NEGEDGE)
                input->state = 0;            
            else
                continue;

            // Si te funcio callback, la crida
            //
            if (input->eventCallback != nullptr) {

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

        bool patternChanged = false;
        
        for (auto it = service->inputs.getIterator(); it.hasNext(); it.next()) {
            
            DigInput* input = it.getCurrent();

            uint32_t oldPattern = input->pattern;
            
            // Actualitza el patro
            //
            input->pattern <<= 1;
            if (halGPIOReadPin(input->port, input->pin))
                input->pattern |= 1;
            
            // Comprova si ha canviat
            //
            if (input->pattern != oldPattern)
                patternChanged = true;
        }
        
        // Notifica a la tasca que hi han canvis pendents per procesar
        //
        if (patternChanged)
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

    return state;
}