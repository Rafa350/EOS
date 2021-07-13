#ifndef __eosDynamicArray__
#define	__eosDynamicArray__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Core/eosStdHeapAllocator.h"

// Std includes
//
#include <vector>
#include <algorithm>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            

            template <typename Element, int initialCapacity = 10, bool fixedCapacity = false>
            class DynamicArray {
            	private:
            		using Allocator = StdHeapAllocator<Element>;
            		using Container = std::vector<Element, Allocator>;

            	public:
                    typedef typename Container::value_type Value;
                    typedef typename Container::reference Reference;
                    typedef typename Container::const_reference CReference;
                    typedef typename Container::pointer Pointer;
                    typedef typename Container::const_pointer CPointer;
                    typedef typename Container::iterator Iterator;
                    typedef typename Container::const_iterator CIterator;

            	private:
            		Container _c;

            	public:

                    /// \brief Constructor per defecte
                    ///
                    DynamicArray() {
                    	if constexpr (initialCapacity > 0)
                    		_c.reserve(initialCapacity);
                    }

                    /// \brief Constructor copia
                    ///
                    DynamicArray(const DynamicArray& other) = delete;

                    /// \brief Inserta un element al final
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushBack(CReference element) {
                        _c.push_back(element);
                    }

                    /// \brief Inserta un element al principi.
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushFront(CReference element) {
                        _c.push_front(element);
                    }

                    /// \brief Extreu un element del final.
                    ///
                    inline void popBack() {
                    	_c.pop_back();
                    }

                    /// \brief Extreu un element del principi.
                    ///
                    inline void popFront() {
                    	_c.remove(_c.begin());
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference getFront() {
                        return _c.front();
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference getFront() const {
                        return _c.front();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference getBack() {
                        return _c.back();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getBack() const {
                        return _c.back();
                    }

                    /// \brief Obte l'element en la posicio indicada.
                    /// \param index: Posicio de l'element.
                    /// \return Una referenciua a l'element.
                    ///
                    inline Reference getAt(int index) {
                        return _c.at(index);
                    }

                    /// \brief Obte l'element en la posicio indicada
                    /// \param index: Posicio de l'element.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getAt(int index) const {
                        return _c.at(index);
                    }

                    /// \brief Inserta un element en la posicio indicada.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool insertAt(int index, CReference element) {
                    	_c.insert(_c.begin() + index, element);
                    	return true;
                    }

                    /// \brief Elimina un element de la posicio indicada.
                    /// \param index: Posicio del element a eliminar.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool removeAt(int index) {
                    	_c.erase(_c.begin() + index);
                    	return true;
                    }

                    /// \brief Copia el contingut en un array.
                    /// \param dst: El array de destinacio.
                    /// \param offset: Index del primer element a copiar.
                    /// \param length: Numero d'elements a copiar.
                    ///
                    void copyTo(Pointer dst, int offset, int length) const {
                    	std::copy(_c.begin() + offset, _c.begin() + offset + length, dst);
                    }

                    /// \brief Obte l'index d'un element.
                    /// \param element: L'element.
                    /// \return L'index o -1 si l'element no existeix.
                    ///
                    int indexOf(CReference element) const {
                    	CIterator it = std::find(_c.begin(), _c.end(), element);
                    	if (it == end())
                    		return -1;
                    	else
                    		return it - _c.begin();
                    }

                    /// \brief Comprova si l'element pertany a la llista.
                    /// \param element: L'element.
                    /// \return Trus si pertany, false en cas contrari.
                    ///
                    inline bool contains(CReference element) const {
                    	return std::find(_c.begin(), _c.end(), element) != _c.end();
                    }

                    /// \brief Buida el array i borra el contenidor.
                    ///
                    inline void clear() {
                    	_c.clear();
                    }

                    /// \brief Comprova si es buit.
                    /// \return True si es buit.
                    ///
                    inline bool isEmpty() const {
                    	return _c.empty();
                    }

                    /// \brief Obte el tamany
                    /// \return El tamamy.
                    ///
                    inline int getSize() const {
                    	return _c.size();
                    }

                    /// \brief Obte la capacitat actual.
                    /// \return La capacitat.
                    ///
                    inline int getCapacity() const {
                    	return _c.capacity();
                    }

                    /// \brief Obte el iterator inicial
                    ///
                    inline Iterator begin() {
                        return _c.begin();
                    }

                    /// \brief Obte el iterator inicial
                    ///
                    inline CIterator begin() const {
                        return _c.cbegin();
                    }

                    /// \brief Obte el iterator final
                    ///
                    inline Iterator end() {
                        return _c.end();
                    }

                    /// \brief Obte el iterator final
                    ///
                    inline CIterator end() const {
                        return _c.cend();
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline CReference operator[](int index) const {
                        return _c[index];
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline Reference operator[](int index) {
                        return _c[index];
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosDynamicArray__

