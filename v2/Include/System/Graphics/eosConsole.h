#ifndef __eosConsole__
#define __eosConsole__


#include "eos.h"


namespace eos {

	class Graphics;

	class Console {
		private:
			Graphics *graphics;
			unsigned rows;
			unsigned columns;
			unsigned row;
			unsigned column;

		public:
			Console(Graphics *graphics, unsigned columnss, unsigned rows);
			void home();
			void moveTo(unsigned column, unsigned row);

			inline unsigned getColumn() const { return column; }
			inline unsigned getRow() const { return row; }
	};
}


#endif // __eosConsole__
