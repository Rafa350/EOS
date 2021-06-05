#ifndef __eosPriorityQueueHeap__
#define __eosPriorityQueueHeap__


#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosDynamicArray.h"


namespace eos {

    /// \brief Cua amb prioritat. Adapta un contenidor per treballar 
    ///        com a  una cua amb prioritat. 
    ///
    template<typename Element, typename Container>
    class PriorityQueueHeap {
        public:
            typedef Element Value;
            typedef Element& Reference;
            typedef const Element& CReference;
            typedef bool (*Comparer)(CReference a, CReference b);

        private:
            Comparer comparer;
            Container heap;

        private:
            void heapifyUp(int idx) {
                int parentIdx = parent(idx);
                if (parentIdx < 0)
                    return;
                else if (comparer(heap[parentIdx], heap[idx])) {
                    swap(heap[parentIdx], heap[idx]);
                    heapifyUp(parentIdx);
                }   
            }
            
            void heapifyDown(int idx) {
                int largeIdx = idx;
                int leftChildIdx = leftChild(idx), rightChildIdx = rightChild(idx);
                if (leftChildIdx < heap.getSize()) {
                    if(comparer(heap[largeIdx], heap[leftChildIdx]))
                        largeIdx = leftChildIdx;
                }               
                if (rightChildIdx < heap.getSize()) {
                    if(comparer(heap[largeIdx], heap[rightChildIdx]))
                        largeIdx = rightChildIdx;
                }
                if (largeIdx != idx) {
                   swap(heap[largeIdx], heap[idx]);
                   heapifyDown(largeIdx);
                }
            }
            
            static void swap(Reference a, Reference b) {                
                CReference tmp = a;
                a = b;
                b = tmp;
            }
            
            inline static int leftChild(int i) {
                return (2 * i) + 1; 
            }
            
            inline static int rightChild(int i) { 
                return (2 * i) + 2; 
            }
            
            inline static int parent(int i) { 
                return (i - 1) / 2; 
            }

        public:
            PriorityQueueHeap(Comparer comparer) {
                this->comparer = comparer;
            }

            /// \brief Comprova si la cua es buida.
            /// \return True si es buida.
            ///
            inline bool isEmpty() const { 
                return heap.isEmpty(); 
            }
            
            /// \brief Afegeix un element a la cua.
            /// \param element: L'element.
            ///
            void push(CReference element) {
                heap.pushBack(element);
                heapifyUp(heap.getSize() - 1);
            }                
            
            /// \brief Extreu el primer element de la cua.
            ///
            void pop() {
                eosAssert(!heap.isEmpty());
                swap(heap[0], heap[heap.getSize() - 1]);
                heap.removeAt(heap.getSize() - 1);
                if (!isEmpty())
                   heapifyDown(0);
            }
            
            /// \brief Obte el primer element de la cua.
            /// \return El primer element.
            ///
            CReference top() const {
                eosAssert(!heap.isEmpty());
                return heap[0];
            }
    };
}


#endif // __eosPriorityQueueHeap__
