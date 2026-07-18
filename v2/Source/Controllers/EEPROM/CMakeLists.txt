add_subdirectory("Drivers")

target_sources(${TARGET_NAME} PRIVATE
    eosEEPROMDriver.cpp
)
