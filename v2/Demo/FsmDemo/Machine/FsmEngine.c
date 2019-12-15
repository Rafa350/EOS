#include "eosPic.h"
#include "Services/EngineSrv.h"
#include "Services/Engine/FsmEngine.h"
#include "Services/Engine/fsm.h"
#include "Services/Engine/fsm_defs.h"


static Queue evQueue;
bool test;
bool trigger;

void StartControlSetup(Context context);
void StartControlRun(Event event, Context context);
void ArmUpActivitySetup(Context context);
void ArmUpActivityRun(Event event, Context context);


/// ----------------------------------------------------------------------
/// \brief Captura els events de les entrades.
///
static void CaptureInputEvents() {

    // Comprova la entrada INP_ST
    //
    if (inpPosEdge(INP_ST))
        quePut(&evQueue, Event_INP_ST_ON);    
    else if (inpNegEdge(INP_ST)) 
        quePut(&evQueue, Event_INP_ST_OFF);    
    
    // Comprova la entrada INP_TR
    //
    if (inpPosEdge(INP_TR))
        quePut(&evQueue, Event_INP_TR_ON);    
    else if (inpNegEdge(INP_TR))
        quePut(&evQueue, Event_INP_TR_OFF);    

    // Comprova la entrada INP_IH
    //
    if (inpPosEdge(INP_IH))
        quePut(&evQueue, Event_INP_IH_ON);    
    else if (inpNegEdge(INP_IH))
        quePut(&evQueue, Event_INP_IH_OFF);   
}


/// ----------------------------------------------------------------------
/// \brief Captura els events dels temporitzadors.
///
void CaptureTimerEvents() {
    
    if (timGet(TIM_TR_DELAY)) {
        quePut(&evQueue, Event_TIM_TR_DELAY);
        timStop(TIM_TR_DELAY);
    }

    if (timGet(TIM_TR_INHIBIT)) {
        quePut(&evQueue, Event_TIM_TR_INHIBIT);
        timStop(TIM_TR_INHIBIT);
    }

    /*if (timGet(TIM_IH_DELAY)) {
        quePut(&evQueue, Event_TIM_IH_DELAY);
        timStop(TIM_IH_DELAY);
    }*/
}


/// ----------------------------------------------------------------------
/// \brief Procesa els events de la cua.
///
static void ProcessEvents() {
    
    while (!queIsEmpty(&evQueue)) {
        Event event = queGet(&evQueue);          
        StartControlRun(event, NULL);
    }
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el servei.
///
void FsmEngineSetup() {

    queInitialize(&evQueue);
    
    StartControlSetup(NULL);
}


/// ----------------------------------------------------------------------
/// \brief Executa el servei.
///
void FsmEngineLoop() {
    
    CaptureInputEvents();
    CaptureTimerEvents();
    
    ProcessEvents();
}


void FsmEngineSendEvent(
    Event event) {
    
    quePut(&evQueue, event);
}