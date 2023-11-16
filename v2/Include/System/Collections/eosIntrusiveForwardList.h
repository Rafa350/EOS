#pragma once


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif

            template <typename T_, int tag_>
            class IntrusiveForwardList;

            template <typename T_, int tag_>
            class IntrusiveForwardListIterator;

            template <typename T_, int tag_>
            class IntrusiveForwardListNode {
                public:
                    using Type = IntrusiveForwardListNode<T_, tag_>*;

                private:
                    Type _next;

                public:
                    inline IntrusiveForwardListNode() :
                        _next {nullptr} {
                    }

                friend IntrusiveForwardList<T_, tag_>;
                friend IntrusiveForwardListIterator<T_, tag_>;
            };

            template <typename T_, int tag_>
            class IntrusiveForwardListIterator {
                public:
                    using Type = IntrusiveForwardListNode<T_, tag_>*;

                private:
                    Type _node;

                public:
                    inline IntrusiveForwardListIterator(Type node) :
                        _node {node} {
                    }

                    inline IntrusiveForwardListIterator& operator ++ () {
                        _node = _node->_next;
                        return *this;
                    }

                    inline IntrusiveForwardListIterator operator ++ (int) {
                        IntrusiveForwardListIterator iterator(_node);
                        _node = _node->_next;
                        return iterator;
                    }

                    inline T_* operator *() {
                        return static_cast<T_*>(_node);
                    }

                friend bool operator == (const IntrusiveForwardListIterator &a, const IntrusiveForwardListIterator &b) {
                    return a._node == b._node;
                }
                friend bool operator != (const IntrusiveForwardListIterator &a, const IntrusiveForwardListIterator &b) {
                    return a._node != b._node;
                }
            };

            template <typename T_, int tag_>
            class IntrusiveForwardList {
                public:
                    using ValueType = T_*;
                    using NodeType = IntrusiveForwardListNode<T_, tag_>*;
                    using Iterator = IntrusiveForwardListIterator<T_, tag_>;
                    using CIterator = const IntrusiveForwardListIterator<T_, tag_>;

                private:
                    NodeType _first;

                public:
                    inline IntrusiveForwardList() :
                        _first {nullptr} {
                    }

                    void clear() {
                        while (!empty())
                            pop_front();
                    }

                    void push_front(ValueType node) {
                        auto n = static_cast<NodeType>(node);
                        n->_next = _first;
                        _first = n;
                    }

                    void pop_front() {
                       auto n = _first;
                       _first = _first->_next;
                       n->_next = nullptr;
                    }

                    void remove(ValueType node) {
                        NodeType p = nullptr;
                        for (auto n = _first; n != nullptr; n = n->_next) {
                            if (n == static_cast<Type>(node)) {
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

                    inline ValueType front() const {
                        return static_cast<ValueType>(_first);
                    }

                    inline bool empty() const {
                        return _first == nullptr;
                    }

                    constexpr bool full() const {
                        return false;
                    }

                    inline Iterator begin() {
                        return Interator(_first);
                    }

                    inline CIterator begin() const {
                        return CIterator(_first);
                    }

                    constexpr Iterator end() {
                        return Iterator(nullptr);
                    }

                    constexpr CIterator end() const {
                        return CIterator(nullptr);
                    }
            };


#ifdef EOS_USE_FULL_NAMESPACE
        }
    }
#endif
}
