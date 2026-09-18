module;


#include "eos.h"
#include "eosCallbacks.h"

#include "FreeRTOS.h"
#include "task.h"


export module Eos.System.Core.Task;


import Eos.Ticks;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.RTOSUtils;


#if configNUM_THREAD_LOCAL_STORAGE_POINTERS < 1
#error "configNUM_THREAD_LOCAL_STORAGE_POINTERS ha de ser mayor que 0"
#endif


namespace eos {

	struct StorageIndex {
		static constexpr uint32_t ptrThis = 0;
	};
}


export namespace eos {

	class Task final {
		public:
			enum class Priority {
				idle = 0,
				low,
				belowNormal,
				normal,
				aboveNormal,
				high,
				realTime
			};

			enum class State {
				ready,
				running,
				suspended,
				blocked,
				killed,
				unknown
			};

			struct EventArgs {
		    };
		    using IEvent = eos::ICallbackP2<Task*, EventArgs*>;
		    template <typename Instance_> using Event = eos::CallbackP2<Instance_, Task*, EventArgs*>;

		private:
			static constexpr char _defaultName[] = "Task";

		private:
			IEvent * const _event;
			TaskHandle_t const _handler;
			uint32_t _lastWeakTick;

		private:
			Task(const Task&) = delete;
			Task(Task&&) = delete;
			Task& operator=(const Task&) = delete;
			Task& operator=(Task&&) = delete;

			[[nodiscard]] TaskHandle_t createHandler(uint32_t stackDepth, Priority priority, const char *name);
			void destroyHandler();

			static uint32_t getPriorityValue(Priority priority);

			static void taskFunction(void *params);

		public:
			Task(uint32_t stackDepth, Priority priority, const char *name, IEvent &event);
			~Task();

		public:
			[[nodiscard]] static Task* getExecutingTask();
			[[nodiscard]] State getState() const;

            static void delay(Ticks time);
            static void delayUntil(Ticks time);

            static bool waitNotification(bool clear, Ticks blockTime);
            void raiseNotification();
            void raiseNotificationISR();

            void suspend() const;
            void resume() const;
            void kill();

            [[nodiscard]] bool isAlive() const;

            void setPriority(Priority priority) const;
	};
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    stackDepth: Profunditat del stack.
/// @param    priority: La prioritat.
/// @param    name: Nom de la tasca.
/// @param    event: Event d'execucio de la tasca
///
eos::Task::Task(
	uint32_t stackDepth,
	Priority priority,
	const char *name,
	IEvent &event):

