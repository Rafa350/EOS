target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosCanServer.cpp
        eosCanOpenService.cpp
        eosCanOpenDictionary.cpp
        eosCanOpenProtocol.cpp
)
