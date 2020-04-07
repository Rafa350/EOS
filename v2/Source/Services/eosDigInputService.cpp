#include "eos.h"
#include "eosAssert.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
#include "HAL/halTMR.h"
#include "Services/eosDigInputService.h"


using namespace eos;


#define PATTERN_mask     0xFF
#define PATTERN_ON       0xFF
#define PATTERN_OFF      0x00
#define PATTERN_POSEDGE  0x7F
#define PATTERN_NEGEDGE  0x80


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: L'aplicacio a la que pertany
/// \params   initParams: Parametres d'inicialitzacio.
///
DigInputService::DigInputService(
    Application* application,
    const InitParams& initParams):
    
    commandQueue(commandQueueSize),
    timer(initParams.timer),
    period(initParams.period),
    Service(application) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigInputService::~DigInputService() {

    while (!inputs.isEmpty()) {
        DigInput* input = inputs.getFirst();
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
            inputs.add(input);
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
            inputs.remove(input);
        }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les entrades del servei.
///
void DigInputService::removeInputs() {
    
    while (!inputs.isEmpty())
        removeInput(inputs.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitzacio del servei.
///
void DigInputService::onInitialize() {
    
    // Inicialitza les entrades
    //
    for (DigInputListIterator it(inputs); it.hasNext(); it.next()) {
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

    // Espera que hagi quelcom per fer
    //
    Command cmd;
    while (commandQueue.pop(cmd, unsigned(-1))) {
        
        DigInput* input = cmd.input;

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
    
    DigInputService* service = reinterpret_cast<DigInputService*>(params);
    if (service != nullptr) {
        for (DigInputListIterator it(service->inputs); it.hasNext(); it.next()) {
            
            DigInput* input = it.getCurrent();
            
            // Actualitza el patro
            //
            input->pattern <<= 1;
            if (halGPIOReadPin(input->port, input->pin))
                input->pattern |= 1;

            // Detecta els canvis d'estat
            //
            OpCode opCode = OpCode::null;
            switch (input->pattern & PATTERN_mask) {
                case PATTERN_POSEDGE:
                    input->state = true;
                    opCode = OpCode::posEdge;
                    break;
            
                case PATTERN_NEGEDGE:
                    input->state = false;
                    opCode = OpCode::negEdge;
                    break;
                    
                case PATTERN_ON:
                    input->state = true;
                    break;

                case PATTERN_OFF:
                    input->state = false;
                    break;
            }

            // Si hi han canvis, genera la comanda per executar en la
            // tasca del servei
            //
            if (opCode != OpCode::null) {
                
                Command cmd;
                cmd.input = input,                    
                cmd.opCode = opCode;
                
                service->commandQueue.pushISR(cmd);
            }
        }
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
bool DigInput::get() const {

    halINTDisableInterrupts();
    bool s = state;
    halINTEnableInterrupts();
    
    return s;
}