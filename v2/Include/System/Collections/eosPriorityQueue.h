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
#include <algorithm>


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
				public:
					inline bool operator == (const Node& other) {
						return
							(priority == other.priority) &&
							(element == other.element);
					}
			};

			class NodeComparator {
    			public:
    				bool operator () (const Node& left, const Node& right) {
    					return left.priority < right.priority;
    				}
    		};

			template <typename T, typename C>
    	    class custom_priority_queue: public std::priority_queue<T, std::vector<T, eos::StdHeapAllocator<T> >, C> {
    	        public:
    	            custom_priority_queue(C comparator):
    	                std::priority_queue<T, std::vector<T, eos::StdHeapAllocator<T> >, C>(comparator) {
    	            }

    	            bool remove(const T& value) {
    	                auto it = std::find(this->c.begin(), this->c.end(), value);
    	                if (it != this->c.end()) {
    	                    this->c.erase(it);
    	                    std::make_heap(this->c.begin(), this->c.end(), this->comp);
    	                    return true;
    	                }
    	                else
    	                    return false;
    	            }

    	            typename std::vector<T, eos::StdHeapAllocator<T> >::const_iterator begin() const {
    	                return this->c.begin();
    	            }

    	            typename std::vector<T, eos::StdHeapAllocator<T> >::const_iterator end() const {
    	                return this->c.end();
    	            }
    	    };

			typedef custom_priority_queue<Node, NodeComparator> Q;

        public:
            typedef Element Value;
            typedef Element& Reference;
            typedef const Element& CReference;
            typedef Element* Pointer;

        private:
            Q _q;

        public:
            /// \brief Contructor
            ///
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
            /// \return True si tot es correcte.
            ///
            CReference peek() const {
            	eosAssert(_q.size() > 0);
            	const Node& node = _q.top();
            	return node.element;
            }

            /// \brief Recupera de la cua la prioritat del primer element.
            /// \return True si tot es correcte.
            ///
            const Priority& peekPriority() const {
            	eosAssert(_q.size() > 0);
            	const Node& node = _q.top();
            	return node.priority;
            }

            /// \brief Elimina un element de la cua.
            /// \param element: El element a eliminar.
            /// \return True si toto es correcte.
            ///
            inline bool remove(CReference element) {
                for (auto it = _q.begin(); it != _q.end(); it++) {
                    const Node& node = *it;
                    if (node.element == element) {
                        _q.remove(node);
                        return true;
                    }
                }
                return false;
            }

            /// \brief Comprova si la cua conte un element.
            /// \param element: El element a comprovar.
            /// \return True si esta en la cua, false en cas contrari.
            ///
            inline bool contains(CReference element) {
                for (auto it = _q.begin(); it != _q.end(); it++) {
                    const Node& node = *it;
                    if (node.element == element)
                    	return true;
                }
                return false;
            }

            /// \brief Borra el contingut de la cua.
            ///
            inline void clear() {
            	_q.clear();
            }

            /// \brief Obte el numero d'elements en la cua.
            /// \return El valor.
            ///
            inline int getSize() const {
            	return _q.size();
            }

            /// \brief Obte la capacitat de la cua.
            /// \return El valor.
            ///
            inline int getCapacity() const {
            	return _q.size();
            }

            /// \brief Indica si la cua es buida.
            /// \remarks True si es buida.
            ///
            inline bool isEmpty() const {
            	return _q.empty();
            }

            /// \brief Indica si la cua es plena
            /// \return True si es plena.
            ///
            inline bool isFull() const {
            	if constexpr (fixedCapacity)
            		return _q.size() == initialCapacity;
            	else
            		return false;
            }
    };

}


#endif // __eosPriorityQueue__
