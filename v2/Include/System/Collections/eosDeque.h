#pragma once


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif

            template <typename T_>
            class Deque {
                public:
                    using ValueType = T_*;
                    using Pointer = ValueType*;
                    using Reference = ValueType&;

                private:
                    Pointer _begin;
                    Pointer _end;
                    Pointer _front;
                    Pointer _back;
                    unsigned _size;

                public:
                    Deque(Pointer container, unsigned capacity):
                        _begin {container},
                        _end {container + capacity},
                        _front {container},
                        _back {container},
                        _size {0} {
                    }

                    void pushFront(ValueType element) {

                        if (_size < capacity()) {
                            _size++;
                            *_front++ = element;
                           if (_front == _end)
                               _front = _begin;
                        }
                    }

                    void pushBack(ValueType element) {

                        if (_size < capacity()) {
                            _size++;
                            *--_back = element;
                           if (_back == _begin)
                               _back = _end;
                        }
                    }

                    inline unsigned size() const {
                        return _size;
                    }

                    inline unsigned capacity() const {
                        return _end - begin;
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}
