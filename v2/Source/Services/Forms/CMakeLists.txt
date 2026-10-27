target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Forms.cpp
        PropertyObserver.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        Forms_Control.impl.cpp
        Forms_Form.impl.cpp
        Forms_Service.impl.cpp
        Forms_Visual.impl.cpp
)

add_subdirectory("Controls")
