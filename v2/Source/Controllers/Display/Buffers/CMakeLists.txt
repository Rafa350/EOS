target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosColorFrameBuffer.cpp
        #eosColorFrameBuffer_DMA2D.cpp
        eosFrameBuffer.cpp
        eosL1FrameBuffer.cpp
        eosL4FrameBuffer.cpp
)
