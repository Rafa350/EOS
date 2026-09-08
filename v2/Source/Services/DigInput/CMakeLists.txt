target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosDigInputService.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        eosDigInputService_Service.cpp
        eosDigInputService_Input.cpp
)
