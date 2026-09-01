target_sources(${TARGET_NAME}
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            eosDigOutputService.cpp
    PRIVATE
        eosDigOutputService_Service.cpp
        eosDigOutputService_Output.cpp
)
