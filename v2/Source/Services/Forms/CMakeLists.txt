target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosFormsService.cpp
        eosPropertyObserver.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        eosFormsService_Control.cpp
        eosFormsService_Form.cpp
        #eosFormsService_Properties.cpp
        eosFormsService_Service.cpp
        eosFormsService_Visual.cpp
)

add_subdirectory("Controls")
