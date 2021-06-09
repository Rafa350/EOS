#include "eos.h"
#ifndef USE_STD_STRINGS

#include "eosAssert.h"
#include "HAL/halINT.h"
#include "OSAL/osalHeap.h"
#include "System/eosMath.h"
#include "System/eosString.h"


using namespace eos;


struct String::StringData {
	unsigned refCount;            // Contador de referencies.
	unsigned length;              // Longitut de la string.
	const char* ptr;              // Punter a la cadena.
};

static const char* nullStr = "";  // Cadena buida.


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

	_data(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Contructor copia de l'objecte.
/// \param    str: La string a copiar.
///
String::String(
	const String& str):

	_data(nullptr) {

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
	const String& str,
	unsigned index,
	unsigned length):

	_data(nullptr) {

	if (!str.isNull())
		create(str, index, length);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    cstr: La string a copiar.
///
String::String(
	const char* cstr):

	_data(nullptr) {

	if (cstr != nullptr)
		create(cstr, 0, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    cstr: La string a copiar.
/// \param    index: Caracter inicial a copiar.
/// \param    length: Numero de caracters a copiar.
///
String::String(
	const char* cstr,
	unsigned index,
	unsigned length):

	_data(nullptr) {

	if ((cstr != nullptr) && (length > 0))
		create(cstr, index, length);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
String::~String() {

	if (_data != nullptr)
		release();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la longitut.
/// \return   La longitut en bytes.
///
unsigned String::getLength() const {

	return _data == nullptr ? 0 : _data->length;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la string es buida.
/// \return   True si es buida.
///
bool String::isEmpty() const {

	return (_data == nullptr) || (_data->length == 0);
}


/// ---------------------------------------------------------------------
/// \brief    Comprova si la string es nula.
/// \return   True si es nula.
///
bool String::isNull() const {

	return _data == nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte el iterator.
///
String::Iterator String::begin() {

	return _data == nullptr ? nullptr : const_cast<char*>(_data->ptr);
}


/// ----------------------------------------------------------------------
/// \brief Obte el iterator.
///
String::CIterator String::begin() const {

	return _data == nullptr ? nullptr : _data->ptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte el iterator
///
String::Iterator String::end() {

	return _data == nullptr ? nullptr : const_cast<char*>(_data->ptr) + _data->length;
}


/// ----------------------------------------------------------------------
/// \brief Obte el iterator
///
String::CIterator String::end() const {

	return _data == nullptr ? nullptr : _data->ptr + _data->length;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si dues strings son iguals.
/// \param    cstr: La string a comparar.
/// \return   True si son iguals.
///
bool String::isEqual(
	const char* cstr) const {

	if (_data == nullptr)
		return cstr == nullptr;
	else
		return strcmp(_data->ptr, cstr) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Conmprova si dues strings son iguals.
/// \param    str: L'altre cadena a comparar.
/// \return   True si son iguals.
///
bool String::isEqual(
	const String& str) const {

	// Si les dues string son buides, aleshores son iguals
	//
	if ((_data == nullptr) && (str._data == nullptr))
		return true;

	// Si les dues string tenen el mateix bloc de dades, aleshores son iguals.
	//
	else if (_data == str._data)
		return true;

	// Si les longituts no coincideixen, aleshores son diferents.
	//
	else if (_data->length != str._data->length)
		return false;

	// Si arriba aqui compara les dues string caracter a caracter.
	//
	else
		return strcmp(_data->ptr, str._data->ptr) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    cstr: La string a asignar.
///
String& String::operator = (
	const char* cstr) {

	if (_data != nullptr)
		release();

	if (cstr != nullptr)
		create(cstr, 0, unsigned(-1));

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador d'asignacio.
/// \param    str: La string a asignar.
///
String& String::operator = (
	const String& str) {

	if (this != &str) {

		if (_data != nullptr)
			release();

		if (!str.isNull())
			reference(str);
	}

	return *this;
}


/// ----------------------------------------------------------------------
/// \brief    Operador []
/// \param    index: Index del caracter.
/// \return   El caracter en el index especificat.
///
char String::operator [] (
	unsigned index) const {

	if ((_data == nullptr) || (index >= _data->length))
		return 0;
	else
		return _data->ptr[index];
}


/// ----------------------------------------------------------------------
/// \brier    Operador const char *
///
String::operator const char* () const {

	return _data == nullptr ? nullStr : _data->ptr;
}


/// ----------------------------------------------------------------------
/// \brief    Crea un bloc de dades desde una string C.
/// \param    cstr: La string inicial.
/// \param    index: El primer caracter a copiar.
/// \param    length: El numero de caracters a copiar.
///
void String::create(
	const char* cstr,
	unsigned index,
	unsigned length) {

	eosAssert(_data == nullptr);

	unsigned totalLength = strlen(cstr);
	if (length == unsigned(-1))
		length = totalLength;
	length = Math::min(length - index, totalLength);

	if (isRomPointer(cstr) && (index == 0) && (length == totalLength)) {

		_data = static_cast<StringData*>(osalHeapAlloc(nullptr, sizeof(StringData)));
		eosAssert(_data != nullptr);

		_data->ptr = cstr;
	}

	else {

		_data = static_cast<StringData*>(osalHeapAlloc(nullptr, sizeof(StringData) + length + 1));
		eosAssert(_data != nullptr);

		_data->ptr = (char*)_data + sizeof(StringData);
		strncpy((char*) _data->ptr, &cstr[index], length);
		((char*)_data->ptr)[length] = 0;
	}

	_data->length = length;
	_data->refCount = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Referencia un bloc de dades d'un altre string.
/// \param    str: La string a referenciar.
///
void String::reference(
	const String& str) {

	eosAssert(_data == nullptr);
	eosAssert(str._data != nullptr);

	if (this != &str) {
		str._data->refCount++;
		_data = str._data;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Elimina el bloc de dades. Decrementa el contador de
///           referencies del bloc i si arriba a zero, aleshores destrueix
///           el bloc.
///
void String::release() {

	eosAssert(_data != nullptr);

	if (_data->refCount-- == 1)
		osalHeapFree(nullptr, _data);
	_data = nullptr;
}


#endif // USE_STD_STRINGS