	_event {&event},
	_handler {createHandler(stackDepth, priority, name)},
	_lastWeakTick {0} {
}


/// ---------------------------------------------------------------------------
/// \brief    Destructor.
///
eos::Task::~Task() {

	kill();
}


/// ---------------------------------------------------------------------------
/// \brief    Obte l'estat.
/// \return   L'estat.
///
eos::Task::State eos::Task::getState() const {

	switch (eTaskGetState(_handler)) {
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


/// ---------------------------------------------------------------------------
/// \brief    Suspend l'execucio de la tasca.
//
void eos::Task::suspend() const {

	vTaskSuspend(_handler);
}


/// ---------------------------------------------------------------------------
/// \brief    Resumeix l'execucio de la tasca.
//
void eos::Task::resume() const {

	vTaskResume(_handler);
}


/// ---------------------------------------------------------------------------
/// \brief    Finalitza permanentment l'execucio de la tasca.
//
void eos::Task::kill() {

	if (isAlive()) {
		CriticalSection::enter();
		if (isAlive())
			destroyHandler();
		CriticalSection::exit();
	}
}


/// ---------------------------------------------------------------------------
/// \brief    Retarda la tasca actual.
/// \param    time: Temps d'espera en milisegons
///
void eos::Task::delay(
	Ticks time) {

	vTaskDelay(static_cast<TickType_t>(time));
}


/// ---------------------------------------------------------------------------
/// \brief    Retarda la tasca actual finst el temps relatiu indicat, desde
///           l'ultima activacio de la tasca
/// \param    time: Temps d'espera en milisegons
///
void eos::Task::delayUntil(
	Ticks time) {

	Task *task = Task::getExecutingTask();
	if (task != nullptr) {
		if (task->_lastWeakTick == 0)
	    	task->_lastWeakTick = xTaskGetTickCount();
		vTaskDelayUntil(&task->_lastWeakTick, static_cast<TickType_t>(time));
	}
}


/// ---------------------------------------------------------------------------
/// \brief    Espera una notificacio.
/// \param    clear:
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool eos::Task::waitNotification(
	bool clear,
	Ticks blockTime) {

	return ulTaskNotifyTake(
		clear ? pdTRUE : pdFALSE,
		static_cast<TickType_t>(blockTime));
}


/// ---------------------------------------------------------------------------
/// \brief    Genera una notificacio.
///
void eos::Task::raiseNotification() {

	xTaskNotifyGive(_handler);
}


/// ---------------------------------------------------------------------------
/// \brief    Genera una notificacio d'ins d'un ISR
///
void eos::Task::raiseNotificationISR() {

	BaseType_t taskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(_handler, &taskWoken);
	portYIELD_FROM_ISR(taskWoken);
}


/// ---------------------------------------------------------------------------
/// \brief    Canvia la prioritat de la tasca.
/// \param    priority: La nova prioritat.
///
void eos::Task::setPriority(
	Priority priority) const {

	vTaskPrioritySet(_handler, getPriorityValue(priority));
}


/// ---------------------------------------------------------------------------
/// \brief    Comprova si la tasca es viva.
/// \return   True si no esta 'Deleted'
///
bool eos::Task::isAlive() const {

	return getState() != State::killed;
}


/// ---------------------------------------------------------------------------
/// \brief    Funcio de la tasca que executa el RTOS
/// \param    params: Parametres de la tasca. En aquest cas es
///           el punter 'this' del objecte 'Task'
///
void eos::Task::taskFunction(
	void *params) {

    Task *task = static_cast<Task*>(params);
    if (task != nullptr) {

    	task->_lastWeakTick = xTaskGetTickCount();

		if (task->_event != nullptr) {

			EventArgs args = {
			};
			task->_event->execute(task, &args);
		}

    	task->destroyHandler();
	}
}


/// ---------------------------------------------------------------------------
/// \brief    Obte la tasca que s'esta executant al cridar a aquest metode
/// \return   La tasca.
///
eos::Task* eos::Task::getExecutingTask() {

	return reinterpret_cast<Task*>(
		pvTaskGetThreadLocalStoragePointer(
			xTaskGetCurrentTaskHandle(),
			StorageIndex::ptrThis));
}


/// ---------------------------------------------------------------------------
/// @brief    Crea el handler de la tasca.
/// @param    stackDepht: profunditat de la pila.
/// @param    priority: Prioridat.
/// @param    name: Nom de la tasca.
///
TaskHandle_t eos::Task::createHandler(
	uint32_t stackDepth,
	Priority priority,
	const char *name) {

	TaskHandle_t handler;

    if ((xTaskCreate(
        taskFunction,
        name == nullptr ? _defaultName : name,
        stackDepth,
        this,
        getPriorityValue(priority),
        &handler) != pdPASS) || (handler == nullptr))
    	return nullptr;

    // Guarda el punter 'this' per recuperacio posterior en 'getExecutingTask'
    //
    vTaskSetThreadLocalStoragePointer(handler, StorageIndex::ptrThis, this);

    return handler;
}


/// ---------------------------------------------------------------------------
/// \brief    Destrueix el handler de la tasca.
///
void eos::Task::destroyHandler() {

	vTaskSetThreadLocalStoragePointer(_handler, StorageIndex::ptrThis, nullptr);
	vTaskDelete(_handler);
}


/// ---------------------------------------------------------------------------
/// \brief    Calcula el valor de prioritat per RTOS.
/// \param    priority: Prioritat.
/// \return   Valor numeric de la prioritat.
/// \notes    Atencio: El valor del enumerador Priority esta definit i no es
///           por canviar sense motiu.
///
uint32_t eos::Task::getPriorityValue(
	Priority priority) {

	return tskIDLE_PRIORITY + (uint32_t)priority - (uint32_t)Task::Priority::idle;
}
