#ifndef __eosLinkedList__
#define __eosLinkedList__

#include "eos.h"


namespace eos {
    
    /// \brief Llista implementada com a llista enllaçada. La llista s'ordena tal com 
    /// s'afegeixen els elements.
    ///
    template <typename T>
    class LinkedList {
        private:
            struct Node {
                Node *prev;
                T element;
            }
            
            Node* last;            
        
        public:
            /// \brief Constructor.
            LinkedList(
                nodes(nullptr) {
                
            }
            
            /// \brief Destructor.
            ~LinkedList() {
                
                Node *node = last;
                while (node != nullptr) {
                    Node *p = node;
                    node = node->prev;
                    delete p;
                }
            }
            
            /// \brief Afegeig un element a la llista.
            /// \param element: L'element a afeigir.
            void add(T element) {

                Node *node = new Node();

                node->prev = last;
                
                last = node;       
                if (first == nullptr)
                    first = node;

                node->element = element;
            }
            
            /// \brief Obte el primer element de la llista.
            /// \return El primer element.
            T getFirst() const {
                
                return first ? first->element : nullptr;
            }

            /// \brief Obte l'ultim element de la llista.
            /// \return El primer element.
            T getLast() const {
                
                return last ? last->element : nullptr;
            }
    }
}


#endif