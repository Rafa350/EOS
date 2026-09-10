target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosEEPROMDriver.cpp)

add_subdirectory("Drivers")
