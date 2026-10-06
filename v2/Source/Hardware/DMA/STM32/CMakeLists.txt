target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        dma.cpp
        dma_class.cpp
        dma_template.cpp
        dma_device_traits.cpp
        dma_platform_traits.cpp
)
