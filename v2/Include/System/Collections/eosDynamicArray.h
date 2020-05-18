#ifndef __eosDynamicArray__
#define	__eosDynamicArray__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"

#include <string.h>


namespace eos {
    
	void* allocContainer(unsigned capacity, unsigned elementSize);
	void freeContainer(void* container);
	void* resizeContainer(void* oldContainer, unsigned oldCapacity, unsigned newCapacity, unsigned count, unsigned elementSize);

    /// \brief Implementa una llista a partir d'un array.
    /// \remarks La llista enmagatzema copies del element.
    ///
    template <typename Element, const unsigned initialCapacity = 0>
    class DynamicArray {

        public:
            /// \brief Iterator bidireccional per la llista.
            ///
            class Iterator {
                private:
                    DynamicArray<Element>& array;
                    unsigned index;

                public:
                    /// \brief Constructor.
                    /// \param array: El array a iterar.
                    /// \param reverse: True si es recorre la llista del final al principi.
                    /// \remarks No es permet modificar la llista mente s'utilitzi el iterator.
                    ///
                    Iterator(DynamicArray<Element>& array, bool reverse = false):
                        array(array),
                        index(reverse ? array.getSize() - 1 : 0) {
                    }

                    /// \brief Mou el iterator al primer element.
                    /// \return True si tot es correcte.
                    ///
                    bool first() {
                        if (array.isEmpty())
                            return false;
                        else {
                            index = 0;
                            return true;
                        }
                    }

                    /// \brief Mou el iterator a l'ultim element.
                    /// \return True si tot es correcte.
                    ///
                    bool last() {
                        if (array.isEmpty())
                            return false;
                        else {
                            index = array.getSize() - 1;
                            return true;
                        }
                    }

                    /// \brief Mou el iterator al anterior element.
                    /// \return True si tot es correcte.
                    ///
                    bool prev() {
                        if (!array.isEmpty() && (index > 0)) {
                            index -=1;
                            return true;
                        }
                        else
                            return false;
                    }

                    /// \brief Mou el iterator al seguent element.
                    /// \return True si tot es correcte.
                    ///
                    bool next() {
                        if (!array.isEmpty() && (index < array.getSize())) {
                            index += 1;
                            return true;
                        }
                        else
                            return false;
                    }

                    /// \brief Indica si hi ha un element previ.
                    /// \return True si existeix l'element previ.
                    ///
                    inline bool hasPrev() const {
                        return !array.isEmpty() && (index >= 0);
                    }

                    /// \brief Indica si hi ha un element posterior.
                    /// \return True si existeix l'element posterior.
                    ///
                    inline bool hasNext() const {
                        return !array.isEmpty() && (index < array.getSize());
                    }

                    /// \brief Obter l'element actual.
                    /// \return L'element actual.
                    ///
                    inline Element& getCurrent() {
                        return array.getAt(index);
                    }
            };

        private:
            unsigned size;
            unsigned capacity;
            Element* elements;

        private:
            void updateCapacity() {
                if (size == capacity) {
                    unsigned newCapacity = (capacity == 0) ?
                        Math::max(unsigned(5), initialCapacity) :
                        ((capacity < 50) ?
                            capacity * 2 :
                            capacity + 25);
                    elements = static_cast<Element*>(resizeContainer(elements, capacity, newCapacity, size, sizeof(Element)));
                    capacity = newCapacity;
                }
            }

            void move(unsigned dstIndex, unsigned srcIndex, unsigned count) {
                if (count > 0)
                    memmove(&elements[dstIndex], &elements[srcIndex], count * sizeof(Element));
            }

        public:

            /// \brief Constructor.
            ///
            DynamicArray():
                size(0),
                capacity(0),
                elements(nullptr) {
            }

            /// \brief Destructor.
            ///
            ~DynamicArray() {
                if (elements != nullptr)
                    freeContainer(elements);
            }

            /// \brief Inserta un element al final
            /// \param element: L'element a inserter.
            ///
            void pushBack(const Element& element) {
                
                insertAt(size, element);
            }
            
            /// \brief Inserta un element al principi
            /// \param element: L'element a inserter.
            ///
            void pushFront(const Element& element) {
                
                insertAt(0, element);
            }

            /// \brief Extreu l'ultim element.
            ///
            void popBack() {
                
                eosAssert(size > 0);
                removeAt(size - 1);
            }
            
            /// \brief Extreu el primer element
            ///
            void popFront() {
                
                removeAt(0);
            }
            
            /// \brief Obte el primer element.
            ///
            Element& getFront() {
                
                eosAssert(size > 0);
                return elements[0];
            }
            
            /// \brief Obte l'ultim element
            ///
            Element& getBack() {
                
                return elements[size - 1];
            }

            /// \brief Obte l'element en la posicio indicada de la llista.
            /// \return L'element.
            ///
            inline Element& getAt(unsigned index) {
                eosAssert(index < size);
                return elements[index];
            }

            /// \brief Inserta un element en la posicio indicada.
            /// \param element: L'element a insertar.
            /// \param index: La posicio on insertar l'element.
            /// \return True si tot es correcte. False en cas contrari.
            ///
            bool insertAt(unsigned index, const Element& element) {
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
            void copyTo(Element* dst, unsigned offset, unsigned length) const {
                eosAssert(offset + length <= size);
                memcpy(dst, &elements[offset], length * sizeof(Element));
            }

            /// \brief Obte l'index d'un element.
            /// \return L'index o -1 si l'element no existeix.
            ///
            unsigned indexOf(const Element& element) const {
                for (unsigned index = 0; index < size; index++)
                    if (elements[index] == element)
                        return index;
                return unsigned(-1);
            }

            /// \brief Comprova si l'element pertany a la llista.
            ///
            inline bool contains(const Element& element) const {
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
            /// \return El numero d'elements.
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

            /// \brief Implementa l'operador []
            /// \return L'element en la posicio indicada.
            ///
            inline const Element& operator[](unsigned index) const {
                return getAt(index);
            }

            /// \brief Implementa l'operador []
            /// \return L'element en la posicio indicada.
            ///
            inline Element& operator[](unsigned index) {
                return getAt(index);
            }
    };
}


#endif // __eosDynamicArray__

