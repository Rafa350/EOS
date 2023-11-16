#pragma once


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif

            template <typename T_>
            class ArrayBase {
                public:
                    using ValueType = T_;
                    using Pointer = ValueType*;
                    using CPointer = const ValueType*;
                    using Reference = ValueType&;
                    using CReference = const ValueType&;
                    using Iterator = ValueType*;
                    using CIterator = const ValueType*;
                    
                private:
                    Pointer _container;
                    unsigned _capacity;
                    
                public:
                    ArrayBase(Pointer container, unsigned capacity):
                        _container {container},
                        _capacity {capacity} {
                        
                    }
                    
                    ValueType front() const {
                        return _container[0];
                    }
                    
                    inline Iterator begin() {
                        return _container;
                    }
                    
                    inline CIterator begin() const {
                        return _container;
                    }
                    
                    inline Iterator end() {
                        return _container + _capacity;
                    }
                    
                    inline CIterator end() const {
                        return _container + _capacity;
                    }
                    
                    constexpr bool empty() const {
                        return false;
                    }
                    
                    constexpr bool full() const {
                        return true;
                    }
                    
                    inline bool size() const {
                        return _capacity;
                    }
                    
                    inline bool capacity() const {
                        return _capacity;
                    }
                    
                    operator [] (unsigned index) {
                        return _container[index];
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}