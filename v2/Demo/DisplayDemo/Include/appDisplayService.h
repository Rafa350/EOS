#ifndef __appDisplayService__
#define __appDisplayService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"


namespace eos {

	class Application;
	class IDisplayDriver;
	class Graphics;
}


namespace app {

	class DisplayService: public eos::AppLoopService {
	    private:
			eos::IDisplayDriver *_driver;
	        eos::Graphics *_graphics;
	        int _screenWidth;
	        int _screenHeight;
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
	        int _bitmapTicks;

	    public:
	        DisplayService(eos::Application *application);

	    protected:
	        void onSetup();
	        void onLoop();

	    private:
	        void drawBackground(const char *title);
	        void testColors();
	        void testOpacity();
	        void testPoints();
	        void testLines();
	        void testRectangles();
	        void testEllipses();
	        void testBitmaps();
	};

}


#endif // __appDisplayService__
