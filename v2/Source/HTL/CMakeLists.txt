cmake_minimum_required(VERSION 4.0)


set (EOS_HTL_TARGET_NAME "EOS_HTL_${PLATFORM_NAME}")

add_library(${EOS_HTL_TARGET_NAME} STATIC)

if(${PLATFORM_NAME} MATCHES "^STM32")
	add_subdirectory("STM32")
elseif(${PLATFORM_NAME} MATCH "^PIC32")
	add_subdirectory("PIC32")
endif()

target_include_directories(${EOS_HTL_TARGET_NAME} PUBLIC
	${EOS_INCLUDE_DIRS})

target_compile_definitions(${EOS_HTL_TARGET_NAME} PUBLIC
	${symbol_definitions})

target_compile_options(${EOS_HTL_TARGET_NAME} PUBLIC
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter

    # Full debug configuration
    -Og -g3 -ggdb
)
