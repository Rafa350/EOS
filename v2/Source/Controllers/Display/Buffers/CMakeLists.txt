if(EOS_USE_BUFFER_RGBLTDC)
target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        BufferColor.cpp
        #BufferColorDMA2D.cpp
)
endif()

if(EOS_USE_BUFFER_L1)
    target_sources(${TARGET_NAME}
        PUBLIC FILE_SET CXX_MODULES FILES
            BufferL1.cpp
    )
endif()

if(EOS_USE_BUFFER_L4)
    target_sources(${TARGET_NAME}
        PUBLIC FILE_SET CXX_MODULES FILES
            BufferL4.cpp
    )
endif()
