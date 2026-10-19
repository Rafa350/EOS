target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
        FILES
            app_application.cpp
)

target_sources(${TARGET_NAME}
    PRIVATE
        boot_main.cpp
)

add_subdirectory("STM32F4")
add_subdirectory("Services")
