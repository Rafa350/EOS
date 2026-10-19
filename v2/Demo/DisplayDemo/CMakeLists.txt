cmake_minimum_required(VERSION 4.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)


project(DisplayDemo LANGUAGES C CXX ASM)


set(TARGET_NAME "DisplayDemo")

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(EOS_DIR ${ROOT_DIR}/Libraries/EOS/Source)
set(LIB_DIR ${ROOT_DIR}/Libraries/EOS/Library/STM32F4)


set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)


add_executable(${TARGET_NAME})

add_subdirectory("Application")
add_subdirectory("Libraries")

target_compile_options(${TARGET_NAME} PRIVATE
    ${CPU_PARAMETERS}
    $<$<CONFIG:Release>:
        -Os
        -g0
    >
    $<$<CONFIG:Debug>:
        -Og
        -g3
        -ggdb
    >
    -c
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wno-switch
    -fstack-usage
)

target_compile_definitions(${TARGET_NAME} PRIVATE
    HARDWARE_STM32F429I_DISC1
    BUILD_ILI9341_SPI
    EOS_NO_INCLUDE_BOARD
    $<$<CONFIG:Debug>:EOS_DEBUG>
    ${EOS_PLATFORM_NAME}
)

target_link_options(${TARGET_NAME} PRIVATE
    ${CPU_PARAMETERS}
    -T${ROOT_DIR}/Build/STM32G0B1KC_FLASH.ld
    -Wl,--cref
    -Wl,-Map=${TARGET_NAME}.map
    -Wl,--gc-sections
    -static
    --specs=nosys.specs
)

target_include_directories(${TARGET_NAME} PRIVATE
    Application/Include
    Application/Include/STM32F4
    Libraries/EOS/Source/Hardware
    Libraries/EOS/Include
    Libraries/EOS/Library/STM32F4/CMSIS_DEVICE/Include
    Libraries/EOS/Library/STM32F4/CMSIS_CORE/Include
    Libraries/EOS/Library/STM32F4/HAL/Inc
    Libraries/EOS/Library/STM32F4/FreeRTOS/Include
    Libraries/EOS/Library/STM32F4/FreeRTOS/portable/GCC/ARM_CM4F
    Libraries/EOS/Library/STM32F4/FreeRTOS/CMSIS_RTOS_V2
)

target_sources(${TARGET_NAME} PRIVATE
    ${LIB_DIR}/CMSIS_DEVICE/Source/Templates/gcc/startup_stm32f429xx.s
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
        COMMAND ${CMAKE_CXX_FILT}
            < ${PROJECT_NAME}.map
            > ${PROJECT_NAME}-demangled.map
)

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET_NAME}>
)
