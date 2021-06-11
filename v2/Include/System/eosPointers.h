#ifndef __eosPointers__
#define __eosPointers__


// EOS includes
//
#include "eos.h"
#include "System/eosRefCounter.h"

// Standard includes
//
#include <memory>


namespace eos {

#if 0
	#define SharedPtr std::shared_ptr
#else
	template <class T>
	class SharedPtr {
        private:
            T* _ptr;
            RefCounter* _count;

        public:
            SharedPtr(T* ptr) {
                _ptr = ptr;
                _count = new RefCounter(1);
            }

            SharedPtr (const SharedPtr<T>& other) {
                _ptr = other._ptr;
                _count = other._count;
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

            SharedPtr<T>& operator = (const SharedPtr<T>& other) {
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

            int uses() const {
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

            inline T& operator*() const {
                return *_ptr;
            }

            inline T* operator ->() const {
                return _ptr;
            }
    };

#endif

}


#endif // __eosPointers__
