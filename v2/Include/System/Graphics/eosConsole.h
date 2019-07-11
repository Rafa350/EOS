#ifndef __eosConsole__
#define __eosConsole__


#include "eos.h"


namespace eos {

	class Graphics;

	class Console {
		private:
			Graphics *graphics;
			int x;
			int y;
			int width;
			int height;
			int cx;
			int cy;
			int state;

		public:
			Console(Graphics *graphics, int x, int y, int width, int height);
			void clear();
			void home();
			void moveTo(int x, int y);
			void put(char ch);
			void put(const char *s, int offset, int length);

			inline int getX() const { return x; }
			inline int getY() const { return y; }
	};
}


#endif // __eosConsole__
