#include "eos.h"
#include "HAL/halGPIO.h"
#include "OSAL/osalTask.h"
#include "OSAL/osalKernel.h"
#include "OSAL/osalQueue.h"


static HQueue queue;


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #1
/// \param parameter: Parametre opcional.
///
static void task1(void *parameter) {

    halGPIOInitializePin(
        LEDS_LED1_PORT,
        LEDS_LED1_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR,
        HAL_GPIO_AF_NONE);

    bool state = false;
    while (true) {
        halGPIOWritePin(LEDS_LED1_PORT, LEDS_LED1_PIN, state);
        if (state) {
            uint8_t data = 1;
            osalQueuePut(queue, &data, 0);
        }
        state = !state;

        osalDelay(1000);
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #2
/// \param parameter: Parametre opcional.
///
static void task2(void *parameter) {

    halGPIOInitializePin(
        LEDS_LED2_PORT,
        LEDS_LED2_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR,
        HAL_GPIO_AF_NONE);

    osalDelay(500);

    bool state = false;
    while (true) {
        halGPIOWritePin(LEDS_LED2_PORT, LEDS_LED2_PIN, state);
        if (state) {
            uint8_t data = 0;
            osalQueuePut(queue, &data, 0);
        }
        state = !state;

        osalDelay(1000);
    }
}


/// ----------------------------------------------------------------------
/// \brief Funcio de la tasca #3
/// \param parameter: Parametre opcional.
///
static void task3(void *parameter) {

    halGPIOInitializePin(
        LEDS_LED3_PORT,
        LEDS_LED3_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR,
        HAL_GPIO_AF_NONE);

    while (true) {

        uint8_t data;
        if (osalQueueGet(queue, &data, (unsigned)(-1)))
            halGPIOWritePin(LEDS_LED3_PORT, LEDS_LED3_PIN, data);
    }
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

    TaskInitializeInfo taskInfo;

    // Inicialitza la cua de missatges
    //
    queue = osalQueueCreate(10, sizeof(uint8_t));

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
