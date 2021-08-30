#ifndef __eosPointers__
#define __eosPointers__


// EOS includes
//
#include "eos.h"
#include "System/eosRefCounter.h"


namespace eos {

	template <typename T_>
	class SharedPtr {
        private:
            T_* _ptr;
            RefCounter* _count;

        public:
            SharedPtr(T_* ptr):
            	_ptr(ptr),
				_count(new RefCounter(1)) {
            }

            SharedPtr (const SharedPtr<T_>& other):
                _ptr(other._ptr),
                _count(other._count) {
                _count->inc();
            }

            ~SharedPtr() {
                if (_count != nullptr) {
                    _count->dec();
                    if (!(*_count)) {
                        delete _ptr;
                        delete _count;
                    }
                }
            }

            SharedPtr<T_>& operator = (const SharedPtr<T_>& other) {
                if (this != &other) {
                    if (_count != nullptr) {
                        _count->dec();
                        if (!(*_count)) {
                            delete _ptr;
                            delete _count;
                        }
                    }
                    _ptr = other._ptr;
                    _count = other._count;
                    _count->inc();
                }
                return *this;
            }

            inline int uses() const {
                return (_count == nullptr) ? 0 : int(*_count);
            }

            void reset() {
                if (_count != nullptr) {
                    _count->dec();
                    if (!(*_count)) {
                        delete _ptr;
                        delete _count;
                    }
                    _count = nullptr;
                    _ptr = nullptr;
                }
            }

            inline bool operator == (const SharedPtr<T_>& other) const  {
            	return _ptr == other._ptr;
            }

            inline bool operator != (const SharedPtr<T_>& other) const  {
            	return _ptr != other._ptr;
            }

            inline T_& operator * () const {
                return *_ptr;
            }

            inline T_* operator -> () const {
                return _ptr;
            }
    };
}


#endif // __eosPointers__
