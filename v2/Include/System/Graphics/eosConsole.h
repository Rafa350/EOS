#ifndef __eosConsole__
#define __eosConsole__


#include "eos.h"


namespace eos {

	class Graphics;

	class Console {
		private:
			Graphics* _graphics;
			int _x;
			int _y;
			int _width;
			int _height;
			Color _bkColor;
			Color _fgColor;
			int _cx;
			int _cy;
			int _state;

		public:
			Console(Graphics* graphics, int x, int y, int width, int height);
			void clear();
			void home();
			void moveTo(int x, int y);
			void put(char ch);
			void put(const char *s, int offset, int length);

			inline int getX() const { return _x; }
			inline int getY() const { return _y; }
	};
}


#endif // __eosConsole__
