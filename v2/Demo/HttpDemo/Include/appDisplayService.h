#pragma once
#ifndef __appDisplayService__
#define __appDisplayService__


/// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"


namespace eos {

	class Application;
	class IDisplayDriver;
	class Graphics;
}


namespace app {

	class DisplayService: public eos::Service {
        public:
            static constexpr uint32_t stackSize = 200;
            static constexpr const char *serviceName = "DISPLAY";

		private:
			eos::IDisplayDriver *_driver;
			eos::Graphics *_graphics;

		public:
			DisplayService();

		protected:
			void onExecute() override;
	};

}

#endif // __appDisplayService__
