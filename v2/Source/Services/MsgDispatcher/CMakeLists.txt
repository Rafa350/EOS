 target_sources(${TARGET_NAME} 
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosMsgDispatcher.cpp
    PUBLIC
        eosMsgDispatcher_Service.cpp
        eosMsgDispatcher_Listener.cpp
)
