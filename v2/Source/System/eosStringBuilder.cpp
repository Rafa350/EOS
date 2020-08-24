#include "eos.h"
#include "System/eosString.h"
#include "System/Collections/eosContainer.h"

#include <string.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
//
StringBuilder::StringBuilder():
	container(nullptr),
	size(0),
	capacity(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
StringBuilder::~StringBuilder() {

	if (container != nullptr)
		Container::free(container);
}


/// ----------------------------------------------------------------------
/// \brief    Reserva memoria.
/// \param    newCapacity: La nova capacitat de memoria a reservar.
///
void StringBuilder::reserve(
	unsigned newCapacity) {

	container = static_cast<char*>(Container::resize(container, capacity, newCapacity, size, sizeof(char)));
	capacity = newCapacity;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un caracter.
/// \param    value: El caracter a afeigir.
///
void StringBuilder::append(
	char value) {

	if (size + sizeof(char) >= capacity)
		reserve(capacity + sizeof(char) + 10);

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
		reserve(capacity + length + 10);

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

}
