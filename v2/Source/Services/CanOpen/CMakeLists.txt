target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosCanServer.cpp
        eosCanOpenService.cpp
        eosCanOpenDictionary.cpp
        eosCanOpenProtocol.cpp
)
