#pragma once
#ifndef __eosCircularBuffer__
#define __eosCircularBuffer__


// EOS includes
//
#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif

			template <typename T_>
			class CircularBuffer {
				public:
					using Pointer = T_*;
					using CPointer = T_ const *;
					using Reference = T_&;
					using CReference = T_ const &;

				private:
					Pointer _buffer;
					Pointer _getPtr;
					Pointer _putPtr;
					unsigned _size;
					unsigned _count;

				public:
					CircularBuffer(Pointer buffer, unsigned size):
						_buffer {buffer},
						_getPtr {buffer},
						_putPtr {buffer},
						_size {size},
						_count {0} {
					}

					inline unsigned getCount() const {
						return _count;
					}

					inline bool isFull() const {
						return _count == _size;
					}

					inline bool isEmpty() const {
						return _count == 0;
					}

					void purge() {
						_putPtr = _buffer;
						_getPtr = _buffer;
						_count = 0;
					}

					bool peek(Reference element) {
						if (_count > 0) {
							element = *_getPtr;
							return true;
						}
						else
							return false;
					}

					bool pop() {
						if (_count > 0) {
							_count--;
							_getPtr++;
							if (_getPtr == _buffer + _size)
								_getPtr = _buffer;
							return true;
						}
						else
							return false;
					}

					bool pop(Reference element) {
						if (peek(element))
							return pop();
						else
							return false;
					}

					bool push(CReference element) {
						if (_count < _size) {
							*_putPtr = element;
							_count++;
							_putPtr++;
							if (_putPtr == _buffer + _size)
								_putPtr = _buffer;
							return true;
						}
						else
							return false;
					}
			};
#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif
