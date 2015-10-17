#ifndef __EOS_STACK_HPP
#define	__EOS_STACK_HPP


#include "eos.hpp"


namespace eos {
    
    template <typename elementType>
    class IStack {
        public:
            virtual const elementType &top() const = 0;
            virtual void push(const elementType &element) = 0;
            virtual const elementType &pop() = 0;
    };
    
    template <typename elementType>
    class Stack: public IStack<elementType> {
        private:
            unsigned count;
            unsigned size;
            elementType *elementPtr;

        public:
            Stack() :
                count(0),
                size(0),
                elementPtr(nullptr) {            
            }
                
            ~Stack() {
                
                if (size > 0)
                    delete[] elementPtr;
            }
            
            void push(const elementType &element) {
                
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
            
            const elementType &pop() {
                
                return elementPtr[--count];
            }
            
            const elementType &top() const {
                
                return elementPtr[count - 1];
            }

            void clear() {

                if (size > 0)
                    delete[] elementPtr;
                count = 0;
                size = 0;
            }
    };   
    
}




#endif


