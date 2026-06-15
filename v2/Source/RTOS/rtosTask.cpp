#include "eos.h"
#include "eosAssert.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosTask.h"
#include "RTOS/rtosTime.h"
#include "System/eosTime.h"

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
/// \param    event: Event d'execucio de la tasca
///
rtos::Task::Task(
	uint32_t stackDepth,
	Priority priority,
	const char *name,
	IEvent &event):

	_event {&event},
	_handler {createHandler(this, taskFunction, stackDepth, priority, name)},
	_lastWeakTick {0} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Task::~Task() {

	kill();
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat.
/// \return   L'estat.
///
rtos::Task::State rtos::Task::getState() const {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	switch (eTaskGetState(hTask)) {
		case eRunning:
			return State::running;

		case eReady:
			return State::ready;

		case eBlocked:
			return State::blocked;

		case eSuspended:
			return State::suspended;

		case eDeleted:
			return State::killed;

		default:
			return State::unknown;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Suspend l'execucio de la tasca.
//
void rtos::Task::suspend() const {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	vTaskSuspend(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Resumeix l'execucio de la tasca.
//
void rtos::Task::resume() const {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	vTaskResume(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza permanentment l'execucio de la tasca.
//
void rtos::Task::kill() const {

	if (isAlive()) {
		CriticalSection::enter();
		if (isAlive())
			destroyHandler(_handler);
		CriticalSection::exit();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual.
/// \param    time: Temps d'espera en milisegons
///
void rtos::Task::delay(
	eos::Time time) {

	vTaskDelay(rtos::toTicks(time));
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual finst el temps relatiu indicat, desde
///           l'ultima activacio de la tasca
/// \param    time: Temps d'espera en milisegons
///
void rtos::Task::delayUntil(
	eos::Time time) {

	Task *task = Task::getExecutingTask();
	if (task != nullptr) {
		if (task->_lastWeakTick == 0)
	    	task->_lastWeakTick = xTaskGetTickCount();
		vTaskDelayUntil(&task->_lastWeakTick, rtos::toTicks(time));
	}
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio.
/// \param    clear:
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool rtos::Task::waitNotification(
	bool clear,
	eos::Time blockTime) {

	return ulTaskNotifyTake(clear ? pdTRUE : pdFALSE, rtos::toTicks(blockTime));
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio.
///
void rtos::Task::raiseNotification() {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	xTaskNotifyGive(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio d'ins d'un ISR
///
void rtos::Task::raiseNotificationISR() {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	BaseType_t taskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(hTask, &taskWoken);
	portYIELD_FROM_ISR(taskWoken);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia la prioritat de la tasca.
/// \param    priority: La nova prioritat.
///
void rtos::Task::setPriority(
	Priority priority) const {

	TaskHandle_t hTask = static_cast<TaskHandle_t>(_handler);
	vTaskPrioritySet(hTask, getPriorityValue(priority));
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la tasca es viva.
/// \return   True si no esta 'Deleted'
///
bool rtos::Task::isAlive() const {

	return getState() != State::killed;
}


/// ----------------------------------------------------------------------
/// \brief    Funcio de la tasca que executa el RTOS
/// \param    params: Parametres de la tasca. En aquest cas es
///           el punter 'this' del objecte 'Task'
///
void rtos::Task::taskFunction(
	void *params) {

    Task *task = static_cast<Task*>(params);
    if (task != nullptr) {

    	task->_lastWeakTick = xTaskGetTickCount();

		if (task->_event != nullptr) {

			EventArgs args = {
			};
			task->_event->execute(task, &args);
		}
    }

    destroyHandler(nullptr);
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
	Task *task,
	Function function,
	uint32_t stackDepth,
	Priority priority,
	const char *name) {

	TaskHandle_t hTask;

    if ((xTaskCreate(
        function,
        name == nullptr ? defaultName : name,
        stackDepth,
        task,
        getPriorityValue(priority),
        &hTask) != pdPASS) || (hTask == nullptr))
    	return nullptr;

    // Guarda el punter 'this' per recuperacio posterior en 'getExecutingTask'
    //
    vTaskSetThreadLocalStoragePointer(hTask, idxThis, task);

    return static_cast<Handler>(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el handler de la tasca.
/// \param    handler: El handler
///
void rtos::Task::destroyHandler(
	Handler handler) {

	TaskHandle_t hTask =
		handler == nullptr ?
			xTaskGetCurrentTaskHandle() :
			static_cast<TaskHandle_t>(handler);

	vTaskSetThreadLocalStoragePointer(hTask, idxThis, nullptr);
	vTaskDelete(hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula el valor de prioritat per RTOS.
/// \param    priority: Prioritat.
/// \return   Valor numeric de la prioritat.
/// \notes    Atencio: El valor del enumerador Priority esta definit i no es
///           por canviar sense motiu.
///
static uint32_t getPriorityValue(
	rtos::Task::Priority priority) {

	return tskIDLE_PRIORITY +
		(uint32_t)priority - (uint32_t)rtos::Task::Priority::idle;
}
