#ifndef __EOS_VECTOR_HPP
#define	__EOS_VECTOR_HPP


#include "eos.hpp"


namespace eos {
    
    template <typename elementType>
    class Vector {
        public:
            Vector() :
                size(0),
                space(0),
                elementPtr(nullptr) {            
            }
                
            ~Vector() {
                
                if (space > 0)
                    delete[] elementPtr;
            }
            
            void add(const elementType &element) {
                
                if (size == space) {
                    space += 10;
                    elementType *newElementPtr = new elementType[space];
                    if (size > 0)
                        memcpy(newElementPtr, elementPtr, size);
                    delete[] elementPtr;
                    
                    elementPtr = newElementPtr;
                }
                
                elementPtr[size++] = element;
            }
            
            void remove(const elementType &element) {
                
            }
            
            inline unsigned getSize() { 
                
                return size; 
            }
            
            inline elementType &operator[](const unsigned index) {
                
                return elementPtr[index];
            }
            
        private:
            unsigned size;
            unsigned space;
            elementType *elementPtr;
    };
}



#endif	
