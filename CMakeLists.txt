cmake_minimum_required(VERSION 3.27)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_PATH                        ${PROJ_PATH}/v2/Source)
set(INC_PATH                        ${PROJ_PATH}/v2/Include)
set(PROJECT_NAME                    ${CMAKE_PROJECT_NAME})                  

message("Build type   : " ${CMAKE_BUILD_TYPE})
message("Project path : " ${PROJ_PATH})           
message("Source path  : " ${SRC_PATH})           
message("Include path : " ${INC_PATH})           


# Core project settings
set (CMAKE_C_COMPILER_WORKS 1)
set (CMAKE_CXX_COMPILER_WORKS 1)


project(EOS)
enable_language(C CXX ASM)

set(INC_DIRS 
    ${INC_PATH}
    ${PROJ_PATH}/v2/Library/STM32G0/CMSIS_CORE/Include
    ${PROJ_PATH}/v2/Library/STM32G0/CMSIS_DEVICE/Include
)

set(SRC_FILES
    ${SRC_PATH}/HTL/STM32/htlGPIO.cpp
    ${SRC_PATH}/HTL/STM32/htlI2CSlave.cpp
    ${SRC_PATH}/HTL/STM32/htlINT.cpp
    ${SRC_PATH}/HTL/STM32/htlSPI.cpp
    ${SRC_PATH}/HTL/STM32/htlTMR.cpp
    ${SRC_PATH}/HTL/STM32/htlUART.cpp
    ${SRC_PATH}/HTL/STM32/G0/htlClock.cpp
 )
    
 set(COMPILER_DEFINES
    STM32    
    STM32G0
    STM32G071RB
    STM32G071xx
    EOS_NO_INCLUDE_CONFIG
    EOS_NO_INCLUDE_BOARD
)

set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m0plus
    -mfpu=fpv5-d16
    -mfloat-abi=soft
)

set(COMPILER_OPTIONS
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -Og -g3 -ggdb
)

    
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILER_DEFINES})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_OPTIONS})
