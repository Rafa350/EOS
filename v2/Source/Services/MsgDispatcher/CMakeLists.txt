 target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        MsgDispatcher.cpp
    PUBLIC
        MsgDispatcher_Service.impl.cpp
        MsgDispatcher_Listener.impl.cpp
)
