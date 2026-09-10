target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDigOutputService.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        eosDigOutputService_Service.cpp
        eosDigOutputService_Output.cpp
)
