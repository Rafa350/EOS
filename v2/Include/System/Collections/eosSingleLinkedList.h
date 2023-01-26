#pragma once
#ifndef __eosSimgleLinkedList__
#define __eosSimgleLinkedList__


namespace eos {
#ifdef EOS_USE_FULL_NAMESPACE
    namespace System {
        namespace Collections {
#endif            
            template <typename T>
            class SingleLinkedList {
                private:
                    struct Node {
                        Node *nextNode;
                        T data;
                    };
                    
                    Node *_firstNode;
                    Node *_lastNode;
                    
                public:
                    class Iterator {
                        private:
                            Node *_currentNode;
                            
                        public:
                            Iterator(Node *node):
                                _currentNode(node) {
                            }
                            
                            Iterator& operator++() {
                                if (_currentNode)
                                    _currentNode = _currentNode->nextNode;
                                return *this;
                            }
                        
                            Iterator operator++(int) {
                                Iterator iterator = *this;
                                ++*this;
                                return iterator;
                            }
                      
                            inline bool operator!=(const Iterator& iterator) {
                                return _current != iterator._currentNode;
                            }
                      
                            inline int operator*() {
                                return _currentNode->data;
                            }                    
                        }
                    
                    SingleLinkedList():
                        _first(nullptr),
                        _last(nullptr) {                
                    }
                    
                    ~SingleLinkedList() {
                        Node *currentNode = _firstNode;
                        while (currentNode) {
                            Node *node = currentNode;
                            currentNode = currentNode->nextNode;
                            delete node;
                        }
                    }
                    
                    void pushBack(T data) {
                        Node *node = new Node;
                        node->data = data;               
                        node->next = !_lastNode ? nullptr : _lastNode;
                        _lastNode = node;
                        if (!_firstNode)
                            _firstNode = _lastNode;                            
                    }
                    
                    inline Iterator begin() {
                        return Iterator(_firstNode);
                    }
                    
                    inline Iterator end() {
                        return Iterator(nullptr);
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosSimgleLInkedList__
