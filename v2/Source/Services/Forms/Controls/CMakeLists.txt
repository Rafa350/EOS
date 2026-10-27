target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        BooleanControl.cpp
        MenuControl.cpp
        NumericControl.cpp
        SelectionControl.cpp
        TextBoxControl.cpp
)
