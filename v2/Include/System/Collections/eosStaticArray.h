#ifndef __eosStaticArray__
#define __eosStaticArray__


#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            
        
            template <typename Element, const unsigned size>
            class StaticArray {
                private:
                    Element elements[size];
                    
                public:
                    /// \brief Constructor per defecte.
                    ///
                    StaticArray() {
                    }
  
                    /// \brief Constructor copia.                    
                    ///
                    StaticArray(const StaticArray& array) {
                        for (int i = 0; i < size; i++)
                            elements[i] = array.elements[i];
                    }
                    
                    /// \brief Constructor a partir d'un array 'C'.
                    ///
                    StaticArray(const Element elements[]) {                        
                        for (int i = 0; i < size; i++)
                            this->elements[0] = elements[i];
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
                    StaticArray& operator=(const StaticArray& array) {                        
                        for (int i = 0; i < size; i++)
                            elements[i] = array.elements[i];                        
                        return *this;
                    }

                    /// \brief Operador d'assignacio a un array 'C'
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    ///
                    StaticArray& operator=(const Element elements[]) {                        
                        for (int i = 0; i < size; i++)
                            this->elements[i] = elements[i];                        
                        return *this;
                    }

                    /// \brief Obte un element del array
                    /// \param index: Index del element
                    ///
                    inline const Element& operator[](int index) const {
                        return elements[index];
                    }

                    /// \brief Obte un element del array
                    /// \param indes: Index del element
                    ///
                    inline Element& operator[](int index) {
                        return elements[index];
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosStaticArray__