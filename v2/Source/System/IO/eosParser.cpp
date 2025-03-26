#include "eos.h"
#include "System/IO/eosParser.h"


using namespace eos;


constexpr char EOT = '\xFF';


static bool isDigit(char ch);
static bool isHexDigit(char ch);
static bool isSpace(char ch);
static bool isAscii(char ch);
static bool isTrue(char ch);
static bool isFalse(char ch);
static bool isEOT(char ch);


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    stream: Stream d'entrada.
///
Parser::Parser(
	Stream * stream) :
	_stream {stream},
	_ungetCh {EOT},
	_finished {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Obte el seguent caracter del stream.
/// \return   El caracter. 0xFF en cas d'error.
///
///
char Parser::get() {

	char ch = _ungetCh;

	if (ch == EOT) {
		auto readResult = _stream->read((uint8_t*)&ch, sizeof(char));
		ch = (readResult.isSuccess() && (readResult == sizeof(char))) ? ch : EOT;
	}
	else
		_ungetCh = EOT;

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
/// \param    value: El valor analitzat. Nomes es valid si retorna true.
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
				if (isEOT(ch)) {
					_finished = true;
					done = true;
				}
				else if (isDigit(ch)) {
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
					if (isEOT(ch))
						_finished = true;
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

	bool done = false;
	bool result = false;

	while (!done) {

		char ch = get();

		if (isEOT(ch)) {
			_finished = true;
			done = true;
		}

		else if (isAscii(ch)) {
			value = ch;
			done = true;
		}

		else if (!isSpace(ch)) {
			if (isEOT(ch))
				_finished = true;
			unget(ch);
			done = true;
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Analitza i obte un bool.
/// \param    value: El valor analitzat. Nomes es valid si retorna true.
/// \return   True si tot es correcte.
///
bool Parser::parseBool(
	bool &value) {

	bool done = false;
	bool result = false;

	while (!done) {

		char ch = get();

		if (isEOT(ch)) {
			_finished = true;
			done = true;
		}
		else if (isTrue(ch)) {
			value = true;
			result = true;
			done = true;

		}
		else if (isFalse(ch)) {
			value = false;
			result = true;
			done = true;

		}
		else if (!isSpace(ch)) {
			if (isEOT(ch))
				_finished = true;
			unget(ch);
			done = true;
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un digit decimal.
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isDigit(
	char ch) {

	return (ch >= '0') && (ch <= '9');
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un digit hexadecimal.
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isHexDigit(
	char ch) {

	return ((ch >= '0') && (ch <= '9')) ||
	       ((ch >= 'a') && (ch <= 'f')) ||
	       ((ch >= 'A') && (ch <= 'F'));
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un espai.
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isSpace(
	char ch) {

	return (ch == ' ') || (ch == '\t');
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un caracter ascii
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isAscii(
	char ch) {

	return ch <= 0x7F;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un carascter TRUE
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isTrue(
	char ch) {

	return
		(ch == '1') ||
		(ch == 'Y') || (ch == 'y') ||
		(ch == 'T') || (ch == 't');
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un caracter FALSE
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isFalse(
	char ch) {

	return
		(ch == '0') ||
		(ch == 'N') || (ch == 'n') ||
		(ch == 'F') || (ch == 'f');
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es un indicador de fi de text.
/// \param    ch: El caracter a verificar.
/// \return   El resultat de la comprovacio.
///
static bool isEOT(
	char ch) {

	return ch == EOT;
}
