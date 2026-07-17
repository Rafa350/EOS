# ------------------------------------------------------------------------
# Afegeix els moduls RTOS

target_sources(${TARGET_NAME} PUBLIC
    rtosCriticalSection.cpp
    rtosGlobalAlloc.cpp
    rtosHeap.cpp
    rtosKernel.cpp
    rtosPool.cpp
    rtosQueue.cpp
    rtosSemaphore.cpp
    rtosStaticSupport.cpp
    rtosTask.cpp
    rtosTime.cpp
    rtosTimer.cpp
)


# ------------------------------------------------------------------------
# Afegeix els moduls especifics per FreeRTOS
#
set(FREERTOS_DIR ${LIB_DIR}/FreeRTOS)

target_sources(${TARGET_NAME} PUBLIC 
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/portable/MemMang/heap_1.c
    FreeRTOS/rtosHooks.cpp
)

target_sources(${TARGET_NAME} PUBLIC 
    ${FREERTOS_DIR}/portable/GCC/ARM_CM0/port.c
)
