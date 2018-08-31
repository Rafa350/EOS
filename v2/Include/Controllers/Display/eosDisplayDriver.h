#ifndef __eosDisplayDriver__
#define __eosDisplayDriver__


// EOS includes
//
#include "eos.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	/// \brief Orientacio de la pantalla.
	enum class DisplayOrientation {
		normal = 0,
	    rotate0 = normal,
		rotate90,
		rotate180,
		rotate270,
	};

    /// \brief Interficie del driver del display.
    class IDisplayDriver {
        public:
    		virtual ~IDisplayDriver() {}

            virtual void initialize() = 0;
            virtual void shutdown() = 0;
            virtual void displayOn() = 0;
            virtual void displayOff() = 0;
            virtual void setOrientation(DisplayOrientation orientation) = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
            virtual void clear(const Color &color) = 0;
            virtual void setPixel(int x, int y, const Color &color) = 0;
            virtual void setHPixels(int x, int y, int length, const Color &color) = 0;
            virtual void setVPixels(int x, int y, int length, const Color &color) = 0;
            virtual void setPixels(int x, int y, int width, int height, const Color &color) = 0;
            virtual void writePixels(int x, int y, int width, int height, const uint8_t *pixels, PixelFormat format, int dx, int dy, int picth) = 0;
            virtual void readPixels(int x, int y, int width, int height, uint8_t *pixels, PixelFormat format) = 0;
            virtual void vScroll(int delta, int x, int y, int width, int height) = 0;
            virtual void hScroll(int delta, int x, int y, int width, int height) = 0;
    };

}


#endif // __eosDisplayDriver__
