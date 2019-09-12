#ifndef __eosRGBLTDC__
#define	__eosRGBLTDC__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"
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

#define PIXEL_FORMAT              PixelFormat::rgb888
#define PIXEL_TYPE                uint32_t

#elif defined(DISPLAY_COLOR_RGB565)
// Format Pixel RGB565
#define PIXEL_MASK_R              COLOR_RGB565_MASK_R
#define PIXEL_MASK_G              COLOR_RGB565_MASK_G
#define PIXEL_MASK_B              COLOR_RGB565_MASK_B

#define PIXEL_SHIFT_R             COLOR_RGB565_SHIFT_R
#define PIXEL_SHIFT_G             COLOR_RGB565_SHIFT_G
#define PIXEL_SHIFT_B             COLOR_RGB565_SHIFT_B

#define PIXEL_FORMAT              PixelFormat::rgb565
#define PIXEL_TYPE                uint16_t
#endif


namespace eos {

	class Pixel {
		private:
		   PIXEL_TYPE d;

		public:
		   inline Pixel(): d(0) {}
		   inline Pixel(uint8_t r, uint8_t g, uint8_t b): d((r << PIXEL_SHIFT_R) | (g << PIXEL_SHIFT_G) | (g << PIXEL_SHIFT_B)) {}
		   inline Pixel(PIXEL_TYPE d): d(d) {}
		   inline Pixel(const Color &color): d((color.getR() << PIXEL_SHIFT_R) | (color.getG() << PIXEL_SHIFT_G) | (color.getB() << PIXEL_SHIFT_B)) {}

		   inline uint8_t getR() const { return (d & PIXEL_MASK_R) >> PIXEL_SHIFT_R; }
		   inline uint8_t getG() const { return (d & PIXEL_MASK_G) >> PIXEL_SHIFT_G; }
		   inline uint8_t getB() const { return (d & PIXEL_MASK_B) >> PIXEL_SHIFT_B; }

		   inline void combine(const Pixel &p, uint8_t o) {
			    d =
			    	((((getR() * o) + (p.getR() * (255 - o))) >> 8) << PIXEL_SHIFT_R) |
					((((getG() * o) + (p.getG() * (255 - o))) >> 8) << PIXEL_SHIFT_G) |
					((((getB() * o) + (p.getB() * (255 - o))) >> 8)<< PIXEL_SHIFT_B);
		   }

		   inline operator PIXEL_TYPE() const { return d; }
	};

	class RGBDirectDriver: public IDisplayDriver {
    	private:
    		static IDisplayDriver *instance;
    		int screenWidth;
    		int screenHeight;
    		DisplayOrientation orientation;
    		int frontFrameAddr;
    		int backFrameAddr;

    	private:
            RGBDirectDriver();

        public:
            static IDisplayDriver *getInstance();
            void initialize() override;
            void shutdown() override;
            void displayOn() override;
            void displayOff() override;
            void setOrientation(DisplayOrientation orientation) override;
            int getWidth() const override { return screenWidth; }
            int getHeight() const override { return screenHeight; }
            void clear(const Color &color) override;
            void setPixel(int x, int y, const Color &color) override;
            void setHPixels(int x, int y, int size, const Color &color) override;
            void setVPixels(int x, int y, int size, const Color &color) override;
            void setPixels(int x, int y, int width, int height, const Color &color) override;
            void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch) override;
            void vScroll(int delta, int x, int y, int width, int height) override;
            void hScroll(int delta, int x, int y, int width, int height) override;
            void refresh() override;

        private:
            void gpioInitialize();
            void ltdcInitialize();
            void rotate(int &x, int &y);
            void rotate(int &x1, int &y1, int &x2, int &y2);
            void put(int x, int y, const Color &color);
            void fill(int x, int y, int width, int height, const Color &color);
            void copy(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int pitch);
    };
}

#endif // __eosRGBDirect__
