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
                        T element;
                    };
                    
                    unsigned _count;
                    Node *_firstNode;
                    Node *_lastNode;
                    
                public:
                    using Value = T;
                    using Pointer = T*;
                    using Reference = T&;
                    using CReference = const T&;

                    class Iterator {
                        private:
                            Node *_currentNode;
                            
                        public:
                            Iterator(Node *node):
                                _currentNode(node) {
                            }
                            
                            Iterator(const Iterator &iterator):
                                _currentNode(iterator._currentNode) {
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
                      
                            inline bool operator==(const Iterator &iterator) {
                                return _currentNode == iterator._currentNode;
                            }

                            inline bool operator!=(const Iterator &iterator) {
                                return _currentNode != iterator._currentNode;
                            }
                      
                            inline Reference operator*() const {
                                return _currentNode->element;
                            }                    
                    };

                    using CIterator = const Iterator;

                    /// \brief Constructor.
                    ///
                    SingleLinkedList():
                    	_count(0),
                        _firstNode(nullptr),
                        _lastNode(nullptr) {
                    }
                    
                    /// \brief Destructor
                    ///
                    ~SingleLinkedList() {
                    	clear();
                    }
                    
                    /// \brief Afegeix un element al final de la llista
                    /// \param element: L'element a afeigir.
                    ///
                    void pushBack(CReference element) {
                        Node *node = new Node;
                        node->element = element;
                        node->nextNode = nullptr;
                        if (_lastNode)
                        	_lastNode->nextNode = node;
                        _lastNode = node;
                        if (!_firstNode)
                            _firstNode = node;
                        _count++;
                    }
                    
                    /// \brief Elimina l'ultim node de la llista
                    ///
                    void popBack() {
                    	Node *node = _firstNode;
                    	while (node && (node->nextNode != _lastNode))
                    		node = node->nextNode;
                    	if (node) {
                    		node->nextNode = nullptr;
                    		_lastNode = node;
                    	}
                    }

                    /// \brief Obte una referencia al primer element
                    /// \return L'element.
                    ///
                    inline Reference peekFront() const {
                    	return _firstNode->element;
                    }

                    /// \brief Obte una referencia a l'ultim element
                    /// \return L'element.
                    ///
                    inline Reference peekBack() const {
                    	return _lastNode->element;
                    }

                    /// \brief Elimina el element especificat.
                    /// \param element: L'element.
                    ///
                    void remove(CReference element) {

                    }

                    /// \brief Comprova si l'element pertany a la llista.
                    /// \param element: L'element.
                    /// \return True si pertany, false en cas contrari.
                    ///
                    bool contains(CReference element) const {
                    	Node *node = _firstNode;
                    	while (node) {
                    		if (node->element == element)
                    			return true;
                    		node = node->nextNode;
                    	}
                    	return false;
                    }

                    /// \brief Buida el contingut de la llista.
                    ///
                    void clear() {
                        Node *currentNode = _firstNode;
                        while (currentNode) {
                            Node *node = currentNode;
                            currentNode = currentNode->nextNode;
                            delete node;
                        }
                        _count = 0;
                        _firstNode = nullptr;
                        _lastNode = nullptr;
                    }

                    /// \brief Obte el iterator inicial
                    ///
                    inline Iterator begin() {
                        return Iterator(_firstNode);
                    }
                    
                    /// \brief Obte el iteratror final.
                    ///
                    inline Iterator end() {
                        return Iterator(nullptr);
                    }

                    /// \brief Obte el nombre d'elements en la llista.
                    /// \return El resultat.
                    ///
                    inline unsigned getSize() const {
                    	return _count;
                    }

                    /// \brief Comprova si la llista es buida.
                    /// \return TRue si es buida, false en cas contrari.
                    ///
                    inline bool isEmpty() const {
                    	return _firstNode == nullptr;
                    }
            };
#ifdef EOS_USE_FULL_NAMESPACE            
        }
    }
#endif    
}


#endif // __eosSimgleLInkedList__
