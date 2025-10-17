#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"
#include "OSAL/osalKernel.h"
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
    const char *name,
    ITaskCallback *taskCallback,
    void *taskParams):

    _taskCallback {taskCallback},
    _taskParams {taskParams} {

    eosAssert(taskCallback != nullptr);

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

        default:
        	break;
    }

    info.function = function;
    info.params = this;
    info.ptrData = this;

    _hTask = osalTaskCreate(&info);
    eosAssert(_hTask != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Destrueix la tasca de FreeRTOS asociada.
///
Task::~Task() {

    if (_hTask != nullptr)
        osalTaskDestroy(_hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Executa la funcio de la tasca.
/// \param    params: El parametre de la tasca.
/// \remarks  No retorna mai.
///
void Task::function(
    void *params) {

    auto task = reinterpret_cast<Task*>(params);
    if ((task != nullptr) && (task->_taskCallback != nullptr)) {

        TaskCallbackArgs args = {
        	.task = task,
        	.params = task->_taskParams
        };
        task->_taskCallback->execute(args);
    }

    // Destrueix la propia tasca perque no s'executi mes
    //
    osalTaskDestroy(nullptr);
    task->_hTask = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la tasca en execucio.
/// \return   El resultat.
///
Task* Task::getExecutingTask() {

	auto hTask = osalGetCurrentTask();
	return static_cast<Task*>(osalGetPtrData(hTask));
}


/// ----------------------------------------------------------------------
/// \brief    Retard en milisegons.
/// \param    time: El numero de milisegons a retardar.
/// \remarks  S'aplica a la tasca que s'esta executant.
///
void Task::delay(
    unsigned time) {

	osalDelay(time);
}


/// ----------------------------------------------------------------------
/// \brief    Retard en milisegons.
/// \param    time: El numero de milisegons a retardar.
/// \param    weakTime: El valor de contador de ticks actualitzat.
/// \remarks  S'aplica a la tasca que s'esta executant.
///
void Task::delay(
    unsigned time,
    unsigned &weakTime) {

	osalDelayUntil(time, &weakTime);
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio interna.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si es correcte, false en cas de timeout o error
/// \remarks  S'aplica a la tasca que s'esta executant.
///
bool Task::waitNotification(
    unsigned blockTime) {

	return osalTaskWaitNotification(true, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Envia una notificacio interna.
///
void Task::raiseNotificationISR() {

	osalTaskRaiseNotificationISR(_hTask);
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
