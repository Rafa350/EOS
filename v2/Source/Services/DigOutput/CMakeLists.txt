target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DigOutput.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        DigOutput_Service.impl.cpp
        DigOutput_Output.impl.cpp
)
