add_subdirectory("Drivers")

target_sources(${TARGET_NAME} PRIVATE
    eosColorFrameBuffer.cpp
    eosFrameBuffer.cpp
    eosMonoFrameBuffer.cpp
)

if (EOS_PLATFORM_NAME EQUAL "STM32F429ZI")
target_sources(${TARGET_NAME} PRIVATE
    eosColorFrameBuffer_DMA2D.cpp
)
endif()
