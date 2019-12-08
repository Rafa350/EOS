#ifndef __eosStaticArray__
#define __eosStaticArray__


#include "eos.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            
        
            template <typename Element, const int numElements>
            class StaticArray {
                private:
                    Element elements[numElements];
                    
                public:
                    /// \brief Constructor per defecte.
                    StaticArray() {
                    }
  
                    /// \brief Constructor copia.                    
                    StaticArray(const StaticArray& array) {
                        for (int i = 0; i < numElements; i++)
                            elements[i] = array.elements[i];
                    }
                    
                    /// \brief Constructor a partir d'un array 'C'.
                    StaticArray(const Element elements[]) {                        
                        for (int i = 0; i < numElements; i++)
                            this->elements[0] = elements[i];
                    }
                    
                    /// \brief Obte el tamany del array.
                    /// \return El tamany.
                    inline int getSize() const {
                        return numElements;
                    }
                    
                    /// \brief Operador d'assignacio.
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    StaticArray& operator=(const StaticArray& array) {                        
                        for (int i = 0; i < numElements; i++)
                            elements[i] = array.elements[i];                        
                        return *this;
                    }

                    /// \brief Operador d'assignacio a un array 'C'
                    /// \param array: El array a asignar.
                    /// \return Una referencia a this.
                    StaticArray& operator=(const Element elements[]) {                        
                        for (int i = 0; i < numElements; i++)
                            this->elements[i] = elements[i];                        
                        return *this;
                    }
                    
                    StaticArray operator+(const StaticArray& array) const {
                        StaticArray result;
                        for (int i = 0; i < numElements; i++)
                            result[i] = elements[i] + array.elements[i];
                        return result;
                    }
                    
                    StaticArray operator-(const StaticArray& array) const {
                        StaticArray result;
                        for (int i = 0; i < numElements; i++)
                            result[i] = elements[i] - array.elements[i];
                        return result;
                    }

                    bool operator ==(const StaticArray& array) const {
                        for (int i = 0; i < numElements; i++)
                            if (elements[i] != array.elements[i])
                                return false;
                        return true;
                    }

                    inline bool operator !=(const StaticArray& array) const {
                        return !operator==(array);
                    }

                    inline const Element& operator[](int index) const {
                        return elements[index];
                    }

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