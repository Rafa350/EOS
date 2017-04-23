#ifndef __EOS_SYSTEM_COLLECTIONS_STACK_HPP
#define	__EOS_SYSTEM_COLLECTIONS_STACK_HPP


#include "eos.hpp"


namespace eos {
    
    /// \brief Pila generica implementada com array de bytes.
    //
    class GenericStack {
        private:
            unsigned capacity;
            unsigned count;
            unsigned size;
            void *container;
            
        public:
            virtual ~GenericStack();
            
        protected:
            GenericStack(unsigned size, unsigned initialCapacity);
            void push(const void *element);
            void pop();
            void *top() const;
            void top(const void *element) const;
            void clear();
            
            /// \brief Obte el nombre d'elements en la pila
            /// \return El nombre d'elements.
            inline unsigned getCount() const { return count; }

            /// \brief COmprova si la pila es buida.
            /// \return True si es buida.
            inline bool isEmpty() const { return count == 0; }
            
        private:
            void resize(unsigned newCapacity);
            void *getPtr(unsigned index) const;
    };
        
    
    /// \brief Interface generic per les piles.
    //
    template <typename T>
    class IStack {
        public:
            virtual const T &top() const = 0;
            virtual void push(const T &element) = 0;
            virtual void pop() = 0;
            virtual bool isEmpty() const = 0;
    };
    
    
    /// \brief Pila d'elements
    ///
    template <typename T>
    class Stack: private GenericStack, public IStack<T> {
        public:
            /// \brief Contructor.
            ///
            Stack(): 
                GenericStack(sizeof(T), 10) {
            }
           
            /// \brief Afegeix un element a la pila.
            /// \param element: L'element a afeigir.
            ///
            inline void push(const T &element) {

                GenericStack::push(&element);
            }            

            /// \brief Elimina el primer element de la pila.
            ///            
            inline void pop() {
                
                GenericStack::pop();
            }

            /// \brief: Obte el primer element de la lila.
            /// \return: El primer element.
            ///
            inline const T &top() const {
                
                return * ((T*) GenericStack::top());
            }
            
            /// \brief: Indica si la pila es buida.
            /// \return: True si es buida.
            ///
            inline bool isEmpty() const {
                
                return GenericStack::isEmpty();
            }
    };   
    
}




#endif


