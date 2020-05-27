#ifndef __eosStaticArray__
#define __eosStaticArray__


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
            template <typename Element, const unsigned size>
            class StaticArray {
                
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
                    StaticArray() {
                    }
  
                    /// \brief Constructor copia.                    
                    ///
                    StaticArray(const StaticArray& other) {
                        memmove(elements, other.elements, size * sizeof(Value));
                    }
                    
                    /// \brief Contructor a partir d'un rang.
                    /// \param first: Primer element del rang.
                    /// \param last: L'ultim element del rang.
                    ///
                    StaticArray(Iterator first, Iterator last) {
                        for(auto it = first; it != last; it++)
                            pushBack(*it);
                    }
                    
                    /// \brief Constructor a partir d'un array 'C'.
                    ///
                    StaticArray(const Value array[], unsigned arraySize) {                        
                        memmove(elements, array, Math::min(size, arraySize) * sizeof(Value));
                    }
                    
                    /// \brief Destructor
                    ///
                    ~StaticArray() {                        
                    }
                    
                    /// \brief Obte el iterator al principi
                    ///
                    inline Iterator begin() const {
                        return elements;
                    }
                    
                    /// \brief Obte el iterator al final
                    ///
                    inline Iterator end() const {
                        return elements + size;
                    }
                    
                    /// \brief Obte el tamany del array.
                    /// \return El tamany.
                    ///
                    inline unsigned getSize() const {
                        return size;
                    }
                                       
                    /// \brief Operador d'assignacio.
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    ///
                    StaticArray& operator=(const StaticArray& array) {                        
                        memmove(elements, array.elements, size * sizeof(Value));
                        return *this;
                    }

                    /// \brief Obte un element del array
                    /// \param index: Index del element
                    ///
                    inline CReference operator[](int index) const {
                        return elements[index];
                    }

                    /// \brief Obte un element del array
                    /// \param indes: Index del element
                    ///
                    inline Reference operator[](int index) {
                        return elements[index];
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosStaticArray__