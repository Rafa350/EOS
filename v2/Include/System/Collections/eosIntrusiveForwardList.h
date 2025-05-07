#pragma once


// EOS includes
//
#include "eos.h"
#include "eosAssert.h"


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace system {
        namespace collections {
#endif

            template <typename T_, int tag_>
            class IntrusiveForwardList;

            template <typename T_, int tag_>
            class IntrusiveForwardListIterator;

            template <typename T_, int tag_>
            class IntrusiveForwardListNode {
                public:
                    using NodeType = IntrusiveForwardListNode<T_, tag_>*;

                private:
                    NodeType _next;

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
                    using ValueType = T_*;
                    using NodeType = IntrusiveForwardListNode<T_, tag_>*;

                private:
                    NodeType _node;

                public:
                    inline IntrusiveForwardListIterator(NodeType node) :
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

                    inline ValueType operator *() {
                        return static_cast<ValueType>(_node);
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
                            popFront();
                    }

                    void pushFront(ValueType element) {
                        auto n = static_cast<NodeType>(element);
                        n->_next = _first;
                        _first = n;
                    }

                    void popFront() {
                       auto n = _first;
                       _first = _first->_next;
                       n->_next = nullptr;
                    }

                    void remove(ValueType element) {
                        NodeType p = nullptr;
                        for (auto n = _first; n != nullptr; n = n->_next) {
                            if (n == static_cast<NodeType>(element)) {
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

                    bool contains(ValueType element) const {
                    	auto n = _first;
                    	while (n) {
                    		if (n == static_cast<NodeType>(element))
                    			return true;
                    		n = n->_next;
                    	}
                    	return false;
                    }

                    constexpr bool full() const {
                        return false;
                    }

                    inline Iterator begin() {
                        return Iterator(_first);
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
