#pragma once
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
			static constexpr uint16_t _displayWidth = DISPLAY_WIDTH;
			static constexpr uint16_t _displayHeight = DISPLAY_HEIGHT;
			static constexpr uint32_t _displayBuffer = DISPLAY_BUFFER;

			eos::IDisplayDriver *_driver;
			eos::Graphics *_graphics;

		protected:
			void onSetup();
			void onLoop();

		public:
			DisplayService();
	};
}


#endif // __appDisplayService__
