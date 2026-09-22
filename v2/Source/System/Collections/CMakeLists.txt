target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosFifoBuffer.cpp
        eosIntrusiveBidirectionalList.cpp
        eosIntrusiveForwardList.cpp
        eosLifoBuffer.cpp
        eosStack.cpp
)
