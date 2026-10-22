target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        AppApplication.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        AppMain.cpp
)

add_subdirectory("STM32F4")
add_subdirectory("Services")
