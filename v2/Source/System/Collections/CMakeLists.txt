target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        buffer_fifo.cpp
        buffer_lifo.cpp
        buffer_circular.cpp
        eosIntrusiveBidirectionalList.cpp
        eosIntrusiveForwardList.cpp
        eosStack.cpp
)
