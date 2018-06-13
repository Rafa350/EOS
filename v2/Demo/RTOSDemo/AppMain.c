#include "eos.h"
#include "hal/halGPIO.h"
#include "osal/osalThread.h"
#include "osal/osalMsgQueue.h"


static HMsgQueue queue;


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #1
/// \param parameter: Parametre opcional.
///
static void task1(void *parameter) {
    
    halGPIOInitializePin(
        LED_LED1_PORT, 
        LED_LED1_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 
        HAL_GPIO_AF_NONE);
    
    while (true) {       
        halGPIOTogglePin(LED_LED1_PORT, LED_LED1_PIN);
        
        uint8_t data = 0;
        osalMsgQueuePut(queue, &data, 0);
        
        osalDelay(250);
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #2
/// \param parameter: Parametre opcional.
///
static void task2(void *parameter) {
    
    halGPIOInitializePin(
        LED_LED2_PORT, 
        LED_LED2_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 
        HAL_GPIO_AF_NONE);

    while (true) {    
        halGPIOTogglePin(LED_LED2_PORT, LED_LED2_PIN);
        osalDelay(350);        
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #3
/// \param parameter: Parametre opcional.
///
static void task3(void *parameter) {
    
    halGPIOInitializePin(
        LED_LED3_PORT, 
        LED_LED3_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, 
        HAL_GPIO_AF_NONE);

    while (true) {    
        
        uint8_t data;
        if (osalMsgQueueGet(queue, &data, 0))
            halGPIOTogglePin(LED_LED3_PORT, LED_LED3_PIN);
    }
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {
    
    TaskInitializeInfo taskInfo;    
    MsgQueueInitializeInfo queueInfo;
    
    // Inicialitza la cua de missatges
    //
    queueInfo.elementSize = sizeof(uint8_t);
    queueInfo.maxElements = 10;
    queue = osalMsgQueueCreate(&queueInfo);

    // Inicialitza els parametres comuns
    //
    taskInfo.options = OSAL_TASK_PRIORITY_NORMAL;
    taskInfo.stackSize = 512;    

    // Inicialitza la tasca #1
    //
    taskInfo.name = "task1";
    taskInfo.function = task1;
    taskInfo.params = (void*) 0;
    osalTaskCreate(&taskInfo);

    // Inicialitza la tasca #2
    //
    taskInfo.name = "task2";
    taskInfo.function = task2;
    taskInfo.params = (void*)0;
    osalTaskCreate(&taskInfo);
    
    // Inicialitza la tasca #3
    //
    taskInfo.name = "task3";
    taskInfo.function = task3;
    taskInfo.params = (void*)0;
    osalTaskCreate(&taskInfo);

    osalStartScheduler();
}
