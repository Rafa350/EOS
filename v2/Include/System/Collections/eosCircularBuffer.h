#pragma once
#ifndef __eosCircularBuffer__
#define __eosCircularBuffer__


// EOS includes
//
#include "eos.h"


namespace eos {

    template <typename Element>
	class CircularBuffer {
		private:
			Element *_buffer;
			Element *_getPtr;
			Element *_putPtr;
			unsigned _size;
			unsigned _count;

		public:
			CircularBuffer(Element *buffer, unsigned size):
				_buffer {buffer},
				_getPtr {buffer},
				_putPtr {buffer},
				_size {size},
				_count {0} {
			}

			inline unsigned getCount() const {return _count; }
			inline bool isFull() const { return _count == _size; }
			inline bool isEmpty() const { return _count == 0; }

			void purge() {
				_putPtr = _buffer;
				_getPtr = _buffer;
				_count = 0;
			}

			bool put(Element element) {
				if (_count < _size) {
					_count++;
					*_putPtr++ = element;
					if (_putPtr == _buffer + _size)
						_putPtr = _buffer;
					return true;
				}
				else
					return false;
			}

			bool get(Element &element) {
				if (_count > 0) {
					_count--;
					element = *_getPtr++;
					if (_getPtr == _buffer + _size)
						_getPtr = _buffer;
					return true;
				}
				else
					return false;
			}
	};
}


#endif
