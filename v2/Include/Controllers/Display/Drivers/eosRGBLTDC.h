#ifndef __eosRGBLTDC__
#define	__eosRGBLTDC__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Controllers/Display/eosColorFrameBuffer.h"
#include "Controllers/Display/eosDisplayDriver.h"


#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH       480       // Tamany fix del controlador
#endif

#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT      272       // Tamany fix del controlador
#endif

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

    typedef PIXEL_TYPE pixel_t;

	class RGBDirectDriver: public IDisplayDriver {
    	private:
    		ColorFrameBuffer *frontFrameBuffer;
    		ColorFrameBuffer *backFrameBuffer;
    		int frontFrameAddr;
    		int backFrameAddr;

        public:
            RGBDirectDriver();

            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;

            inline int getWidth() const override { return frontFrameBuffer->getWidth(); }
            inline int getHeight() const override { return frontFrameBuffer->getHeight(); }

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
            void initializeGPIO();
            void initializeLTDC();
    };
}

#endif // __eosRGBDirect__
