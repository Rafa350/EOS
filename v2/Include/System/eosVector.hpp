#ifndef __EOS_VECTOR_HPP
#define	__EOS_VECTOR_HPP


#include "eos.hpp"


namespace eos {
    
    template <typename elementType>
    class IVector {
        public:
            virtual unsigned getCount() const = 0;
            virtual const elementType &getElement(const unsigned index) const = 0;
            virtual const elementType &operator[](const unsigned index) const = 0;
    };
    
    template <typename elementType>
    class Vector: public IVector<elementType> {
        private:
            unsigned count;
            unsigned size;
            elementType *elementPtr;

        public:
            Vector() :
                count(0),
                size(0),
                elementPtr(nullptr) {            
            }
                
            ~Vector() {
                
                if (size > 0)
                    delete[] elementPtr;
            }
            
            void add(const elementType &element) {
                
                if (count == size) {
                    size += 10;
                    elementType *newElementPtr = new elementType[size];
                    if (count > 0) {
                        memcpy(newElementPtr, elementPtr, count);
                        delete[] elementPtr;
                    }
                    
                    elementPtr = newElementPtr;
                }
                
                elementPtr[count++] = element;
            }
            
            void remove(const elementType &element) {
                
            }
            
            void clear() {

                if (size > 0)
                    delete[] elementPtr;
                count = 0;
                size = 0;
            }
            
            unsigned getCount() const { 
                
                return count; 
            }
            
            const elementType &getElement(const unsigned index) const {

                return elementPtr[index];                
            }
            
            const elementType &operator[](const unsigned index) const {
                
                return elementPtr[index];
            }           
    };
}



#endif	
