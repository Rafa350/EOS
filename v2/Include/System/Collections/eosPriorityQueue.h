#ifndef __eosPriorityQueue__
#define __eosPriorityQueue__


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosStdHeapAllocator.h"


/// Std includes
///
#include <vector>
#include <queue>


namespace eos {

    /// \brief Implementa una cua amb prioritat.
    ///
    template <typename Priority, typename Element, int initialCapacity = 0, bool fixedCapacity = false>
    class PriorityQueue {
        private:
			class Node {
				public:
					Priority priority;
					Element element;
			};
    		class NodeComparator {
    			public:
    				bool operator () (const Node& left, const Node& right) {
    					return left.priority < right.priority;
    				}
    		};
    		typedef std::priority_queue<Node, std::vector<Node, StdHeapAllocator<Node> >, NodeComparator > Q;

        public:
            typedef Element Value;
            typedef Element& Reference;
            typedef const Element& CReference;
            typedef Element* Pointer;

        private:
            Q _q;

        public:
            PriorityQueue() :
            	_q(NodeComparator()) {
            }

            PriorityQueue(const PriorityQueue& other) = delete;

            /// \brief Afegeig un element a la cua.
            /// \param priority: La prioritat.
            /// \param element: L'element a afeigir.
            /// \return La posicio on s'ha insertat l'element.
            ///
            bool push(Priority priority, CReference element) {

            	if constexpr (fixedCapacity)
            		if (_q.size() == initialCapacity)
            			return false;

            	Node node = {
            		.priority = priority,
					.element = element
            	};
            	_q.push(node);
            	return true;
            }

            /// \brief Recupera i elimina de la cua el primer element.
            /// \param: El element recuperat.
            /// \return True si tot es correcte.
            ///
            bool pop() {
            	if (_q.size() > 0) {
            		_q.pop();
            		return true;
            	}
            	return false;
            }

            /// \brief Recupera de la cua el primer element.
            /// \param: El element recuperat.
            /// \return True si tot es correcte.
            ///
            CReference peek() const {
            	eosAssert(_q.size() > 0);
            	const Node& node = _q.top();
            	return node.element;
            }

            /// \brief Recupera de la cua la prioritat del primer element.
            /// \param: El element recuperat.
            /// \return True si tot es correcte.
            ///
            const Priority& peekPriority() const {
            	eosAssert(_q.size() > 0);
            	const Node& node = _q.top();
            	return node.priority;
            }

            /// \brief Borra el contingut de la cua.
            ///
            inline void clear() {
            	_q.clear();
            }

            /// \brief Obte el numero d'elements en �a cua.
            /// \return El nombre d'elements.
            ///
            inline int getSize() const {
            	return _q.size();
            }

            inline int getCapacity() const {
            	return _q.size();
            }

            /// \brief Indica si la cua es buida.
            /// \remarks True si es buida.
            ///
            inline bool isEmpty() const {
            	return _q.empty();
            }

            inline bool isFull() const {
            	if constexpr (fixedCapacity)
            		return _q.size() == initialCapacity;
            	else
            		return false;
            }
    };
    
}


#endif // __eosPriorityQueue__
