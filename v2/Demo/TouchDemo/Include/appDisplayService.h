#ifndef __appTouchService__
#define __appTouchService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoop.h"


namespace eos {

	class Application;
	class Graphics;
	class Bitmap;
	class TouchPad;
	class ITouchPadDriver;
	class IDisplayDriver;
}


namespace app {

	class DisplayService: public eos::AppLoopService {
		private:
			eos::Bitmap *bitmap;
			eos::IDisplayDriver *displayDriver;
			eos::Graphics *display;
			eos::ITouchPadDriver *touchDriver;
			eos::TouchPad *touch;
			int16_t screenWidth;
			int16_t screenHeight;
			int16_t x;
			int16_t y;
			int16_t w;
			int16_t h;

		public:
			DisplayService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();

		private:
			void drawBackground();
			void drawInfo();
			void drawDot();
			void clearDot();
	};

}


#endif // __appDisplayService__
