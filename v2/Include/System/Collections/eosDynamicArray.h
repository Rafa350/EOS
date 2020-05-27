#ifndef __eosDynamicArray__
#define	__eosDynamicArray__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Collections/eosContainer.h"
#include <string.h>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            

            /// \brief Implementa array de tamany variable.
            /// \remarks La llista enmagatzema copies del element.
            ///
            template <typename Element, const unsigned initialCapacity = 0>
            class DynamicArray {
                
                public:
                    typedef Element Value;
                    typedef Element& Reference;
                    typedef const Element& CReference;
                    typedef Element* Pointer;
                    typedef const Element* CPointer;
                    typedef Element* Iterator;
                    typedef const Element* CIterator;

                private:
                    unsigned size;
                    unsigned capacity;
                    Value* elements;

                private:
                    void updateCapacity() {
                        if (size == capacity) {
                            unsigned newCapacity = (capacity == 0) ?
                                Math::max(unsigned(5), initialCapacity) :
                                ((capacity < 50) ?
                                    capacity * 2 :
                                    capacity + 25);
                            elements = static_cast<Pointer>(Container::resize(elements, capacity, newCapacity, size, sizeof(Value)));
                            capacity = newCapacity;
                        }
                    }

                    void move(unsigned dstIndex, unsigned srcIndex, unsigned count) {
                        if (count > 0)
                            memmove(&elements[dstIndex], &elements[srcIndex], count * sizeof(Value));
                    }

                public:

                    /// \brief Constructor per defecte
                    ///
                    DynamicArray():
                        size(0),
                        capacity(0),
                        elements(nullptr) {
                    }
                        
                    /// \brief Constructor copia
                    ///
                    DynamicArray(const DynamicArray& other):
                        size(other.size),
                        capacity(other.capacity),
                        elements(Container::alloc(capacity, sizeof(Value))) {                       
                        memmove(elements, other.elements, size * sizeof(Value));
                    }

                    /// \brief Destructor.
                    ///
                    ~DynamicArray() {
                        if (elements != nullptr)
                            Container::free(elements);
                    }

                    /// \brief Inserta un element al final
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushBack(CReference element) {
                        insertAt(size, element);
                    }

                    /// \brief Inserta un element al principi.
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushFront(CReference element) {
                        insertAt(0, element);
                    }

                    /// \brief Extreu un element del final.
                    ///
                    inline void popBack() {
                        eosAssert(size > 0);
                        removeAt(size - 1);
                    }

                    /// \brief Extreu un elkement del principi.
                    ///
                    inline void popFront() {
                        eosAssert(size > 0);
                        removeAt(0);
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference getFront() {
                        eosAssert(size > 0);
                        return elements[0];
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference getFront() const {
                        eosAssert(size > 0);
                        return elements[0];
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference getBack() {
                        eosAssert(size > 0);
                        return elements[size - 1];
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getBack() const {
                        eosAssert(size > 0);
                        return elements[size - 1];
                    }

                    /// \brief Obte l'element en la posicio indicada.
                    /// \param index: Posicio de l'element.
                    /// \return Una referenciua a l'element.
                    ///
                    inline Reference getAt(unsigned index) {
                        eosAssert(index < size);
                        return elements[index];
                    }

                    /// \brief Obte l'element en la posicio indicada
                    /// \param index: Posicio de l'element.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getAt(unsigned index) const {
                        eosAssert(index < size);
                        return elements[index];
                    }

                    /// \brief Inserta un element en la posicio indicada.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool insertAt(unsigned index, CReference element) {
                        if (index == size) {
                            updateCapacity();
                            elements[index] = element;
                            size += 1;
                            return true;
                        }
                        else if (index < size) {
                            updateCapacity();
                            move(index + 1, index, size - index);
                            elements[index] = element;
                            size += 1;
                            return true;
                        }
                        else
                            return false;
                    }

                    /// \brief Elimina un element de la posicio indicada.
                    /// \param index: Posicio del element a eliminar.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool removeAt(unsigned index) {
                        if (index >= size)
                            return false;
                        else if (index < size) {
                            move(index, index + 1, size - index - 1);
                            size -= 1;
                            return true;
                        }
                        else
                            return true;
                    }

                    /// \brief Copia el contingut en un array.
                    /// \param dst: El array de destinacio.
                    /// \param offset: Index del primer element a copiar.
                    /// \param length: Numero d'elements a copiar.
                    ///
                    void copyTo(Pointer dst, unsigned offset, unsigned length) const {
                        eosAssert(offset + length <= size);
                        memcpy(dst, &elements[offset], length * sizeof(Element));
                    }

                    /// \brief Obte l'index d'un element.
                    /// \param element: L'element.
                    /// \return L'index o -1 si l'element no existeix.
                    ///
                    unsigned indexOf(CReference element) const {
                        for (unsigned index = 0; index < size; index++)
                            if (elements[index] == element)
                                return index;
                        return unsigned(-1);
                    }

                    /// \brief Comprova si l'element pertany a la llista.
                    /// \param element: L'element.
                    /// \return Trus si pertany, false en cas contrari.
                    ///
                    inline bool contains(CReference element) const {
                        return indexOf(element) != unsigned(-1);
                    }

                    /// \brief Buida el array, pero deixa el contenidor.
                    ///
                    inline void empty() {
                        size = 0;
                    }

                    /// \brief Buida el array i borra el contenidor.
                    ///
                    void clear() {
                        freeContainer(elements);
                        size = 0;
                        capacity = 0;
                        elements = nullptr;
                    }

                    /// \brief Comprova si es buit.
                    /// \return True si es buit.
                    ///
                    inline bool isEmpty() const {
                        return size == 0;
                    }

                    /// \brief Obte el tamany
                    /// \return El tamamy.
                    ///
                    inline unsigned getSize() const {
                        return size;
                    }

                    /// \brief Obte la capacitat actual.
                    /// \return La capacitat.
                    ///
                    inline unsigned getCapacity() const {
                        return capacity;
                    }
                    
                    /// \brief Obte el iterator.
                    ///
                    inline Iterator begin() const {
                        return elements;
                    }
                    
                    /// \brief Obte el iterator
                    ///
                    inline Iterator end() const {
                        return elements + size;
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline CReference operator[](unsigned index) const {
                        return getAt(index);
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline Reference operator[](unsigned index) {
                        return getAt(index);
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosDynamicArray__

