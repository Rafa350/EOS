#include "eosAssert.hpp"
#include "System/Core/eosTask.hpp"

#include "FreeRTOS.h"
#include "task.h"


using namespace eos;


static const char *defaultName = "";


/// ----------------------------------------------------------------------
/// \brief Constructor. Crea un objecte Task que encapsula una tasca
///        de FreeRTOS.
/// \param stackSize: Tamany de la pila.
/// \param priority: Prioritat del proces.
/// \param name: Nom de la tasca.
/// \param runable: Objecte que implementa IRunable.
///
Task::Task(
    unsigned stackSize, 
    TaskPriority priority,
    const char *name,
    IRunable *runable) {
    
    eosArgumentIsNotNull("runnable", runnable);
    
    this->runable = runable;
    
    xTaskCreate(
        Task::function, 
        name == nullptr ? defaultName : name, 
        stackSize, 
        this, 
        tskIDLE_PRIORITY + ((UBaseType_t) priority), 
        &handle);
    eosAssert(handle != nullptr);
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
        task->runable->run(task);
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
/// \brief Retarda la tasca actual un numero determinat de milisegons.
/// \param time: El numero de milisegons a retardar.
///
void Task::delay(
    unsigned time) {

    if (time > 0)
        vTaskDelay(time / portTICK_PERIOD_MS);    
}


/// ----------------------------------------------------------------------
/// \brief Retarda la tasca actual un numero determinat de milisegons.
/// \param time: El numero de milisegons a retardar.
/// \param lastTick: El valor de contador de ticks actualitzat.
///
void Task::delayUntil(
    unsigned time, 
    unsigned *lastTick) {
    
    eosArgumentIsNotNull("lastTick", lastTick);
    
    if (time > 0) 
        vTaskDelayUntil((TickType_t*) lastTick, time / portTICK_PERIOD_MS);
}


/// ----------------------------------------------------------------------
/// \brief Espera una notificacio interna de la tasca.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si hi ha notificacio, false en cas contrari.
///
bool Task::notificationTake(
    unsigned blockTime) {
    
    TickType_t ticks = blockTime == ((unsigned) -1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return ulTaskNotifyTake(pdTRUE, ticks) != 0;
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
/// \brief Inicia tots els fils d'execucio.
///
void Task::startAll() {
    
    vTaskStartScheduler();    
}


/// ----------------------------------------------------------------------
/// \brief Suspend tots els fils d'execucio. Impedeix el canvi de tasca
///
void Task::suspendAll() {
    
    vTaskSuspendAll();
}


/// ----------------------------------------------------------------------
/// \brief Activa tots els fils d'execucio
///
void Task::resumeAll() {

    xTaskResumeAll();
}
