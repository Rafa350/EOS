#pragma once
#ifndef __appDROPanel__
#define __appDROPanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace app {

	class DROPanel: public eos::Panel {
		private:
			void initialize();

		public:
			DROPanel();
	};
}


#endif // __appDROPanel__

