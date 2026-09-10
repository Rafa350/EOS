target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosSerialDriverUART.cpp
        eosSerialDriverUARTDMA.cpp
)
