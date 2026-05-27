#include "eosAssert.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosTask.h"

#include "FreeRTOS.h"
#include "task.h"


#if configNUM_THREAD_LOCAL_STORAGE_POINTERS < 1
#error "configNUM_THREAD_LOCAL_STORAGE_POINTERS ha de ser mayor que 0"
#endif


static constexpr uint32_t idxThis = 0;
static constexpr const char *defaultName = "Task";

static uint32_t getPriorityValue(rtos::Task::Priority priority);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    stackDepth: Profunditat del stack.
/// \param    priority: La prioritat.
/// \param    name: Nom de la tasca.
/// \param    taskCallback: Callback de la tasca.
///
rtos::Task::Task(
	uint32_t stackDepth,
	Priority priority,
	const char *name,
	ITaskEvent &taskEvent):

	_taskEvent {&taskEvent},
	_handler {createHandler(taskFunction, this, stackDepth, priority, name)} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Task::~Task() {

	destroyHandler(_handler);
}


/// ----------------------------------------------------------------------
/// \brief    Suspend l'execucio de la tasca.
//
void rtos::Task::suspend() const {

	vTaskSuspend(static_cast<TaskHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Resumeix l'execucio de la tasca.
//
void rtos::Task::resume() const {

	vTaskResume(static_cast<TaskHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual.
/// \param    time: Temps d'espera en milisegons
///
void rtos::Task::delay(
	Time time) {

	vTaskDelay(time.toTicks());
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual finst el temps relatiu indicat, desde
///           l'ultima activacio de la tasca
/// \param    time: Temps d'espera en milisegons
///
void rtos::Task::delayUntil(
	Time time) {

	Task *task = Task::getExecutingTask();
	vTaskDelayUntil(&task->_lastWeakTick, time.toTicks());
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio.
/// \param    clear:
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool rtos::Task::waitNotification(
	bool clear,
	Time blockTime) {

	return ulTaskNotifyTake(clear ? pdTRUE : pdFALSE, blockTime.toTicks());
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio.
///
void rtos::Task::raiseNotification() {

	xTaskNotifyGive(static_cast<TaskHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio d'ins d'un ISR
///
void rtos::Task::raiseNotificationISR() {

	portBASE_TYPE taskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(static_cast<TaskHandle_t>(_handler), &taskWoken);
	portYIELD_FROM_ISR(taskWoken);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia la prioritat de la tasca.
/// \param    priority: La nova prioritat.
///
void rtos::Task::setPriority(
	Priority priority) const {

	vTaskPrioritySet(
        static_cast<TaskHandle_t>(_handler),
        getPriorityValue(priority));
}


/// ----------------------------------------------------------------------
/// \brief    Entrada a una seccio critica.
///
void rtos::Task::enterCriticalSection() {

	taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Sortida d'una seccio critica.
///
void rtos::Task::exitCriticalSection() {

    taskEXIT_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Funcio de la tasca que executa el RTOS
/// \param    params: Parametres de la tasca. En aquest cas es
///           el punter 'this' del objecte 'Task'
///
void rtos::Task::taskFunction(
	void *params) {

    Task *task = static_cast<Task*>(params);
    if ((task != nullptr) &&
		(task->_taskEvent != nullptr)) {

    	task->_lastWeakTick = xTaskGetTickCount();

		TaskEventArgs args = {
		};
		task->_taskEvent->execute(task, &args);

        while (true)
        	vTaskSuspend(nullptr);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Obte la tasca que s'esta executant al cridar a aquest metode
/// \return   La tasca.
///
rtos::Task* rtos::Task::getExecutingTask() {

	return reinterpret_cast<Task*>(
		pvTaskGetThreadLocalStoragePointer(
			xTaskGetCurrentTaskHandle(),
			idxThis));
}


/// ----------------------------------------------------------------------
/// \brief    Crea el handler de la tasca.
//  \param    function: Funcio callback de la tasca.
/// \param    task: La tasca que s'esta creant.
/// \param    stackDepht: profunditat de la pila.
/// \param    priority: Prioridat.
///
rtos::Task::Handler rtos::Task::createHandler(
	Function function,
	Task *task,
	uint32_t stackDepth,
	Priority priority,
	const char *name) {

	TaskHandle_t handler;

    xTaskCreate(
        function,
        name == nullptr ? defaultName : name,
        stackDepth,
        task,
        getPriorityValue(priority),
        &handler);

    // Guarda el punter 'this' per recuperacio posterior en 'getExecutingTask'
    //
    vTaskSetThreadLocalStoragePointer(
    	handler,
		idxThis,
		task);

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el handler de la tasca,.
/// \param    handler: El handler.
///
void rtos::Task::destroyHandler(
	Handler handler) {

	vTaskSuspend(static_cast<TaskHandle_t>(handler));
	vTaskDelete(static_cast<TaskHandle_t>(handler));
}


/// ----------------------------------------------------------------------
/// \brief    Calcula el valor de prioritat per RTOS
/// \param    priority: Prioritat.
/// \return   Valor numeric de la prioritat.
///
static uint32_t getPriorityValue(
	rtos::Task::Priority priority) {

	return tskIDLE_PRIORITY +
		(uint32_t)priority - (uint32_t)rtos::Task::Priority::idle;
}
