#ifndef __eosFrameMap__
#define __eosFrameMap__


#include "eos.h"


namespace eos {

	class FrameMap {
		private:
			int _columns;
			int _rows;
			int _blockWidth;
			int _blockHeight;
			int _mapSize;
			uint8_t* _map;

		private:
			inline bool isInitialized() const { return _map != nullptr; }
			inline int getColumn(int x) const { return x / _blockWidth; }
			inline int getRow(int y) const { return y / _blockHeight; }

		public:
			FrameMap();
			FrameMap(int width, int height, int blockWidth, int blockHeight);
			~FrameMap();

			void initialize(int width, int height, int blockWidth, int blockHeight);

			void invalidate(int x, int y, int width, int height);
			void clear();
			bool isDirty(int x, int y) const;
	};
}


#endif // __eosFrameMap__
