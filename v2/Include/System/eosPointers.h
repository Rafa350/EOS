#ifndef __eosPointers__
#define __eosPointers__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include <memory>


namespace eos {

	template <class T>
	class SharedPtr {
        private:
            T* ptr;
            int *count;

            inline void dec_count() {
                (*count)--;
            }

            inline void inc_count() {
                (*count)++;
            }

        public:
            SharedPtr(T* _ptr) {
                ptr = _ptr;
                count = new int(1);
            }

            SharedPtr (const SharedPtr<T>& other) {
                ptr = other.ptr;
                count = other.count;
                inc_count();
            }

            ~SharedPtr() {
                if (count != nullptr) {
                    dec_count();
                    if (*count == 0) {
                        delete ptr;
                        delete count;
                    }
                }
            }

            SharedPtr<T>& operator = (const SharedPtr<T>& other) {
                if (this != &other) {
                    if (count != nullptr) {
                        dec_count();
                        if (*count == 0)
                            delete ptr;
                    }
                    ptr = other.ptr;
                    count = other.count;
                    inc_count();
                }
                return *this;
            }

            int use_count() const {
                if (count != nullptr)
                    return *count;
                else
                    return 0;
            }

            void reset() {
                if (count != nullptr) {
                    dec_count();
                    if(*count == 0) {
                        delete ptr;
                        delete count;
                    }
                    count = nullptr;
                    ptr = nullptr;
                }
            }

            inline T* operator*() {
                return ptr;
            }

            inline T* operator ->() {
                return ptr;
            }
    };
}


#endif // __eosPointers__
