#pragma once


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace eos {

    class LedService;
}


namespace app {

	class DisplayService;

	class MyApplication: public eos::RTOSApplication {
		private:
			eos::LedService *_ledService;
			DisplayService *_displayService;

		protected:
			void onInitialize() override;

		public :
			MyApplication();
	};

}
