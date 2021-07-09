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
            template <typename Element, const int initialCapacity = 0>
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
                    int _size;
                    int _capacity;
                    Value *_elements;

                private:
                    void updateCapacity() {
                        if (_size == _capacity) {
                            int newCapacity = (_capacity == 0) ?
                                Math::max(5, initialCapacity) :
                                ((_capacity < 50) ?
                                    _capacity * 2 :
                                    _capacity + 25);
                            _elements = static_cast<Pointer>(Container::resize(_elements, _capacity, newCapacity, _size, sizeof(Value)));
                            _capacity = newCapacity;
                        }
                    }

                    void move(int dstIndex, int srcIndex, int count) {
                        if (count > 0)
                            memmove(&_elements[dstIndex], &_elements[srcIndex], count * (int)sizeof(Value));
                    }

                public:

                    /// \brief Constructor per defecte
                    ///
                    DynamicArray():
                        _size(0),
                        _capacity(0),
                        _elements(nullptr) {
                    }
                        
                    /// \brief Constructor copia
                    ///
                    DynamicArray(const DynamicArray& other):
                        _size(other._size),
                        _capacity(other._capacity),
                        _elements(Container::alloc(_capacity, (int)sizeof(Value))) {
                        memmove(_elements, other._elements, _size * (int)sizeof(Value));
                    }

                    /// \brief Destructor.
                    ///
                    ~DynamicArray() {
                        if (_elements != nullptr)
                            Container::free(_elements);
                    }

                    /// \brief Inserta un element al final
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushBack(CReference element) {
                        insertAt(_size, element);
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
                        eosAssert(_size > 0);
                        removeAt(_size - 1);
                    }

                    /// \brief Extreu un elkement del principi.
                    ///
                    inline void popFront() {
                        eosAssert(_size > 0);
                        removeAt(0);
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference getFront() {
                        eosAssert(_size > 0);
                        return _elements[0];
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference getFront() const {
                        eosAssert(_size > 0);
                        return _elements[0];
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference getBack() {
                        eosAssert(_size > 0);
                        return _elements[_size - 1];
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getBack() const {
                        eosAssert(_size > 0);
                        return _elements[_size - 1];
                    }

                    /// \brief Obte l'element en la posicio indicada.
                    /// \param index: Posicio de l'element.
                    /// \return Una referenciua a l'element.
                    ///
                    inline Reference getAt(int index) {
                        eosAssert(index < _size);
                        return _elements[index];
                    }

                    /// \brief Obte l'element en la posicio indicada
                    /// \param index: Posicio de l'element.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getAt(int index) const {
                        eosAssert(index < _size);
                        return _elements[index];
                    }

                    /// \brief Inserta un element en la posicio indicada.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool insertAt(int index, CReference element) {
                        if (index == _size) {
                            updateCapacity();
                            _elements[index] = element;
                            _size += 1;
                            return true;
                        }
                        else if (index < _size) {
                            updateCapacity();
                            move(index + 1, index, _size - index);
                            _elements[index] = element;
                            _size += 1;
                            return true;
                        }
                        else
                            return false;
                    }

                    /// \brief Elimina un element de la posicio indicada.
                    /// \param index: Posicio del element a eliminar.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool removeAt(int index) {
                        if (index >= _size)
                            return false;
                        else if (index < _size) {
                            move(index, index + 1, _size - index - 1);
                            _size -= 1;
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
                    void copyTo(Pointer dst, int offset, int length) const {
                        eosAssert(offset + length <= _size);
                        memcpy(dst, &_elements[offset], length * (int)sizeof(Element));
                    }

                    /// \brief Obte l'index d'un element.
                    /// \param element: L'element.
                    /// \return L'index o -1 si l'element no existeix.
                    ///
                    int indexOf(CReference element) const {
                        for (int index = 0; index < _size; index++)
                            if (_elements[index] == element)
                                return index;
                        return -1;
                    }

                    /// \brief Comprova si l'element pertany a la llista.
                    /// \param element: L'element.
                    /// \return Trus si pertany, false en cas contrari.
                    ///
                    inline bool contains(CReference element) const {
                        return indexOf(element) != -1;
                    }

                    /// \brief Buida el array, pero deixa el contenidor.
                    ///
                    inline void empty() {
                        _size = 0;
                    }

                    /// \brief Buida el array i borra el contenidor.
                    ///
                    void clear() {
                        Container::free(_elements);
                        _size = 0;
                        _capacity = 0;
                        _elements = nullptr;
                    }

                    /// \brief Comprova si es buit.
                    /// \return True si es buit.
                    ///
                    inline bool isEmpty() const {
                        return _size == 0;
                    }

                    /// \brief Obte el tamany
                    /// \return El tamamy.
                    ///
                    inline int getSize() const {
                        return _size;
                    }

                    /// \brief Obte la capacitat actual.
                    /// \return La capacitat.
                    ///
                    inline int getCapacity() const {
                        return _capacity;
                    }
                    
                    /// \brief Obte el iterator.
                    ///
                    inline Iterator begin() const {
                        return _elements;
                    }
                    
                    /// \brief Obte el iterator
                    ///
                    inline Iterator end() const {
                        return _elements + _size;
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline CReference operator[](int index) const {
                        return getAt(index);
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline Reference operator[](int index) {
                        return getAt(index);
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosDynamicArray__

