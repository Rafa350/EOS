target_sources(${TARGET_NAME} 
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosService.cpp
        eosLedService.cpp
)
    
add_subdirectory("CanOpen")
add_subdirectory("DigInput")
add_subdirectory("DigOutput")
#add_subdirectory("Forms")
#add_subdirectory("MsgDispatcher")
