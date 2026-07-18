add_subdirectory("Controls")

target_sources(${TARGET_NAME} PRIVATE
    eosControl.cpp
    eosForm.cpp
    eosFormsService.cpp
)