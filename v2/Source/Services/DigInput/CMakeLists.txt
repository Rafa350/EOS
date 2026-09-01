target_sources(${TARGET_NAME} 
    PUBLIC 
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            eosDigInputService.cpp
    PRIVATE
        eosDigInputService_Service.cpp
        eosDigInputService_Input.cpp
)
