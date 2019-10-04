#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "System/Core/eosString.h"
#include <string.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte. Crea una string buida.
///
String::String():

	pData(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Contructor copia de l'objecte.
/// \param    str: La string a copiar.
///
String::String(
	const String& str):

	pData(nullptr) {

	if (!str.isNull())
		reference(str);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    cstr: La string a copiar.
///
String::String(
	const char *cstr):

	pData(nullptr) {

	if (cstr != nullptr)
		create(cstr, 0, strlen(cstr));
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
String::~String() {

	if (pData != nullptr)
		release();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la longitut.
/// \return   La longitut en bytes.
///
unsigned String::getLength() const {

	return pData == nullptr ? 0 : pData->length;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la string es buida.
/// \return   True si es buida.
///
bool String::isEmpty() const {

	return (pData == nullptr) || (pData->length == 0);
}


/// ---------------------------------------------------------------------
/// \brief    Comprova si la string es nula.
/// \return   True si es nula.
///
bool String::isNull() const {

	return pData == nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    cstr: La string a asignar.
///
String& String::operator = (
	const char *cstr) {

	if (pData != nullptr)
		release();

	if (cstr != nullptr)
		create(cstr, 0, strlen(cstr));

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    str: La string a asignar.
///
String& String::operator = (
	const String &str) {

	if (pData != nullptr)
		release();

	if (!str.isNull())
		reference(str);

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operator ==
/// \param    str: El text amb que comparar.
///
bool String::operator ==(
	const String &str) const {

	// Si les dues string son buides, aleshores son iguals
	//
	if ((pData == nullptr) && (str.pData == nullptr))
		return true;

	// Si les dues string tenen el mateix bloc de dades, aleshores son iguals.
	//
	else if (pData == str.pData)
		return true;

	// Si les longituts no coincideixen, aleshores son diferents.
	//
	else if (pData->length != str.pData->length)
		return false;

	// Si arriba aqui compara les dues string caracter a caracter.
	//
	else
		return strcmp(pData->container, str.pData->container) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador []
/// \param    index: Index del caracter.
/// \return   El caracter en el index especificat.
///
char String::operator[](
	int index) const {

	if ((pData == nullptr) || ((unsigned) index >= pData->length))
		return 0;
	else
		return pData->container[index];
}


/// ----------------------------------------------------------------------
/// \brief    Crea un bloc de dades desde una string C.
/// \param    cstr: La string inicial.
/// \param    index: El primer caracter a copiar.
/// \param    length: El numero de caracters a copiar.
///
void String::create(
	const char *cstr,
	unsigned index,
	unsigned length) {

	eosAssert(pData == nullptr);

	unsigned size = sizeof(StringData) + length;
	pData = (StringData*) osalHeapAlloc(NULL, size);

	pData->length = length;
	pData->refCount = 1;
	strcpy(pData->container, cstr);
}


/// ----------------------------------------------------------------------
/// \brief    Referencia un bloc de dades d'un altre string.
/// \param    str: La string a referenciar.
///
void String::reference(
	const String &str) {

	eosAssert(pData == nullptr);
	eosAssert(str.pData != nullptr);

	str.pData->refCount++;

	pData = str.pData;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina el bloc de dades. Decrementa el contador de
///           referencies del bloc i si arriba a zero, aleshores destrueix
///           el bloc.
///
void String::release() {

	eosAssert(pData != nullptr);

	if (pData->refCount-- == 1)
		osalHeapFree(NULL, pData);
	pData = nullptr;
}
