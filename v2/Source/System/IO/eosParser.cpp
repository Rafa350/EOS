export module Eos.System.IO.Parser;


import Eos.System.IO.Streams;
import Eos.Types;


export namespace eos {

	class Parser final {
		private:
			static constexpr char EOT = '\xFF';

		private:
			Stream * const _stream;
			char _ungetCh;
			bool _finished;

		private:
			char get();
			void unget(char ch);

			static UInt8 DecValue(char ch);
			static UInt8 HexValue(char ch);

			static bool isDigit(char ch);
			static bool isHexDigit(char ch);
			static bool isSpace(char ch);
			static bool isAscii(char ch);
			static bool isTrue(char ch);
			static bool isFalse(char ch);
			static bool isEOT(char ch);

		public:
			Parser(Stream *stream);

			bool parseU8(UInt8 &value, bool hex = false);
			bool parseU16(UInt16 &value, bool hex = false);
			bool parseU32(UInt32 &value, bool hex = false);
			bool parseBool(bool &value);
			bool parseChar(char &value);
			bool isFinished() const { return _finished; }
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @param    stream: Stream d'entrada.
///
Parser::Parser(
	Stream * stream) :
	_stream {stream},
	_ungetCh {EOT},
	_finished {false} {

}


/// ---------------------------------------------------------------------------
/// @brief    Obte el seguent caracter del stream.
/// @return   El caracter. 0xFF en cas d'error.
///
///
char Parser::get() {

	char ch = _ungetCh;

	if (ch == EOT) {
		auto readResult = _stream->read((UInt8*)&ch, sizeof(char));
		ch = (readResult.isOk() && (readResult.getValue() == sizeof(char))) ? ch : EOT;
	}
	else
		_ungetCh = EOT;

	return ch;
}


/// ---------------------------------------------------------------------------
/// @brief    Retorna el caracter al stream.
/// @param    ch: El caracter.
///
void Parser::unget(
	char ch) {

	_ungetCh = ch;
}


/// ---------------------------------------------------------------------------
/// @brief    Analitza el text i retorna un valor UInt8
/// @param 	  value : El valor retornat. Nomes es valid si la funcio
///           retorna true
/// @param    hex: True si es vol en hexadecimal.
/// @return   True si tot es correcte.
///
bool Parser::parseU8(
	UInt8 &value,
	bool hex) {

	UInt32 v;
	if (parseU32(v, hex) && (v <= 0xFF)) {
		value = v;
		return true;
	}

	return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Analitza el text i retorna un valor UInt16
/// @param 	  value : El valor retornat. Nomes es valid si la funcio
///           retorna true
/// @param    hex: True si es vol en hexadecimal.
/// @return   True si tot es correcte.
///
bool Parser::parseU16(
	UInt16 &value,
	bool hex) {

	UInt32 v;
	if (parseU32(v, hex) && (v <= 0xFFFF)) {
		value = v;
		return true;
	}

	return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Analitza el text i retorna un valor UInt32
/// @param 	  value : El valor retornat. Nomes es valid si la funcio
///           retorna true
/// @param    hex: True si es vol en hexadecimal.
/// @return   True si tot es correcte.
///
bool Parser::parseU32(
	UInt32 &value,
    bool hex) {

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
				else if (hex && isHexDigit(ch)) {
					value = HexValue(ch);
					state = 1;
				}
				else if (!hex && isDigit(ch)) {
					value = DecValue(ch);
					state = 1;
				}
				else if (!isSpace(ch)) {
					unget(ch);
					done = true;
				}
				break;

			case 1:
				if (hex && isHexDigit(ch))
					value = (value * 16) + HexValue(ch);
				else if (!hex && isDigit(ch))
					value = (value * 10) + DecValue(ch);
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


/// ---------------------------------------------------------------------------
/// @brief    Analitza i obte un char.
/// @param    value: El valor analitzat. Nomes es valid si retorna true.
/// @return   True si tot es correcte.
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


/// ---------------------------------------------------------------------------
/// @brief    Analitza i obte un bool.
/// @param    value: El valor analitzat. Nomes es valid si retorna true.
/// @return   True si tot es correcte.
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


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un digit decimal.
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isDigit(
	char ch) {

	return (ch >= '0') && (ch <= '9');
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un digit hexadecimal.
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isHexDigit(
	char ch) {

	return ((ch >= '0') && (ch <= '9')) ||
	       ((ch >= 'a') && (ch <= 'f')) ||
	       ((ch >= 'A') && (ch <= 'F'));
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un espai.
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isSpace(
	char ch) {

	return (ch == ' ') || (ch == '\t');
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un caracter ascii
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isAscii(
	char ch) {

	return ch <= 0x7F;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un carascter TRUE
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isTrue(
	char ch) {

	return
		(ch == '1') ||
		(ch == 'Y') || (ch == 'y') ||
		(ch == 'T') || (ch == 't');
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un caracter FALSE
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isFalse(
	char ch) {

	return
		(ch == '0') ||
		(ch == 'N') || (ch == 'n') ||
		(ch == 'F') || (ch == 'f');
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si es un indicador de fi de text.
/// @param    ch: El caracter a verificar.
/// @return   El resultat de la comprovacio.
///
bool Parser::isEOT(
	char ch) {

	return ch == EOT;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el valor decimal d'un caracter.
/// @param    ch: El caracter.
/// @return   El seu valor decimal.
/// @remark   El caracter ha de ser un caracter decimal valid.
///
UInt8 Parser::DecValue(
	char ch) {

	return ch - 0x30;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el valor hexadecimal d'un caracter.
/// @param    ch: El caracter.
/// @return   El seu valor decimal.
/// @remark   El caracter ha de ser un caracter hexadecimal valid.
///
UInt8 Parser::HexValue(
	char ch) {

	return (ch < 0x39) ? ch - 0x30 : (ch & 0x20) - 0x37;
}
