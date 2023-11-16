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
            class IntrusiveList;

            template <typename T_, int tag_>
            class IntrusiveListIterator;

            template <typename T_, int tag_>
            class IntrusiveListNode {
                public:
                    using NodeType = IntrusiveListNode<T_, tag_>*;

                private:
                    NodeType _next;
                    NodeType _prev;

                public:
                    inline IntrusiveListNode() :
                        _next {nullptr},
                        _prev {nullptr} {
                    }

                friend IntrusiveList<T_, tag_>;
                friend IntrusiveListIterator<T_, tag_>;
            };

            template <typename T_, int tag_>
            class IntrusiveListIterator {
                public:
                    using ValueType ? T_*;
                    using NodeType = IntrusiveListNode<T_, tag_>*;

                private:
                    NodeType _node;

                public:
                    inline IntrusiveListIterator(NodeType node) :
                        _node {node} {
                    }

                    inline IntrusiveListIterator& operator ++ () {
                        _node = _node->_next;
                        return *this;
                    }

                    inline IntrusiveListIterator operator ++ (int) {
                        IntrusiveListIterator iterator(_node);
                        _node = _node->_next;
                        return iterator;
                    }

                    inline ValueType operator *() {
                        return static_cast<ValueType>(_node);
                    }

                friend bool operator == (const IntrusiveListIterator &a, const IntrusiveListIterator &b) {
                    return a._node == b._node;
                }
                friend bool operator != (const IntrusiveListIterator &a, const IntrusiveListIterator &b) {
                    return a._node != b._node;
                }
            };

            template <typename T_, int tag_>
            class IntrusiveList {
                public:
                    using ValueType = T_*;
                    using NodeType = IntrusiveListNode<T_, tag_>*;
                    using Iterator = IntrusiveListIterator<T_, tag_>;
                    using CIterator = const IntrusiveListIterator<T_, tag_>;

                private:
                    NodeType _first;
                    NodeType _last;

                public:
                    inline IntrusiveForwardList() :
                        _first {nullptr},
                        _last {nullptr} {
                    }

                    void clear() {
                        while (!empty())
                            pop_front();
                    }

                    void pushFront(ValueType element) {
                        auto n = static_cast<NodeType>(element);
                        n->_next = _first;
                        _first = n;
                    }

                    void pushBack(ValueType element) {
                    }

                    void popFront() {
                       auto n = _first;
                       _first = _first->_next;
                       n->_next = nullptr;
                    }

                    void popBack() {
                    }

                    void remove(ValueType node) {
                    }

                    inline ValueType front() const {
                        return static_cast<ValueType>(_first);
                    }

                    inline ValueType back() const {
                        return static_cast<ValueType>(_last);
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
