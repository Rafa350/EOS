#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "System/eosMath.h"
#include "System/Core/eosString.h"
#include <string.h>


using namespace eos;


struct String::StringData {
	int refCount;                 // Contador de referencies.
	int length;                   // Longitut de la string.
	const char *ptr;              // Punter a la cadena.
};

static const char *nullStr = "";  // Cadena buida.


/// ----------------------------------------------------------------------
/// \brief    Comprova si apunte al area de ROM
/// \param 	  ptr: El punter
/// \return   True si es constant.
///
#ifdef EOS_STM32
static inline bool isRomPointer(
	const void *ptr) {

	extern char _stext2; // Declarada en el script del linker inici de la ROM
	extern char _etext2; // Declarada en el script del linker final de la ROM

	unsigned start = unsigned(&_stext2);
	unsigned end = unsigned(&_etext2);
	unsigned addr = unsigned(ptr);

	return (addr >= start) && (addr <= end);
}
#else
#define isRomPointer(a) (false)
#endif


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
/// \brief    Constructor. Crea la string a partir d'una part d'un altre.
/// \param    str: La string a copiar
/// \param    index: primer caracter a copiar.
/// \param    length: Numero de caracters a copiar.
///
String::String(
	const String &str,
	int index,
	int length):

	pData(nullptr) {

	if (!str.isNull())
		create(str, index, length);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    cstr: La string a copiar.
///
String::String(
	const char *cstr):

	pData(nullptr) {

	if (cstr != nullptr)
		create(cstr, 0, -1);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    cstr: La string a copiar.
/// \param    index: Caracter inicial a copiar.
/// \param    length: Numero de caracters a copiar.
///
String::String(
	const char *cstr,
	int index,
	int length):

	pData(nullptr) {

	if ((cstr != nullptr) && (length > 0))
		create(cstr, index, length);
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
int String::getLength() const {

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
/// \brief    Comprova si dues strings son iguals.
/// \param    cstr: La string a comparar.
/// \return   True si son iguals.
///
int String::isEqual(
	const char *cstr) const {

	if (pData == nullptr)
		return cstr == nullptr;
	else
		return strcmp(pData->ptr, cstr) == 0;
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
		create(cstr, 0, -1);

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
/// \param    str: La string a comparar.
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
		return strcmp(pData->ptr, str.pData->ptr) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador []
/// \param    index: Index del caracter.
/// \return   El caracter en el index especificat.
///
char String::operator[](
	int index) const {

	if ((pData == nullptr) || (index < 0) || (index >= pData->length))
		return 0;
	else
		return pData->ptr[index];
}


/// ----------------------------------------------------------------------
/// \brier    Operador const char *
///
String::operator const char*() const {

	return pData == nullptr ? nullStr : pData->ptr;
}


/// ----------------------------------------------------------------------
/// \brief    Crea un bloc de dades desde una string C.
/// \param    cstr: La string inicial.
/// \param    index: El primer caracter a copiar.
/// \param    length: El numero de caracters a copiar.
///
void String::create(
	const char *cstr,
	int index,
	int length) {

	eosAssert(pData == nullptr);
	eosAssert(index >= 0);
	eosAssert(length >= -1);

	int totalLength = strlen(cstr);
	if (length < 0)
		length = totalLength;
	length = Math::min(length - index, totalLength);

	if (isRomPointer(cstr) && (index == 0) && (length == totalLength)) {

		pData = (StringData*) osalHeapAlloc(nullptr, int(sizeof(StringData)));
		eosAssert(pData != nullptr);

		pData->ptr = cstr;
	}

	else {

		pData = (StringData*) osalHeapAlloc(nullptr, int(sizeof(StringData)) + length + 1);
		eosAssert(pData != nullptr);

		pData->ptr = (char*)pData + sizeof(StringData);
		strncpy((char*) pData->ptr, &cstr[index], length);
		((char*)pData->ptr)[length] = 0;
	}

	pData->length = length;
	pData->refCount = 1;
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
		osalHeapFree(nullptr, pData);
	pData = nullptr;
}
