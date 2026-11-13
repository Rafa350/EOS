target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        BufferL1.cpp
        BufferL4.cpp
        BufferColor.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32429")
    target_sources(${TARGET_NAME}
        PUBLIC FILE_SET CXX_MODULES FILES
            BufferColorDMA2D.cpp
    )
endif()
