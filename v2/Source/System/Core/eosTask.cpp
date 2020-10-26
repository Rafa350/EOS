#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"
#include "OSAL/osalKernel.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"

#include "FreeRTOS.h"
#include "task.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea un objecte Task.
/// \param    stackSize: Tamany de la pila.
/// \param    priority: Prioritat del proces.
/// \param    name: Nom de la tasca.
/// \param    eventCallback: Funcio callback.
/// \param    eventParam: Parametre que es passa a la funcio callback.
///
Task::Task(
    unsigned stackSize,
    Priority priority,
    const String& name,
    IEventCallback* eventCallback,
    void* eventParams):

    eventCallback(eventCallback),
    eventParams(eventParams),
	weakTime(0) {

    eosAssert(eventCallback != nullptr);

    TaskInitializeInfo info;

    info.name = name;
    info.stackSize = stackSize;
    info.options = 0;
    switch (priority) {
        case Priority::high:
            info.options |= OSAL_TASK_PRIORITY_HIGH;
            break;

        case Priority::normal:
            info.options |= OSAL_TASK_PRIORITY_NORMAL;
            break;

        case Priority::low:
            info.options |= OSAL_TASK_PRIORITY_LOW;
            break;

        case Priority::idle:
            info.options |= OSAL_TASK_PRIORITY_IDLE;
            break;
    }

    info.function = function;
    info.params = this;

    hTask = osalTaskCreate(&info);
    eosAssert(hTask != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Destrueix la tasca de FreeRTOS asociada.
///
Task::~Task() {

    if (hTask != nullptr)
        osalTaskDestroy(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Executa la funcio de la tasca.
/// \param    params: El parametre de la tasca.
/// \remarks  No retorna mai.
///
void Task::function(
    void* params) {

    Task *task = reinterpret_cast<Task*>(params);
    if (task && task->eventCallback) {

        task->weakTime = osalGetTickCount();

        EventArgs args;
        args.task = task;
        args.params = task->eventParams;

        // Executa continuament la funcio
        //
        while (true)
            task->eventCallback->execute(args);
    }

    // Destrueix la propia tasca perque no s'executi mes
    //
    osalTaskDestroy(NULL);
    task->hTask = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Retorna el numero te ticks transcurreguts desde la
///           inicialitzacio del sistema.
/// \return   El numero de ticks.
///
unsigned Task::getTickCount() {

    return osalGetTickCount();
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual un numero determinat de milisegons.
/// \param    time: El numero de milisegons a retardar.
///
void Task::delay(
    unsigned time) {

	osalDelay(time);
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual un numero determinat de milisegons.
/// \param    time: El numero de milisegons a retardar.
/// \param    weakTime: El valor de contador de ticks actualitzat.
///
void Task::delay(
    unsigned time,
    unsigned &weakTime) {

	osalDelayUntil(time, &weakTime);
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio interna de la tasca.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si hi ha notificacio, false en cas contrari.
///
bool Task::notificationTake(
    unsigned blockTime) {

	// Millorar a traves de OSAL
    TickType_t ticks = blockTime == ((unsigned)-1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return ulTaskNotifyTake(pdTRUE, ticks) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Entra en una seccio critica
///
void Task::enterCriticalSection() {

    osalEnterCritical();
}


/// ----------------------------------------------------------------------
/// \brief    Surt d'una seccio critica
///
void Task::exitCriticalSection() {

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief    Inicia tots els fils d'execucio.
///
void Task::startAll() {

    osalStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Suspend tots els fils d'execucio. Impedeix el canvi de tasca
///
void Task::suspendAll() {

    osalSuspendAll();
}


/// ----------------------------------------------------------------------
/// \brief    Activa tots els fils d'execucio
///
void Task::resumeAll() {

    osalResumeAll();
}


void Task::yield() {

    osalTaskYield();
}


void Task::yieldISR() {

    //osalTaskYield();
}
