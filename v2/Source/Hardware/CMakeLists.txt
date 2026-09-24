target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosAtomic.cpp
        eosRegs.cpp
)

add_subdirectory("TMR")
add_subdirectory("UART")
