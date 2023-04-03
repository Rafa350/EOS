#ifndef __eosVector__
#define	__eosVector__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"

// Std includes
//
#include <vector>
#include <algorithm>


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif            
            template <typename Element_, unsigned initialCapacity_ = 10, bool fixedCapacity_ = false>
            class Vector {
            	private:
            		using Container = std::vector<Element_>;

            	public:
                    using Value = typename Container::value_type;
                    using Reference = typename Container::reference;
                    using CReference = typename Container::const_reference;
                    using Pointer = typename Container::pointer;
                    using CPointer = typename Container::const_pointer;
                    using Iterator = typename Container::iterator;
                    using CIterator = typename Container::const_iterator;

            	private:
            		Container _c;

            	public:

                    /// \brief Constructor per defecte
                    ///
                    Vector() {
                    	if constexpr (initialCapacity_ > 0)
                    		_c.reserve(initialCapacity_);
                    }

                    /// \brief Constructor copia
                    ///
                    Vector(const Vector &other) = delete;

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
                    	eosAssert(_c.size > 0);
                  		_c.pop_back();
                    }

                    /// \brief Extreu un element del principi.
                    ///
                    inline void popFront() {
                    	eosAssert(_c.size > 0);
                    	_c.remove(_c.begin());
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline Reference peekFront() {
            			eosAssert(_c.size() > 0);
                        return _c.front();
                    }

                    /// \brief Obte el element del principi.
                    ///
                    inline CReference peekFront() const {
            			eosAssert(_c.size() > 0);
                        return _c.front();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    //
                    inline Reference peekBack() {
            			eosAssert(_c.size() > 0);
                        return _c.back();
                    }

                    /// \brief Obte l'element del final.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference peekBack() const {
            			eosAssert(_c.size() > 0);
                        return _c.back();
                    }

                    /// \brief Obte l'element en la posicio indicada.
                    /// \param index: Posicio de l'element.
                    /// \return Una referenciua a l'element.
                    ///
                    inline Reference getAt(unsigned index) {
            			eosAssert(index < _c.size());
                        return _c.at(index);
                    }

                    /// \brief Obte l'element en la posicio indicada
                    /// \param index: Posicio de l'element.
                    /// \return Una referencia a l'element.
                    ///
                    inline CReference getAt(unsigned index) const {
            			eosAssert(index < _c.size());
                        return _c.at(index);
                    }

                    /// \brief Inserta un element en el index indicat.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool insertAt(unsigned index, CReference element) {
                    	_c.insert(_c.begin() + index, element);
                    	return true;
                    }

                    /// \brief Inserta un element en la posicio indicada.
                    /// \param element: L'element a insertar.
                    /// \param index: La posicio on insertar l'element.
                    /// \return La posicio del primer element insertat.
                    ///
                    Iterator insert(CIterator position, CReference element) {
                    	return _c.insert(position, element);
                    }

                    /// \brief Elimina un element del index expecificat.
                    /// \param index: Index del element a eliminar.
                    /// \return True si tot es correcte. False en cas contrari.
                    ///
                    bool removeAt(unsigned index) {
                    	_c.erase(_c.begin() + index);
                    	return true;
                    }

                    /// \brief Elimina un element de al posicio especificada.
                    /// \param position: La posicio.
                    /// \return La posicio del element que segueix al element borrat.
                    ///
                    Iterator remove(CIterator position) {
                    	return _c.erase(position);
                    }

                    /// \brief Elimina un grup element de al posicio especificada.
                    /// \param begin: La posicio del primer element
                    /// \param end: La posicio de l'ultim element
                    /// \return La posicio despre del element que segeix a l'ultim element borrat
                    ///
                    Iterator remove(CIterator begin, CIterator end) {
                    	return _c.erase(begin, end);
                    }

                    /// \brief Copia el contingut en un array.
                    /// \param dst: El array de destinacio.
                    /// \param offset: Index del primer element a copiar.
                    /// \param length: Numero d'elements a copiar.
                    ///
                    void copyTo(Pointer dst, unsigned offset, unsigned length) const {
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

                    /// \brief Buida el array.
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

                    /// \brief Comprova si es ple.
                    /// \return True si es buit.
                    ///
                    inline bool isFull() const {
                    	if constexpr (fixedCapacity_)
                    		return _c.size() == _c.capacity();
                    	else
                    		return false;
                    }

                    /// \brief Obte el tamany
                    /// \return El tamamy.
                    ///
                    inline unsigned getSize() const {
                    	return _c.size();
                    }

                    /// \brief Obte la capacitat actual.
                    /// \return La capacitat.
                    ///
                    inline unsigned getCapacity() const {
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
                    inline CReference operator [] (unsigned index) const {
                        return _c[index];
                    }

                    /// \brief Implementa l'operador []
                    /// \param index: La posicio.
                    /// \return L'element en la posicio indicada.
                    ///
                    inline Reference operator [] (unsigned index) {
                        return _c[index];
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosVector__

