#ifndef __appDisplayService__
#define __appDisplayService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Graphics/eosText.h"


namespace eos {

	class IDisplayDriver;
	class Graphics;
}


namespace app {

	class DisplayService: public eos::Service {
	    private:
			static constexpr uint32_t _displayWidth = DISPLAY_WIDTH;
			static constexpr uint32_t _displayHeight = DISPLAY_HEIGHT;
			static constexpr uint32_t _displayBuffer = DISPLAY_BUFFER;

			eos::IDisplayDriver *_driver;
	        eos::Graphics *_graphics;
	        eos::Text _text;
	        int _maxX;
	        int _maxY;
	        int _orientation;
	        int _loopCount;

	        int _pointsTicks;
	        int _horizontalLinesTicks;
	        int _verticalLinesTicks;
	        int _linesTicks;
	        int _rectanglesTicks;
	        int _filledRectanglesTicks;
	        int _ellipsesTicks;
	        int _filledEllipsesTicks;
	        int _polygonsTicks;
	        int _filledPolygonsTicks;
	        int _bitmapTicks;

	    public:
	        DisplayService();

	    protected:
	        void onInitialize();
	        void onTask();

	    private:
	        void drawBackground(const char *title);
	        void testColors();
	        void testOpacity();
	        void testPoints();
	        void testLines();
	        void testThickLines();
	        void testRectangles();
	        void testEllipses();
	        void testPolygons();
	        void testBitmaps();
	};

}


#endif // __appDisplayService__
