#ifndef __eosArray__
#define __eosArray__


#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include <string.h>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif

            /// \brief Implementa array de tamany fix.
            /// \remarks La llista enmagatzema copies del element.
            ///
            template <typename Element, int size>
            class Array {

                public:
                    typedef Element Value;
                    typedef Element& Reference;
                    typedef const Element& CReference;
                    typedef Element* Pointer;
                    typedef const Element* CPointer;
                    typedef Element* Iterator;
                    typedef const Element* CIterator;

                private:
                    Value elements[size];

                public:
                    /// \brief Constructor per defecte.
                    ///
                    Array() {
                    }

                    /// \brief Constructor copia.
                    ///
                    Array(const Array& other) {
                        memmove(elements, other.elements, size * sizeof(Value));
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
                    Array(const Value array[], int arraySize = size) {
                        memmove(elements, array, Math::min(size, arraySize) * sizeof(Value));
                    }

                    /// \brief Destructor
                    ///
                    ~Array() {
                    }

                    /// \brief Obte el iterator al principi
                    ///
                    inline Iterator begin() {
                        return elements;
                    }

                    /// \brief Obte el iterator al principi
                    ///
                    inline CIterator begin() const {
                        return elements;
                    }

                    /// \brief Obte el iterator al final
                    ///
                    inline Iterator end() {
                        return &elements[size];
                    }

                    /// \brief Obte el iterator al final
                    ///
                    inline CIterator end() const {
                        return &elements[size];
                    }

                    /// \brief Obte el tamany del array.
                    /// \return El tamany.
                    ///
                    inline int getSize() const {
                        return size;
                    }

                    /// \brief Operador d'assignacio.
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    ///
                    Array& operator = (const Array& array) {
                        memmove(elements, array.elements, size * sizeof(Value));
                        return *this;
                    }

                    /// \brief Obte un element del array
                    /// \param index: Index del element
                    ///
                    inline CReference operator [] (int index) const {
                        return elements[index];
                    }

                    /// \brief Obte un element del array
                    /// \param indes: Index del element
                    ///
                    inline Reference operator [] (int index) {
                        return elements[index];
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}


#endif // __eosStaticArray__
