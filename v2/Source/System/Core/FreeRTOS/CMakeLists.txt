target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosCriticalSection.cpp
        eosHeapAllocator.cpp
        eosKernel.cpp
        eosQueue.cpp
        eosSemaphore.cpp
        eosTask.cpp
        eosTimer.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        eosRTOSHooks.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        ${LIB_DIR}/FreeRTOS/list.c
        ${LIB_DIR}/FreeRTOS/queue.c
        ${LIB_DIR}/FreeRTOS/tasks.c
        ${LIB_DIR}/FreeRTOS/timers.c
        ${LIB_DIR}/FreeRTOS/portable/MemMang/heap_1.c
        ${LIB_DIR}/FreeRTOS/portable/GCC/ARM_CM0/port.c
)
