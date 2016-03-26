#include "System/Core/eosTask.hpp"
#include "FreeRTOS.h"
#include "task.h"


using namespace eos;


static const char *defaultTaskName = "";


/// ----------------------------------------------------------------------
/// \brief Constructor. Crea un objecte Task que encapsula una tasca
///        de FreeRTOS.
/// \param stackSize: Tamany de la pila.
/// \param priority: Prioritat del proces.
/// \param runable: Objecte que implementa IRunable.
///
Task::Task(
    unsigned stackSize, 
    TaskPriority priority,
    IRunable *runable) {
    
    this->runable = runable;
    
    xTaskCreate(
        Task::function, 
        defaultTaskName, 
        stackSize, 
        this, 
        tskIDLE_PRIORITY + unsigned(priority), 
        &handle);
}


/// ----------------------------------------------------------------------
/// \brief Destructor. Destrueix la tasca de FreeRTOS asociada.
///
Task::~Task() {
    
    vTaskDelete(handle);
}


/// ----------------------------------------------------------------------
/// \brief Executa la funcio de la tasca.
/// \param params: El handler de la tasca.
///
void Task::function(
    void *params) {
    
    Task *task = reinterpret_cast<Task*>(params);
    while (true) 
        task->runable->run();
}


/// ----------------------------------------------------------------------
/// \brief Retorna el numero te ticks transcurreguts desde la 
///        inicialitzacio del sistema.
/// \return El numero de ticks.
///
unsigned Task::getTickCount() {

    return xTaskGetTickCount();   
}


/// ----------------------------------------------------------------------
/// \brief Retarda la tasca actual un numero determinat de ticks.
/// \param time: El numero de ticks a retardar.
///
void Task::delay(
    unsigned time) {

    if (time > 0)
        vTaskDelay((TickType_t) time);    
}


void Task::delayUntil(
    unsigned time, 
    unsigned *lastTick) {
    
    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, (TickType_t) time);
}


/// ----------------------------------------------------------------------
/// \brief Entra en una seccio critica
///
void Task::enterCriticalSection() {

    taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief Surt d'una seccio critica
///
void Task::exitCriticalSection() {
    
    taskEXIT_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief Suspend tots els fils d'execucio. Imprideix el canvi de tasca
///
void Task::suspendAllThreads() {
    
    vTaskSuspendAll();
}


/// ----------------------------------------------------------------------
/// \brief Activa tots els fils d'execucio
///
void Task::resumeAllThreads() {

    xTaskResumeAll();
}
