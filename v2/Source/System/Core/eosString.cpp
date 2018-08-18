#include "System/Core/eosString.h"
#include "OSAL/osalMemory.h"

#include <string.h>



using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
String::String() {

	length = 0;
    container = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Contructor copia de l'objecte.
/// \param other: La string a copiar.
///
String::String(
	const String& other) {

	length = other.length;
	container = other.container;
}


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param text: El text de la cadena.
///
String::String(
	const char *text) {

	if (text == nullptr) {
		length = 0;
		container = nullptr;
	}
	else {
		length = strlen(text);
		container = (char*) osalMemoryAlloc(length + 1);
		memcpy(container, text, length + 1);
	}
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
String::~String() {

	if (container != nullptr)
		osalMemoryFree(container);
}
