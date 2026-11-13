target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        Display.cpp
    PUBLIC
        Display_Buffer.impl.cpp
)

add_subdirectory("Drivers")
add_subdirectory("Buffers")
