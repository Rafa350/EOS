target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        Forms.cpp
        PropertyObserver.cpp
    PUBLIC
        Forms_Control.impl.cpp
        Forms_Form.impl.cpp
        Forms_Service.impl.cpp
        Forms_Visual.impl.cpp
)

add_subdirectory("Controls")
