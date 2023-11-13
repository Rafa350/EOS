#pragma once


// EOS includes
//
#include "HTL/htl.h"
#include "System/Graphics/eosColor.h"


namespace htl {
    
    namespace dma2d {

        /// \brief Format de color d'entrada.
        /// \remarks Els valors corresponen al registre hardware. No modificar.
        ///
        enum class InputColorMode {
            argb8888 = 0,
            rgb888 = 1,
            rgb565 = 2,
            argb1555 = 3,
            argb4444 = 4,
            l8 = 5,
            al44 = 6,
            al88 = 7,
            l4 = 8,
            a8 = 9,
            a4 = 10
        };

        /// \brief Format de color de sortida.
        /// \remarks Els valors corresponen al registre hardware. No modificar.
        ///
        enum class OutputColorMode {
            argb8888 = 0,
            rgb888 = 1,
            rgb565 = 2,
            argb1555 = 3,
            argb4444 = 4
        };
        

        class DMA2DDevice final {
            private:
                static DMA2DDevice _instance;
            private:
                DMA2DDevice();
                DMA2DDevice(const DMA2DDevice &) = delete;
                DMA2DDevice(const DMA2DDevice &&) = delete;
                DMA2DDevice & operator = (const DMA2DDevice &) = delete;
                DMA2DDevice & operator = (const DMA2DDevice &&) = delete;
                void activate();
                void deactivate();
            public:
                void initialize();
                void deinitialize();
                void startFill(void *ptr, uint16_t width, uint16_t height, uint16_t pitch, OutputColorMode colorMode, uint32_t color);
                void startCopy(void *ptr, uint16_t width, uint16_t height, uint16_t pitch, OutputColorMode colorMode, const void *src, uint16_t srcPitch, InputColorMode srcColorMode);
                bool waitForFinish();
				void interruptService();
				static constexpr DMA2DDevice * getHandler() {
					return &_instance;
				}
                inline static void interruptHandler() {
                    getHandler()->interruptService();
                }
        };

        typedef DMA2DDevice *DMA2DDeviceHandler;

    }
}
