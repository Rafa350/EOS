cmake_minimum_required(VERSION 4.0)

# Setup compiler settings
set(CMAKE_C_STANDARD                17)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(CMAKE_CXX_SCAN_FOR_MODULES      ON)

#
# Core project settings
#
project(EOS)
enable_language(C CXX ASM)

message("+-------------------------------------------------------------------------")
message("| Build info:")
message("|     Build type       : ${CMAKE_BUILD_TYPE}")
message("|")
message("| Compiler:")
message("|     Toolchain file   : ${CMAKE_TOOLCHAIN_FILE}")
message("|     Assembler        : ${CMAKE_ASM_COMPILER}")
message("|     C compiler       : ${CMAKE_C_COMPILER}")
message("|     C++ compiler     : ${CMAKE_CXX_COMPILER}")
message("|     Compiler id      : ${CMAKE_CXX_COMPILER_ID}")
message("|     Compiler version : ${CMAKE_CXX_COMPILER_VERSION}")
message("|")
message("| CMAKE_CXX flags info:")
message("|     CMAKE_CXX_FLAGS                ${CMAKE_CXX_FLAGS}")
message("|     CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG}")
message("|     CMAKE_CXX_FLAGS_MINSIZEREL     ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("|     CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE}")
message("|     CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("+-------------------------------------------------------------------------")


# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
#
set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m0plus
    -mfloat-abi=soft
)


# Set linker script
#
set(linker_script_file              ${PROJ_PATH}/Build/STM32G071RB_FLASH.ld)


# Project options
#
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
set(EOS_PATH                        ${CMAKE_CURRENT_SOURCE_DIR}/..)


# Include directories
#
set(include_dirs
    ${PROJ_PATH}/../BuildCMake
    ${EOS_PATH}/Include
    ${EOS_PATH}/Library/STM32G0/CMSIS_CORE/Include
    ${EOS_PATH}/Library/STM32G0/CMSIS_DEVICE/Include
    ${EOS_PATH}/Library/STM32G0/FreeRTOS/Include
    ${EOS_PATH}/Library/STM32G0/FreeRTOS/Portable/GCC/ARM_CM0
    ${EOS_PATH}/Library/STM32G0/FreeRTOS/CMSIS_RTOS_V2
)


# Symbols definition
#
set(symbol_definitions
    -DSTM32G071RB
    -DEOS_NO_INCLUDE_BOARD
)

# Target
add_library(${CMAKE_PROJECT_NAME} STATIC)

# Sources
#
add_subdirectory("HTLMod")
#add_subdirectory(System)

# Include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${include_dirs})

# Project symbols
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ${symbol_definitions})

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter

    # Full debug configuration
    -Og -g3 -ggdb
)
