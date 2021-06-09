#include "StringV2.h"
#include "OSAL/osalHeap.h"

#include <string.h>


struct StringV2::Impl{
    unsigned length;
    char* p;
};


StringV2::StringV2(
    const char* cstr):

    _pImpl(allocate(cstr)) {

}

StringV2::StringV2(
    const StringV2& str):

    _pImpl(str._pImpl) {

}


StringV2::PImpl StringV2::allocate(
    const char* cstr) {

    unsigned length = strlen(cstr);
    unsigned size = sizeof(Impl) + length + 1;
    
    Impl* pImpl = (Impl*) osalHeapAlloc(nullptr, size);
    pImpl->length = length;
    pImpl->p = (char*)pImpl + sizeof(Impl);

    strcpy_s(pImpl->p, length + 1, cstr);

    return PImpl(pImpl);
}


unsigned StringV2::getLength() const {

    return _pImpl->length;
}


StringV2& StringV2::operator = (
    const char* cstr) {

    _pImpl = allocate(cstr);

    return *this;
}


StringV2& StringV2::operator = (
    const StringV2& str) {

    _pImpl = str._pImpl;

    return *this;
}


StringV2::operator const char* () const {

    return _pImpl->p;
}


char StringV2:: operator [] (unsigned index) const {

    return _pImpl->p[index];
}



bool StringV2::isEmpty() const {

    return (_pImpl->p == nullptr) || (_pImpl->length == 0);
}


bool StringV2::isNull() const {

    return _pImpl->p == nullptr;
}

