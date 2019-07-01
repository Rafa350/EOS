#ifndef __eosConsole__
#define __eosConsole__


#include "eos.h"


namespace eos {

	class Graphics;

	class Console {
		private:
			Graphics *graphics;
			int width;
			int height;
			int row;
			int col;
	};
}


#endif // __eosConsole__
