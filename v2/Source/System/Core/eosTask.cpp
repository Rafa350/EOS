#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"
#include "OSAL/osalKernel.h"
#include "System/Core/eosString.h"
#include "System/Core/eosTask.h"

#include "FreeRTOS.h"
#include "task.h"


using namespace eos;



/// ----------------------------------------------------------------------
/// \brief    Constructor. Crea un objecte Task que encapsula una tasca
///           de FreeRTOS.
/// \param    stackSize: Tamany de la pila.
/// \param    priority: Prioritat del proces.
/// \param    name: Nom de la tasca.
/// \param    runable: Objecte que implementa IRunable.
///
Task::Task(
    unsigned stackSize,
    TaskPriority priority,
    const String& name,
    IRunable *runable):

    runable(runable),
	weakTime(0) {

    eosAssert(runable != nullptr);

    TaskInitializeInfo info;
    info.name = (const char*) name;
    info.stackSize = stackSize;
    info.options = OSAL_TASK_PRIORITY_NORMAL;
    info.function = function;
    info.params = this;
    hTask = osalTaskCreate(&info);

    eosAssert(hTask != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Destrueix la tasca de FreeRTOS asociada.
///
Task::~Task() {

	osalTaskDestroy(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Executa la funcio de la tasca.
/// \param    pParams: El handler de la tasca.
///
void Task::function(
    void *pParams) {

	eosAssert(pParams != nullptr);

    Task *task = reinterpret_cast<Task*>(pParams);
    task->weakTime = osalGetTickCount();
    while (true)
        task->runable->run(task);
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
    int time) {

	osalDelay(time);
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual un numero determinat de milisegons.
/// \param    time: El numero de milisegons a retardar.
/// \param    weakTime: El valor de contador de ticks actualitzat.
///
void Task::delay(
    int time,
    int &weakTime) {

	osalDelayUntil(time, &weakTime);
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio interna de la tasca.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si hi ha notificacio, false en cas contrari.
///
bool Task::notificationTake(
    int blockTime) {

	// Millorar a traves de OSAL
    TickType_t ticks = blockTime == -1 ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
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
