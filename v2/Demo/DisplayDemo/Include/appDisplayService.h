#ifndef __appDisplayService__
#define __appDisplayService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoop.h"


namespace eos {

	class Application;
	class IDisplayDriver;
	class Graphics;
}


namespace app {

	class DisplayService: public eos::AppLoopService {
	    private:
			eos::IDisplayDriver *driver;
	        eos::Graphics *graphics;
	        int screenWidth;
	        int screenHeight;
	        int orientation;
	        int loopCount;

	    public:
	        DisplayService(eos::Application *application);

	    protected:
	        void onSetup();
	        void onLoop();

	    private:
	        void drawBackground(const char *title);
	};


}


#endif // __appDisplayService__
