#ifndef __EOS_STACK_HPP
#define	__EOS_STACK_HPP


#include "eos.hpp"


namespace eos {
    
    template <typename elementType>
    class IStack {
        public:
            virtual const elementType &top() const = 0;
            virtual void push(elementType &element) = 0;
            virtual void pop() = 0;
    };
    
    class GenericStack {
        private:
            unsigned capacity;
            unsigned count;
            unsigned size;
            void *container;
        public:
            GenericStack(unsigned size, unsigned initialCapacity);
            ~GenericStack();
            void pushElement(void *element);
            void popElement();
            void *topElement() const;
            inline unsigned getCount() const { return count; }
        private:
            void resize(unsigned newCapacity);
            void *getPtr(unsigned index) const;
    };
    
    template <typename elementType>
    class Stack: private GenericStack, public IStack<elementType> {
        public:
            Stack(): 
                GenericStack(sizeof(elementType), 10) {
            }
           
            inline void push(elementType &element) {

                pushElement(&element);
            }            
            
            inline void pop() {
                
                popElement();
            }            
            
            inline const elementType &top() const {
                
                return * ((elementType*) topElement());
            }
    };   
    
}




#endif


