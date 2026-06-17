add_subdirectory("CanOpen")
add_subdirectory("DigInput")
add_subdirectory("DigOutput")
add_subdirectory("MsgDispatcher")

target_sources(${TARGET_NAME} PUBLIC 
    eosLedService.cpp
    eosService.cpp
)