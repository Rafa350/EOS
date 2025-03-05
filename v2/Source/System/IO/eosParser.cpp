#include "eos.h"
#include "System/IO/eosParser.h"


using namespace eos;


static bool isDigit(char ch);
static bool isHexDigit(char ch);
static bool isSpace(char ch);
static bool isAscii(char ch);


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    stream: Stream d'entrada.
///
Parser::Parser(
	Stream * stream) :
	_stream {stream},
	_ungetCh {'\xFF'} {

}


/// ----------------------------------------------------------------------
/// \brief    Obte el seguent caracter del stream.
/// \return   El caracter. 0xFF en cas d'error.
///
///
char Parser::get() {

	char ch = _ungetCh;

	if (ch == '\xFF') {
		auto readResult = _stream->read((uint8_t*)&ch, sizeof(char));
		ch = (readResult.isSuccess() && (readResult == sizeof(char))) ? ch : '\xFF';
	}
	else
		_ungetCh = '\xFF';

	return ch;
}


/// ----------------------------------------------------------------------
/// \brief    Retorna el caracter al stream.
/// \param    ch: El caracter.
///
void Parser::unget(
	char ch) {

	_ungetCh = ch;
}


/// ----------------------------------------------------------------------
/// \brief    Analitza i retorna un uint32_t
/// \param    value: El valor analitzat. Nomes es valis si retorna true.
/// \return   True si tot es correcte. False en cas contrari.

bool Parser::parseU32(
	uint32_t &value) {

	unsigned state = 0;
	bool done = false;
	bool result = false;

	while (!done) {

		char ch = get();

		switch (state) {
			case 0:
				if (isDigit(ch)) {
					value = ch - 0x30;
					state = 1;
				}
				else if (!isSpace(ch)) {
					unget(ch);
					done = true;
				}
				break;

			case 1:
				if (isDigit(ch))
					value = (value * 10) + (ch - 0x30);
				else {
					unget(ch);
					result = true;
					done = true;
				}
				break;
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Analitza i obte un char.
/// \param    value: El valor analitzat. Nomes es valid si retorna true.
/// \return   True si tot es correcte.
///
bool Parser::parseChar(
	char &value) {

	value = get();

	return isAscii(value);
}


static bool isDigit(
	char ch) {

	return (ch >= '0') && (ch <= '9');
}


static bool isHexDigit(
	char ch) {

	return ((ch >= '0') && (ch <= '9')) ||
	       ((ch >= 'a') && (ch <= 'f')) ||
	       ((ch >= 'A') && (ch <= 'F'));
}


static bool isSpace(
	char ch) {

	return ch == ' ';
}


static bool isAscii(char ch) {

	return ch <= 0x7F;
}
