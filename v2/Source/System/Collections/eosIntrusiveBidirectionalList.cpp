module;


#include "eos.h"


export module Eos.System.Collections.IntrusiveBidirectionalList;


import Eos.Concepts;


namespace eos {

    export template <IsClass T_, int tag_>
    class IntrusiveBidirectionalList;

    export template <IsClass T_, int tag_>
    class IntrusiveBidirectionalListNode {
        public:
            using NodeType = IntrusiveBidirectionalListNode<T_, tag_>;
            using NodePtr = NodeType*;

        private:
            NodePtr _next;
            NodePtr _prev;

        public:
            IntrusiveBidirectionalListNode() :
                _next {nullptr},
                _prev {nullptr} {
            }

        friend IntrusiveBidirectionalList<T_, tag_>;
    };

    export template <IsClass T_, int tag_>
    class IntrusiveBidirectionalList {
        public:
            using ValueType = T_;
            using ValuePtr = ValueType*;
            using ValueRef = ValueType&;
            using NodeType = IntrusiveBidirectionalListNode<T_, tag_>;
            using NodePtr = NodeType*;

        private:
            NodePtr _first;
            NodePtr _last;

        public:
            IntrusiveBidirectionalList();
            IntrusiveBidirectionalList(const IntrusiveBidirectionalList &other) = delete;

            IntrusiveBidirectionalList& operator = (const IntrusiveBidirectionalList &other) = delete;

            void addFront(NodePtr element);
            void addBack(NodePtr element);
            void addBefore(NodePtr beforeElement, NodePtr element);
            void addAfter(NodePtr afterElement, NodePtr element);

            void clear();
            void removeFront();
            void removeBack();
            void remove(NodePtr element);

            [[nodiscard]] ValuePtr getFirst() const;
            [[nodiscard]] ValuePtr getLast() const;
            [[nodiscard]] ValuePtr getNext(NodePtr element) const;
            [[nodiscard]] ValuePtr getPrev(NodePtr element) const;

            [[nodiscard]] bool isEmpty() const;
    };

}


/// ---------------------------------------------------------------------------
/// @brief    Constructor per defecte.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <eos::IsClass T_, int tag_>
eos::IntrusiveBidirectionalList<T_, tag_>::IntrusiveBidirectionalList() :
    _first {nullptr},
    _last {nullptr} {

}


/// ---------------------------------------------------------------------------
/// @brief    Buida la llista.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::clear() {

    while (!isEmpty())
        removeFront();
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element al principi de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element a afeigir.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::addFront(
    NodePtr element) {

    if (_first == nullptr) {
        element->_prev = nullptr;
        element->_next = nullptr;
    }
    else {
        element->_prev = _first->_prev;
        element->_next = _first;
        _first->_prev = element;
    }
    _first = element;
    if (_last == nullptr)
        _last = _first;
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element al final de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element a afeigir.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::addBack(
    NodePtr element) {

}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element abans de l'element especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    beforeElement: L'element s'afegirar abans d'aquest. Si es null.
///           aleshores s'afegeix al principi de la llista.
/// @param    element: L'element a afeigir.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::addBefore(
    NodePtr beforeElement,
    NodePtr element) {

    if (beforeElement == nullptr)
        addToBegin(element);
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element despres de l'element especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    afterEElement: L'element s'afegirar despres d'aquest. Si es null,
///           aleshores s'afegeix al final de la llista.
/// @param    element: L'element a afeigir.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::addAfter(
    NodePtr afterElement,
    NodePtr element) {

    if (afterElement == nullptr)
        addToEnd(element);
}


/// ---------------------------------------------------------------------------
/// @brief    Elimina el primer element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::removeFront() {

    if (_first != nullptr)
        remove(_first);
}


/// ---------------------------------------------------------------------------
/// @brief    Elimina l'ultim element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::removeBack() {

    if (_last != nullptr)
        remove(_last);
}


/// ---------------------------------------------------------------------------
/// @brief    Elimina un element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element a eliminar.
///
template <eos::IsClass T_, int tag_>
void eos::IntrusiveBidirectionalList<T_, tag_>::remove(
    NodePtr element) {

}


/// ---------------------------------------------------------------------------
/// @brief    Obte el primer element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @return   El primer element.
///
template <eos::IsClass T_, int tag_>
eos::IntrusiveBidirectionalList<T_, tag_>::ValuePtr
        eos::IntrusiveBidirectionalList<T_, tag_>::getFirst() const {

    return static_cast<ValuePtr>(_first);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'ultim element de la llista.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @return   L'ultim element.
///
template <eos::IsClass T_, int tag_>
eos::IntrusiveBidirectionalList<T_, tag_>::ValuePtr
        eos::IntrusiveBidirectionalList<T_, tag_>::getLast() const {

    return static_cast<ValuePtr>(_last);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'element posterior al especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element
/// @return   L'element posterior
///
template <eos::IsClass T_, int tag_>
eos::IntrusiveBidirectionalList<T_, tag_>::ValuePtr
        eos::IntrusiveBidirectionalList<T_, tag_>::getNext(
    NodePtr element) const {

    return static_cast<ValuePtr>(
            element == nullptr ? nullptr :  element->_next);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte l'element anterior al especificat.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @param    element: L'element
/// @return   L'element anterior.
///
template <eos::IsClass T_, int tag_>
eos::IntrusiveBidirectionalList<T_, tag_>::ValuePtr
        eos::IntrusiveBidirectionalList<T_, tag_>::getPrev(
    NodePtr element) const {

    return static_cast<ValuePtr>(
            element == nullptr ? nullptr :  element->_prev);
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la llista es buida.
/// @tparam   T_: El tipus de l'element.
/// @tparam   tag_: Etiqueta per diferenciar tipus.
/// @return   Trus si la llista es buida.
///
template <eos::IsClass T_, int tag_>
bool eos::IntrusiveBidirectionalList<T_, tag_>::isEmpty() const {

    return _first == nullptr;
}
