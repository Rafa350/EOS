#ifndef __EOS_VECTOR_HPP
#define	__EOS_VECTOR_HPP


#include "eos.hpp"


namespace eos {
    
    template <typename elementType>
    class Vector {
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
            
            inline unsigned getCount() { 
                
                return count; 
            }
            
            inline elementType &getElement(const unsigned index) {

                return elementPtr[index];                
            }
            
            inline elementType &operator[](const unsigned index) {
                
                return elementPtr[index];
            }           
    };
}



#endif	
