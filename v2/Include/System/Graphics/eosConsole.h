#ifndef __eosConsole__
#define __eosConsole__


#include "eos.h"


namespace eos {

	class Graphics;

	class Console {
		private:
			Graphics *graphics;
			int rows;
			int cols;
			int row;
			int col;

		public:
			Console(Graphics *graphics, int cols, int rows);
	};
}


#endif // __eosConsole__
