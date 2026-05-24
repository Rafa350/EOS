#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosTask.h"
#include "RTOS/rtosTicks.h"

#include "FreeRTOS.h"
#include "task.h"


#if configNUM_THREAD_LOCAL_STORAGE_POINTERS < 1
#error "configNUM_THREAD_LOCAL_STORAGE_POINTERS ha de ser mayor que 0"
#endif


static constexpr BaseType_t idxThis = 0;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    stackDepth: Profunditat del stack.
/// \param    priority: La prioritat.
/// \param    name: Nom de la tasca.
/// \param    taskCallback: Callback de la tasca.
/// \param    taskParams: Parametres a pasar a la tasca.
///
rtos::Task::Task(
	uint32_t stackDepth,
	Priority priority,
	const char *name,
	ITaskCallback *taskCallback,
	void *taskParams):

	_taskCallback {taskCallback},
	_taskParams {taskParams} {

	// Crea la tasca
	//
    xTaskCreate(
        taskFunction,
        name == nullptr ? "" : name,
        stackDepth,
        this,
        tskIDLE_PRIORITY + ((UBaseType_t) priority),
        reinterpret_cast<TaskHandle_t*>(&_handler));

    // Guarda el punter 'this' per recuperacio posterior en 'getExecutingTask'
    //
    vTaskSetThreadLocalStoragePointer(
    	static_cast<TaskHandle_t>(_handler),
		idxThis,
		this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Task::~Task() {

	if (_handler != nullptr)
		vTaskDelete(static_cast<TaskHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual.
/// \param    time: Temps d'espera en ticks
///
void rtos::Task::delay(
	Ticks ticks) {

	vTaskDelay(ticks);
}


/// ----------------------------------------------------------------------
/// \brief    Retarda la tasca actual.
/// \param    time: Temps d'espera en milisegons
///
void rtos::Task::delay(
	Miliseconds time) {

	vTaskDelay(time.asTicks());
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
    	(task->_handler != nullptr) &&
		(task->_taskCallback != nullptr)) {

        TaskCallbackArgs args = {
        	.task = task,
        	.params = task->_taskParams
        };
        task->_taskCallback->execute(args);
    }

    // Destrueix la propia tasca perque no s'executi mes
    //
    vTaskDelete(static_cast<TaskHandle_t>(task->_handler));
    task->_handler = nullptr;
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

