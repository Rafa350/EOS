#ifndef __eosILI9341LTDC__
#define	__eosILI9341LTDC__


#include "eos.h"
#include "Controllers/Display/eosDisplayDriver.h"
#include "Controllers/Display/eosFrameBuffer_RGB565_DMA2D.h"


#if !defined(DISPLAY_COLOR_RGB565) && !defined(DISPLAY_COLOR_RGB888)
	#error Formato de color no soportado
#endif


#ifndef DISPLAY_SCREEN_WIDTH
#define DISPLAY_SCREEN_WIDTH      240  // Tamany fix del controlador
#endif
#ifndef DISPLAY_SCREEN_HEIGHT
#define DISPLAY_SCREEN_HEIGHT     320  // Tamany fix del controlador
#endif


#if defined(DISPLAY_COLOR_RGB565)
typedef int16_t pixel_t;
#elif defined(DISPLAY_COLOR_RGB888)
typedef int32_t pixel_t;
#endif
#define PIXEL_SIZE                sizeof(pixel_t)
#define LINE_SIZE                 (((DISPLAY_SCREEN_WIDTH * PIXEL_SIZE) + 63) & 0xFFFFFFC0)
#define LINE_WIDTH                (LINE_SIZE / PIXEL_SIZE)
#define FRAME_SIZE                (LINE_SIZE * DISPLAY_SCREEN_HEIGHT)

#if defined(DISPLAY_COLOR_RGB888)
// Format Pixel RGB888
#define PIXEL_MASK_R              COLOR_RGB888_MASK_R
#define PIXEL_MASK_G              COLOR_RGB888_MASK_G
#define PIXEL_MASK_B              COLOR_RGB888_MASK_B
#define PIXEL_SHIFT_R             COLOR_RGB888_SHIFT_R
#define PIXEL_SHIFT_G             COLOR_RGB888_SHIFT_G
#define PIXEL_SHIFT_B             COLOR_RGB888_SHIFT_B
#define PIXEL_FORMAT              ColorFormat::rgb888
#define PIXEL_TYPE                uint32_t

#elif defined(DISPLAY_COLOR_RGB565)
// Format Pixel RGB565
#define PIXEL_MASK_R              COLOR_RGB565_MASK_R
#define PIXEL_MASK_G              COLOR_RGB565_MASK_G
#define PIXEL_MASK_B              COLOR_RGB565_MASK_B
#define PIXEL_SHIFT_R             COLOR_RGB565_SHIFT_R
#define PIXEL_SHIFT_G             COLOR_RGB565_SHIFT_G
#define PIXEL_SHIFT_B             COLOR_RGB565_SHIFT_B
#define PIXEL_FORMAT              ColorFormat::rgb565
#define PIXEL_TYPE                uint16_t
#endif

namespace eos {
    
    class Color;

    class ILI9341LTDCDriver: public IDisplayDriver {
        private:
    		static IDisplayDriver *instance;
            ColorFrameBuffer* frameBuffer;

        public:
            static IDisplayDriver *getInstance();;
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const override { return frameBuffer->getWidth(); }
            int getHeight() const override { return frameBuffer->getHeight(); }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, ColorFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            ILI9341LTDCDriver();
            void displayInit();
            void writeCommands(const uint8_t *dada);

        private:
            void initializeLTDC();
            void lcdInitialize();
            void lcdReset();
            void lcdOpen();
            void lcdClose();
            void lcdWriteCommand(uint8_t d);
            void lcdWriteData(uint8_t d);
    };
}


#endif // __eos_ILI9341LTDC__
