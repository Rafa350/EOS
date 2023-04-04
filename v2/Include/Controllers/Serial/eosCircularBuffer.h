#pragma once
#ifndef __eosCircularBuffer__
#define __eosCircularBuffer__


#include "eos.h"


namespace eos {
	class CircularBuffer final {
		private:
			uint8_t *_buffer;
			uint16_t _bufferSize;
			uint16_t _pushIdx;
			uint16_t _popIdx;
			uint16_t _count;

		public:
			CircularBuffer(uint8_t *buffer, uint16_t bufferSize);

			void push(uint8_t data);
			void push(uint8_t *data, uint16_t dataLength);
			uint8_t pop();
			void clear();

			inline bool isEmpty() const {
				return _count == 0;
			}

			inline bool isFull() const {
				return _count == _bufferSize;
			}

			inline unsigned getSize() const {
				return _count;
			}

			inline unsigned getCapacity() const {
				return _bufferSize;
			}
	};

}


#endif // __eosCircularBuffer__
