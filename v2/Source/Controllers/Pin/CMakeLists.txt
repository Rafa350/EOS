target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosPinDriver.cpp
)

add_subdirectory("GPIO")
