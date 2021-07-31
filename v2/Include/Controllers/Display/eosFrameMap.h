#ifndef __eosFrameMap__
#define __eosFrameMap__


#include "eos.h"


namespace eos {

	class FrameMap {
		private:
			const int _columns;
			const int _rows;
			const int _blockWidth;
			const int _blockHeight;
			const int _mapSize;
			uint8_t* _map;

		private:
			inline int getColumn(int x) const { return x / _blockWidth; }
			inline int getRow(int y) const { return y / _blockHeight; }

		public:
			FrameMap(int width, int height, int blockWidth, int blockHeight);

			void invalidate(int x, int y, int width, int height);
			void clear();
			bool isDirty(int x, int y) const;
	};
}


#endif // __eosFrameMap__
