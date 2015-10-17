#include "System/elsList.hpp"
#include "System/eosList.hpp"


using namespace eos:


GenericList::GenericList(
    unsigned elementSize) {
    
    this->elementSize = elementSize;
    this->count = 0;
    this->size = 0;
    this->data = nullptr;
}

GenericList::~GenericList() {
    
    if (data != nullptr)
        delete[] data;
}


void GenericList::addElement(
    void* data) {
    
}

void GenericList::removeElement(
    void* data) {
    
}