 target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosMsgDispatcher.cpp
    PUBLIC
        eosMsgDispatcher_Service.cpp
        eosMsgDispatcher_Listener.cpp
)
