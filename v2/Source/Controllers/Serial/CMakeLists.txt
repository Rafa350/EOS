target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosSerialDriver.cpp
)

add_subdirectory("UART")
