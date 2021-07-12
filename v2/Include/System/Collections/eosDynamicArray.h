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

            template <typename Element, int initialCapacity = 10>
            class DynamicArray {
            	private:
            		typedef std::vector<Element, StdHeapAllocator<Element> > V;

            	public:
                    typedef Element Value;
                    typedef Element& Reference;
                    typedef const Element& CReference;
                    typedef Element* Pointer;
                    typedef const Element* CPointer;
                    typedef typename V::iterator Iterator;
                    typedef typename V::const_iterator CIterator;

            	private:
            		V _v;

            	public:

                    /// \brief Constructor per defecte
                    ///
                    DynamicArray() {
                    	if constexpr (initialCapacity > 0)
                    		_v.reserve(initialCapacity);
                    }

                    /// \brief Constructor copia
                    ///
                    DynamicArray(const DynamicArray& other) = delete;

                    /// \brief Inserta un element al final
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushBack(CReference element) {
                        _v.push_back(element);
                    }

                    /// \brief Inserta un element al principi.
                    /// \param element: L'element a inserter.
                    ///
                    inline void pushFront(CReference element) {
                        _v.push_front(element);
                    }

                    /// \brief Extreu un element del final.
                    ///
                    inline void popBack() {
                    	_v.pop_back();
                    }

                    /// \brief Extreu un element del principi.
                    ///
                    inline void popFront() {
                    	_v.remove(_v.begin());
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference getFront() {
                        return _v.front();
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference getFront() const {
                        return _v.front();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference getBack() {
                        return _v.back();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getBack() const {
                        return _v.back();
                    }

                    /// \brief Obte l'element en la posicio indicada.
                    /// \param index: Posicio de l'element.
                    /// \return Una referenciua a l'element.
                    ///
                    inline Reference getAt(int index) {
                        return _v.at(index);
                    }

                    /// \brief Obte l'element en la posicio indicada
                    /// \param index: Posicio de l'element.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getAt(int index) const {
                        return _v.at(index);
                    }

                    /// \brief Inserta un element en la posicio indicada.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool insertAt(int index, CReference element) {
                    	_v.insert(_v.begin() + index, element);
                    	return true;
                    }

                    /// \brief Elimina un element de la posicio indicada.
                    /// \param index: Posicio del element a eliminar.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool removeAt(int index) {
                    	_v.erase(_v.begin() + index);
                    	return true;
                    }

                    /// \brief Copia el contingut en un array.
                    /// \param dst: El array de destinacio.
                    /// \param offset: Index del primer element a copiar.
                    /// \param length: Numero d'elements a copiar.
                    ///
                    void copyTo(Pointer dst, int offset, int length) const {
                    	std::copy(_v.begin() + offset, _v.begin() + offset + length, dst);
                    }

                    /// \brief Obte l'index d'un element.
                    /// \param element: L'element.
                    /// \return L'index o -1 si l'element no existeix.
                    ///
                    int indexOf(CReference element) const {
                    	typename V::const_iterator it = std::find(_v.begin(), _v.end(), element);
                    	if (it == end())
                    		return -1;
                    	else
                    		return it - _v.begin();
                    }

                    /// \brief Comprova si l'element pertany a la llista.
                    /// \param element: L'element.
                    /// \return Trus si pertany, false en cas contrari.
                    ///
                    inline bool contains(CReference element) const {
                    	return std::find(_v.begin(), _v.end(), element) != _v.end();
                    }

                    /// \brief Buida el array i borra el contenidor.
                    ///
                    inline void clear() {
                    	_v.clear();
                    }

                    /// \brief Comprova si es buit.
                    /// \return True si es buit.
                    ///
                    inline bool isEmpty() const {
                    	return _v.empty();
                    }

                    /// \brief Obte el tamany
                    /// \return El tamamy.
                    ///
                    inline int getSize() const {
                    	return _v.size();
                    }

                    /// \brief Obte la capacitat actual.
                    /// \return La capacitat.
                    ///
                    inline int getCapacity() const {
                    	return _v.capacity();
                    }

                    /// \brief Obte el iterator inicial
                    ///
                    inline Iterator begin() {
                        return _v.begin();
                    }

                    /// \brief Obte el iterator inicial
                    ///
                    inline CIterator begin() const {
                        return _v.cbegin();
                    }

                    /// \brief Obte el iterator final
                    ///
                    inline Iterator end() {
                        return _v.end();
                    }

                    /// \brief Obte el iterator final
                    ///
                    inline CIterator end() const {
                        return _v.cend();
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline CReference operator[](int index) const {
                        return _v[index];
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline Reference operator[](int index) {
                        return _v[index];
                    }
            };

#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosDynamicArray__

