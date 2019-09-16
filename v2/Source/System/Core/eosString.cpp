#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "System/Core/eosString.h"
#include <string.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
///
String::String():
	length(0),
	containerSize(0),
	container(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief Contructor copia de l'objecte.
/// \param text: L'objecte a copiar.
///
String::String(
	const String& text):

	length(0),
	containerSize(0),
	container(nullptr) {

	alloc(text.container);
}


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param text: El text de la cadena.
/// \remarks Optimitzat per no utilitzar memoria del heap.
///
String::String(
	const char *text):

	length(strlen(text)),
	containerSize(0),
	container((char*)text) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
String::~String() {

	if ((containerSize > 0) && (container != nullptr))
		osalHeapFree(NULL, container);
}


/// ----------------------------------------------------------------------
/// \brief Operador d'asignacio.
/// \param text: El text a asignar.
///
String& String::operator = (
	const char *text) {

	alloc(text);
	return *this;
}


/// ----------------------------------------------------------------------
/// \brief Operador d'asignacio.
/// \param other: El text a asignar.
///
String& String::operator = (
	const String &text) {

	alloc(text.container);
	return *this;
}


/// ----------------------------------------------------------------------
/// \brief Operator ==
/// \param text: El text amb que comparar.
///
bool String::operator ==(
	const String &text) const {

	if (length != text.length)
		return false;
	else
		return compare(text) == 0;
}


int String::compare(
	const String &text) const {

	return strcmp(container, text.container);
}


int String::compare(
	const char *text) const {

	return strcmp(container, text);
}


/// ----------------------------------------------------------------------
/// \brief Asigna el text al contenidor.
/// \param text: El text.
///
void String::alloc(
	const char *text) {

	if (text != nullptr) {

		unsigned textLength = strlen(text);
		if (textLength >= containerSize) {

			unsigned newContainerSize = textLength + 1;

			char *newContainer = (char*) osalHeapAlloc(NULL, newContainerSize);
			if ((container != nullptr) && (containerSize > 0))
				osalHeapFree(NULL, container);

			containerSize = newContainerSize;
			container = newContainer;
		}
		strcpy(container, text);
		length = textLength;
	}
}
