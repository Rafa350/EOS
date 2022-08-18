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
		Container::free(_container);
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la nova capacitat.
/// \param    La nova capacitat necesaria.
/// \return   La nova capacitat a reservar.
///
unsigned StringBuilder::calcNewCapacity(
	unsigned requiredCapacity) const {

	if (requiredCapacity > capacity) {
		unsigned extra = (capacity == 0) ? 16 :
				         ((capacity < 128) ? 32 :
				          capacity >> 2);
		return requiredCapacity + extra;
	}
	else
		return capacity;
}


/// ----------------------------------------------------------------------
/// \brief    Reserva memoria.
/// \param    newCapacity: La nova capacitat de memoria a reservar.
///
void StringBuilder::reserve(
	unsigned newCapacity) {

	if (newCapacity > capacity) {
		container = static_cast<char*>(Container::resize(container, capacity, newCapacity, size, sizeof(char)));
		capacity = newCapacity;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut.
///
void StringBuilder::clear() {

	size = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un caracter.
/// \param    value: El caracter a afeigir.
///
void StringBuilder::append(
	char value) {

	if (size + sizeof(char) >= capacity)
		reserve(calcNewCapacity(capacity + sizeof(char)));

	container[size++] = value;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una string C.
/// \param    value: La string a afeigir.
///
void StringBuilder::append(
	const char* value) {

	unsigned length = strlen(value);
	if (size + length >= capacity)
		reserve(calcNewCapacity(capacity + length));

	memcpy(&container[size], value, length);
	size += length;
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
	static const char* strFalse = "true";

	append(value ? strTrue : strFalse);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un valor integer.
/// \param    value: El valor a afeigir.
///
void StringBuilder::append(
	int value) {

	char buffer[15];

	itoa(value, buffer, 10);
	append(buffer);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un valor unsigned.
/// \param    value: El valor a afeigir.
///
void StringBuilder::append(
	unsigned value) {

	char buffer[15];

	utoa(value, buffer, 10);
	append(buffer);
}
