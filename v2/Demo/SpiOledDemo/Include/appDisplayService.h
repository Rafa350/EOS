#pragma once
#ifndef __appDisplayService__
#define __appDisplayService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"


namespace eos {

	class Application;
	class DisplayDriver;
	class Graphics;
}

namespace app {

	class DisplayService: public eos::Service {
		private:
			static constexpr uint16_t _displayWidth = DISPLAY_WIDTH;
			static constexpr uint16_t _displayHeight = DISPLAY_HEIGHT;

		protected:
			void onExecute() override;

		public:
			DisplayService();
	};
}


#endif // __appDisplayService__
