target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
        FILES
            eosService.cpp
            eosLedService.cpp
)

if(EOS_USE_SERVICE_CANOPEN)
    add_subdirectory("CanOpen")
endif()

if(EOS_USE_SERVICE_DIGINPUT)
    add_subdirectory("DigInput")
endif()

if(EOS_USE_SERVICE_DIGOUTPUT)
    add_subdirectory("DigOutput")
endif()

if(EOS_USE_SERVICE_FORMS)
    add_subdirectory("Forms")
endif()

if(EOS_USE_SERVICE_MSGDISPATCHER)
    add_subdirectory("MsgDispatcher")
endif()
