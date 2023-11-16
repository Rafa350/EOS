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

            /// \brief Implementa una estructura de array utilitzant un buffer extern.
            ///
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
                    Pointer _begin;
                    Pointer _end;
                    
                public:
                    /// \brief Constructor.
                    /// \param container: Buffer on enmagatzemar els elements.
                    /// \param capacity: Nombre maxim d'elements en el buffer.
                    ///
                    ArrayBase(Pointer container, unsigned capacity):
                        _begin {container},
                        _end {container + capacity} {
                        
                    }
                    
                    /// \brief Obte el primer element.
                    /// \return El primer element del array.
                    ///
                    ValueType front() const {
                        return *_begin;
                    }
                    
                    /// \brief Obte el iterator al inici del array.
                    /// \return El iterator.
                    ///
                    inline Iterator begin() {
                        return _begin;
                    }
                    
                    /// \brief Obte el iterator constant al inici del array.
                    /// \return El iterator.
                    ///
                    inline CIterator begin() const {
                        return _begin;
                    }
                    
                    /// \brief Obte el iterator al final del array.
                    /// \return El iterator.
                    ///
                    inline Iterator end() {
                        return _end;
                    }
                    
                    /// \brief Obte el iterator constant al final del array.
                    /// \return El iterator.
                    ///
                    inline CIterator end() const {
                        return _end;
                    }
                    
                    /// \brief Indica si el array es buit. Mai esta buit.
                    /// \return false
                    ///
                    constexpr bool empty() const {
                        return false;
                    }
                    
                    /// \brief Indica si el array es ple. Sempre es ple.
                    /// \return true
                    ///
                    constexpr bool full() const {
                        return true;
                    }

                    /// \brief Obte el tamany del array.
                    /// \return El tamany.
                    ///
                    inline bool size() const {
                        return _end - _begin;
                    }
                    
                    /// \brief Obte la capacitat del array.
                    /// \return La capacitat.
                    ///
                    inline bool capacity() const {
                        return _end - begin;
                    }

                    /// \bried Accedeix als elements per index.
                    /// \param index: Index del element.
                    /// \return El element
                    ///
                    Reference operator [] (unsigned index) {
                        return _begin[index];
                    }

                    /// \bried Accedeix als elements per index.
                    /// \param index: Index del element.
                    /// \return El element
                    ///
                    CReference operator [] (unsigned index) const {
                        return _begin[index];
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}