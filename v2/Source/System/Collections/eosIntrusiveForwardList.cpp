module;


#include "eos.h"
#include <concepts>


export module Eos.System.Collections.IntrusiveForwardList;


namespace local {

    template <typename T_>
    concept IsClass = std::is_class_v<T_>;

}

namespace eos {

    export template <local::IsClass T_, int tag_>
    class IntrusiveForwardList;

    export template <local::IsClass T_, int tag_>
    class IntrusiveForwardListIterator;

    export template <local::IsClass T_, int tag_>
    class IntrusiveForwardListNode {
        public:
            using NodeType = IntrusiveForwardListNode<T_, tag_>;
            using NodePtr = NodeType*;

        private:
            NodePtr _next;

        public:
            IntrusiveForwardListNode() :
                _next {nullptr} {
            }

        friend IntrusiveForwardList<T_, tag_>;
        friend IntrusiveForwardListIterator<T_, tag_>;
    };


    export template <local::IsClass T_, int tag_>
    class IntrusiveForwardListIterator {
        public:
            using ValueType = T_;
            using ValuePtr = ValueType*;
            using ValueRef = ValueType&;
            using NodeType = IntrusiveForwardListNode<T_, tag_>;
            using NodePtr = NodeType*;

        private:
            NodePtr _node;

        public:
            IntrusiveForwardListIterator(NodePtr node) :
                _node {node} {
            }

            IntrusiveForwardListIterator& operator ++ () {
                _node = _node->_next;
                return *this;
            }

            IntrusiveForwardListIterator operator ++ (int) {
                IntrusiveForwardListIterator iterator(_node);
                _node = _node->_next;
                return iterator;
            }

            ValuePtr operator *() const {
                return static_cast<ValuePtr>(_node);
            }

        friend bool operator == (const IntrusiveForwardListIterator &a, const IntrusiveForwardListIterator &b) {
                return a._node == b._node;
        }

        friend bool operator != (const IntrusiveForwardListIterator &a, const IntrusiveForwardListIterator &b) {
            return a._node != b._node;
        }
    };


    export template <local::IsClass T_, int tag_>
    class IntrusiveForwardList {
        public:
            using ValueType = T_;
            using ValuePtr = ValueType*;
            using ValueRef = ValueType&;
            using NodeType = IntrusiveForwardListNode<T_, tag_>;
            using NodePtr = NodeType*;
            using Iterator = IntrusiveForwardListIterator<T_, tag_>;
            using CIterator = const IntrusiveForwardListIterator<T_, tag_>;

        private:
            NodePtr _first;

        public:
            IntrusiveForwardList();
            IntrusiveForwardList(const IntrusiveForwardList &other) = delete;

            IntrusiveForwardList& operator = (const IntrusiveForwardList &other) = delete;

            void addFront(NodePtr element);
            void addAfter(NodePtr afterElement, NodePtr element);

            void clear();
            void removeFront();
            void remove(NodePtr element);

            [[nodiscard]] ValuePtr getFirst() const;
            [[nodiscard]] ValuePtr getNext(NodePtr element) const;

            [[nodiscard]] bool isEmpty() const;

            void pushFront(NodePtr element) { addFront(element); }
            void popFront() { removeFront(); }

            bool contains(NodePtr element) const {
                auto n = _first;
                while (n != nullptr) {
                    if (n == element)
                        return true;
                    n = n->_next;
                }
                return false;
            }

            Iterator begin() {
                return Iterator(_first);
            }

            CIterator begin() const {
                return CIterator(_first);
            }

            constexpr Iterator end() {
                return Iterator(nullptr);
            }

            constexpr CIterator end() const {
                return CIterator(nullptr);
            }
    };
}


using namespace eos;
using namespace local;


/// ---------------------------------------------------------------------------
/// @brief    Constructor per defecte.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <IsClass T_, int tag_>
IntrusiveForwardList<T_, tag_>::IntrusiveForwardList() :
    _first {nullptr} {
}


/// ---------------------------------------------------------------------------
/// @brief    Buida la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <IsClass T_, int tag_>
void IntrusiveForwardList<T_, tag_>::clear() {

    while (!isEmpty())
        removeFront();
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element al principi de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element a afeigir.
///
template <IsClass T_, int tag_>
void IntrusiveForwardList<T_, tag_>::addFront(
    NodePtr element) {

    element->_next = _first;
    _first = element;
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element despres de l'element especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    afterEElement: L'element s'afegirar despres d'aquest.
/// @param    element: L'element a afeigir.
///
template <IsClass T_, int tag_>
void IntrusiveForwardList<T_, tag_>::addAfter(
    NodePtr afterElement,
    NodePtr element) {

}


/// ---------------------------------------------------------------------------
/// @brief    Elimina el primer element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <IsClass T_, int tag_>
void IntrusiveForwardList<T_, tag_>::removeFront() {

    if (_first != nullptr) {
        auto e = _first;
        _first = _first->_next;
        e->_next = nullptr;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Elimina un element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element a eliminar.
///
template <IsClass T_, int tag_>
void IntrusiveForwardList<T_, tag_>::remove(
    NodePtr element) {

    NodePtr p = nullptr;
    for (auto n = _first; n != nullptr; n = n->_next) {
        if (n == element) {
            if (p == nullptr)
                _first = n->_next;
            else
                p->_next = n->_next;
            n->_next = nullptr;
            return;
        }
        p = n;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el primer element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @return   El element posterior.
///
template <IsClass T_, int tag_>
IntrusiveForwardList<T_, tag_>::ValuePtr IntrusiveForwardList<T_, tag_>::getFirst() const {

    return static_cast<ValuePtr>(_first);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'element posterior al especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element
/// @return   El element posterior.
///
template <IsClass T_, int tag_>
IntrusiveForwardList<T_, tag_>::ValuePtr IntrusiveForwardList<T_, tag_>::getNext(
    NodePtr element) const {

    return static_cast<ValuePtr>(element->_next);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la llista es buida.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @return   Trus si la llista es buida.
///
template <IsClass T_, int tag_>
bool IntrusiveForwardList<T_, tag_>::isEmpty() const {

    return _first == nullptr;
}
