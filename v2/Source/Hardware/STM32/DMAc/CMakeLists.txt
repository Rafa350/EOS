target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        dma.cpp
        dma_types.cpp
        dma_class.cpp
        dma_template.cpp
        DMA_DeviceTraits.cpp
        DMA_PlatformTraits.cpp
)
