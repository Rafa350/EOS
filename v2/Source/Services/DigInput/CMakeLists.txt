target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DigInput.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        DigInput_Service.impl.cpp
        DigInput_Input.impl.cpp
)
