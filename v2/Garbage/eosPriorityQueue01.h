#ifndef __eosPriorityQueue__
#define __eosPriorityQueue__


// EOS includes
//
#include "eos.h"
#include "System/Collections/eosDynamicArray.h"


namespace eos {

    /// \brief Implementa una cua amb prioritat basada en una lista
    ///
    template <typename Priority, typename Element, const unsigned initialCapacity = 0>
    class PriorityQueue {
        private:
            struct Node {
                Priority priority;
                Element element;
            };

            typedef DynamicArray<Node, initialCapacity> List;

        public:
            class Iterator {
                private:
                    List& list;
                    unsigned index;

                public:
                    Iterator(PriorityQueue<Priority, Element, initialCapacity>& queue):
                        list(queue.list),
                        index(0) {
                    }

                    inline bool first() {
                        if (list.isEmpty())
                            return false;
                        else {
                            index = 0;
                            return true;
                        }
                    }

                    inline bool next() {
                        if (!list.isEmpty() && index < list.getCount()) {
                            index += 1;
                            return true;
                        }
                        else
                            return false;
                    }

                    inline bool hasNext() const {
                        return index < list.getCount();
                    }

                    inline const Element& getCurrent() const {
                        return list[index].element;
                    }
            };

        private:
            List list;

        public:
            /// \brief Afegeig un element a la cua.
            /// \param priority: La prioritat.
            /// \param element: L'element a afeigir.
            /// \return La posicio on s'ha insertat l'element.
            ///
            unsigned push(Priority priority, const Element& element) {

                unsigned index = 0;
                while ((index < list.getSize()) &&
                       (list[index].priority <= priority))
                    index += 1;

                Node node;
                node.priority = priority;
                node.element = element;
                return list.insertAt(index, node) ? index : unsigned(-1);
            }

            /// \brief Recupera i elimina de la cua el primer element.
            /// \param: El element recuperat.
            /// \return True si tot es correcte.
            ///
            bool pop(Element& element) {

                if (peek(element)) {
                    list.removeAt(0);
                    return true;
                }
                else
                    return false;
            }

            /// ----------------------------------------------------------
            /// \brief Elimina el element especificat.
            /// \param element: El element a eliminar.
            /// \return True si tot es correcte.
            ///
            bool remove(Element& element) {

                for (unsigned i = 0, ii = list.getSize(); i < ii; i++) {
                    if (list[i].element == element)
                        return list.removeAt(i);
                }
                return false;
            }

            /// \brief Elimina de la cua el primer element.
            /// \return True si s'ha realitzat l'operacio correctament.
            ///
            bool pop() {
                if (list.isEmpty())
                    return false;
                else {
                    list.removeAt(0);
                    return true;
                }
            }

            /// \brief Recupera de la cua el primer element.
            /// \param: El element recuperat.
            /// \return True si tot es correcte.
            ///
            bool peek(Element& element) {
                if (list.isEmpty())
                    return false;
                else {
                    element = list.getFront().element;
                    return true;
                }
            }

            /// \brief Comprova si el element existeix.
            /// \param element:El element a comprovar.
            /// \return True si existeix, false en cas conmtrari.
            ///
            bool contains(const Element& element) {
                for (unsigned i = 0, ii = list.getSize(); i < ii; i++)
                    if (list[i].element == element)
                        return true;
                return false;
            }

            /// \brief Borra el contingut de la cua.
            ///
            inline void clear() {
                list.clear();
            }

            /// \brief Obte el numero d'elements en �a cua.
            /// \return El nombre d'elements.
            ///
            inline unsigned getSize() const {
                return list.getSize();
            }

            /// \brief Indica si la cua es buida.
            /// \remarks True si es buida.
            ///
            inline bool isEmpty() const {
                return list.isEmpty();
            }
    };
    
}


#endif // __eosPriorityQueue__
