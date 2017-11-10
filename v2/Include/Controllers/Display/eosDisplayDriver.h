#ifndef __eosDisplayDriver__
#define __eosDisplayDriver__


#include "eos.h"
#include "Controllers/Display/eosColor.h"

#include <stdint.h>


namespace eos {

	/// \brief Orientacio de la pantalla.
	enum class DisplayOrientation {
		normal,
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
            virtual int16_t getWidth() const = 0;
            virtual int16_t getHeight() const = 0;
            virtual void clear(const Color &color) = 0;
            virtual void setPixel(int16_t x, int16_t y, const Color &color) = 0;
            virtual void setHPixels(int16_t x, int16_t y, int16_t length, const Color &color) = 0;
            virtual void setVPixels(int16_t x, int16_t y, int16_t length, const Color &color) = 0;
            virtual void setPixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color &color) = 0;
            virtual void writePixels(int16_t x, int16_t y, int16_t width, int16_t height, const Color *colors) = 0;
            virtual void readPixels(int16_t x, int16_t y, int16_t width, int16_t height, Color *colors) = 0;
            virtual void vScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height) = 0;
            virtual void hScroll(int16_t delta, int16_t x, int16_t y, int16_t width, int16_t height) = 0;
    };

}


#endif // __eosDisplayDriver__
