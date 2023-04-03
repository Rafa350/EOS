#ifndef __eosArray__
#define __eosArray__


#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include <string.h>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif

            /// \brief Implementa array de tamany fix.
            /// \remarks La llista enmagatzema copies del element.
            ///
            template <typename Element_, int size_>
            class Array {

                public:
                    typedef Element_ Value;
                    typedef Element_ &Reference;
                    typedef const Element_ &CReference;
                    typedef Element_ *Pointer;
                    typedef const Element_ *CPointer;
                    typedef Element_ *Iterator;
                    typedef const Element_ *CIterator;

                private:
                    Value _elements[size_];

                public:
                    /// \brief Constructor per defecte.
                    ///
                    Array() {
                    }

                    /// \brief Constructor copia.
                    ///
                    Array(const Array &other) {
                        memmove(_elements, other._elements, size_ * sizeof(Value));
                    }

                    /// \brief Contructor a partir d'un rang.
                    /// \param first: Primer element del rang.
                    /// \param last: L'ultim element del rang.
                    ///
                    Array(Iterator first, Iterator last) {
                        for(auto it = first; it != last; it++)
                            pushBack(*it);
                    }

                    /// \brief Constructor a partir d'un array 'C'.
                    ///
                    Array(const Value array[], int arraySize = size_) {
                        memmove(_elements, array, Math::min(size, arraySize) * sizeof(Value));
                    }

                    /// \brief Destructor
                    ///
                    ~Array() {
                    }

                    /// \brief Obte el iterator al principi
                    ///
                    inline Iterator begin() {
                        return _elements;
                    }

                    /// \brief Obte el iterator al principi
                    ///
                    inline CIterator begin() const {
                        return _elements;
                    }

                    /// \brief Obte el iterator al final
                    ///
                    inline Iterator end() {
                        return &_elements[size_];
                    }

                    /// \brief Obte el iterator al final
                    ///
                    inline CIterator end() const {
                        return &_elements[size_];
                    }

                    /// \brief Obte el tamany del array.
                    /// \return El tamany.
                    ///
                    inline int getSize() const {
                        return size_;
                    }

                    /// \brief Operador d'assignacio.
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    ///
                    Array& operator = (const Array &array) {
                        memmove(_elements, array._elements, size_ * sizeof(Value));
                        return *this;
                    }

                    /// \brief Obte un element del array
                    /// \param index: Index del element
                    ///
                    inline CReference operator [] (int index) const {
                        return _elements[index];
                    }

                    /// \brief Obte un element del array
                    /// \param indes: Index del element
                    ///
                    inline Reference operator [] (int index) {
                        return _elements[index];
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosStaticArray__
