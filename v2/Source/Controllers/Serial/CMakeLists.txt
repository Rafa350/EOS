target_sources(${TARGET_NAME} 
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosSerialDriver.cpp
        eosSerialDriverUART.cpp
        eosSerialDriverUARTDMA.cpp
)
