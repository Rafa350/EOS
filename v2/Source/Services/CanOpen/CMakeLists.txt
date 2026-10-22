target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        #eosCanServer.cpp
        CanOpen.cpp
        CanOpenDictionary.cpp
        CanOpenProtocol.cpp
    PUBLIC
        CanOpen_IO.impl.cpp
        CanOpen_LocalDict.impl.cpp
        CanOpen_RemoteDict.impl.cpp
        CanOpen_NodeCtrl.impl.cpp
)
