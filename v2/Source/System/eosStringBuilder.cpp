#include "eos.h"
#include "System/eosString.h"

#include <stdlib.h>
#include <string.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
//
StringBuilder::StringBuilder():
	_container(nullptr),
	_size(0),
	_capacity(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
StringBuilder::~StringBuilder() {

	if (_container != nullptr)
		osalHeapFree(nullptr, _container);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la nova capacitat.
/// \param    La nova capacitat necesaria.
/// \return   La nova capacitat a reservar.
///
int StringBuilder::calcNewCapacity(
	int requiredCapacity) const {

	if (requiredCapacity > _capacity) {
		int extra = (_capacity == 0) ? 16 :
				         ((_capacity < 128) ? 32 :
				          _capacity >> 2);
		return requiredCapacity + extra;
	}
	else
		return _capacity;
}


/// ----------------------------------------------------------------------
/// \brief    Reserva memoria.
/// \param    newCapacity: La nova capacitat de memoria a reservar.
///
void StringBuilder::reserve(
	int newCapacity) {

	if (newCapacity > _capacity) {
		char *newContainer = (char*) osalHeapAlloc(nullptr, newCapacity);
		if (_container != nullptr) {
			memcpy(newContainer, _container, _size);
			osalHeapFree(nullptr, _container);
			_container = newContainer;
		}
		_capacity = newCapacity;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut.
///
void StringBuilder::clear() {

	_size = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un caracter.
/// \param    value: El caracter a afeigir.
///
void StringBuilder::append(
	char value) {

	if (_size + (int)sizeof(char) >= _capacity)
		reserve(calcNewCapacity(_capacity + (int)sizeof(char)));

	_container[_size++] = value;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una string C.
/// \param    value: La string a afeigir.
///
void StringBuilder::append(
	const char* value) {

	int length = (int)strlen(value);
	if (_size + length >= _capacity)
		reserve(calcNewCapacity(_capacity + length));

	memcpy(&_container[_size], value, length);
	_size += length;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una string.
/// \param    value: La string a afeigir.
///
void StringBuilder::append(
	const String& value) {

	append((const char*) value);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un valor boolean.
/// \param    value: El valor a afeigir.
///
void StringBuilder::append(
	bool value) {

	static const char* strTrue = "true";
	static const char* strFalse = "false";

	append(value ? strTrue : strFalse);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un valor integer.
/// \param    value: El valor a afeigir.
///
void StringBuilder::append(
	int value) {

	char buffer[15];

	sprintf(buffer, "%i", value);
	append(buffer);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un valor unsigned.
/// \param    value: El valor a afeigir.
///
void StringBuilder::append(
	unsigned value) {

	char buffer[15];

	sprintf(buffer, "%u", value);
	append(buffer);
}

