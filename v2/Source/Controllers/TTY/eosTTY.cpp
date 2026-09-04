module;


#include "eos.h"


export module Eos.Controllers.TTY;


import Eos.System.IO.Streams;
import Eos.System.IO.Formatters.Text;


export namespace eos {

	class TTY final {
		public :
			enum class Color {
				black,
				red,
				green,
				yellow,
				blue,
				magenta,
				cyan,
				white
			};

		private:
			Stream * const _stream;
			TextWriter _writer;
			uint8_t const _numRows;
			uint8_t const _numColumns;
			uint8_t _row;
			uint8_t _column;
			// uint16_t _buffer[]
			// uint16_t *_localBuffer;
			// uint16_t *_remoteBuffer;

		public:
			TTY(Stream *stream, uint8_t numRows, uint8_t nulColumns);

			void writeText(const char *s);
			void writeFormatedText(const char *fmt, ...);
			void writeChar(char c);
			void writeChar(char c, uint32_t count);
			void writeNewLine();
			void writeU8(uint8_t value);
			void writeU16(uint16_t value);
			void writeU32(uint32_t value);
			void writeU8Hex(uint8_t value);
			void writeU16Hex(uint16_t value);
			void writeU32Hex(uint32_t value);
			void writeI8(int8_t value);
			void writeI16(int16_t value);
			void writeI32(int32_t value);

			uint32_t read(char *buffer, uint32_t bufferSize);

			void cursorShow();
			void cursorHide();
			void cursorAdvance();
			void cursorHome();
     		void cursorTo(uint8_t row, uint8_t column);
			void cursorLeft(uint8_t columns = 1);
			void cursorRight(uint8_t columns = 1);
			void cursorUp(uint8_t rows = 1);
			void cursorDown(uint8_t rows = 1);

			void clear();
			void clearRow();
			void clearRowEnd();

			void refresh();

			void setDefaultColor();
			void setTextColor(Color color, bool hi = false);
			void setBackgroundColor(Color color, bool hi = false);
	};
}


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    stream: El stream.
/// \param    numRows: Nombre de fileres.
/// \para     numColumns: Nombre de columnes.
///
eos::TTY::TTY(
	Stream *stream,
	uint8_t numRows,
	uint8_t numColumns) :

	_stream {stream},
	_writer {stream},
	_numRows {numRows},
	_numColumns {numColumns},
	_row {0},
	_column {0} {
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una cadena de text.
/// \param    s: El text.
///
void eos::TTY::writeText(
	const char *s) {

	_writer.writeString(s);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una cadena de text formatejat
/// \param    fmt: La cadena de format.
///
void eos::TTY::writeFormatedText(
	const char *fmt,
	...) {

}


/// ----------------------------------------------------------------------
/// \brief    Escriu un salt de linia.
///
void eos::TTY::writeNewLine() {

	_writer.writeString("\r\n");

	_row++;
	_column = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una caracter
/// \param    c: El caracter
///
void eos::TTY::writeChar(
	char c) {

	_writer.writeChar(c);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una caracter
/// \param    c: El caracter.
/// \param    count: El nombre de repeticions.
///
void eos::TTY::writeChar(
	char c,
	uint32_t count) {

	while (count--)
		_writer.writeChar(c);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor numeric de 16 bits en hexadecimal.
/// \param    value: El valor.
///
void eos::TTY::writeU16Hex(
	uint16_t value) {

	_writer.writeU16Hex(value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor numeric de 32 bits en hexadevimal.
/// \param    value: El valor.
///
void eos::TTY::writeU32Hex(
	uint32_t value) {

	_writer.writeU32Hex(value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor numeric de 8 bits.
/// \param    value: El valor.
///
void eos::TTY::writeU8(
	uint8_t value) {

	_writer.writeU8(value);
}

/// ----------------------------------------------------------------------
/// \brief    Escriu un valor numeric de 18 bits.
/// \param    value: El valor.
///
void eos::TTY::writeU16(
	uint16_t value) {

	_writer.writeU16(value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor numeric de 32 bits.
/// \param    value: El valor.
///
void eos::TTY::writeU32(
	uint32_t value) {

	_writer.writeU32(value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix la entrada del terminal.
/// \param    buffer: El buffer de recepcio.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El nombre de bytes lleigits.
///
uint32_t eos::TTY::read(
	char *buffer,
	uint32_t bufferSize) {

	auto readResult = _stream->read((uint8_t *)buffer, bufferSize);
	if (readResult.isSuccess())
		return readResult.value();
	else
		return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Mostra el cursor.
///
void eos::TTY::cursorShow() {

	_writer.writeString("\x1B[?25h");
}


/// ----------------------------------------------------------------------
/// \brief    Oculta el cursor.
///
void eos::TTY::cursorHide() {

	_writer.writeString("\x1B[?25l");
}


/// ----------------------------------------------------------------------
/// \brief    Avança el cursor a la seguent posicio.
///
void eos::TTY::cursorAdvance() {

	_column += 1;
	if (_column == _numColumns) {
		_column = 0;
		_row += 1;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Mou el cursor al origen.
///
void eos::TTY::cursorHome() {

	_column = 0;
	_row = 0;

	_writer.writeString("\x1B[H");
}


/// ----------------------------------------------------------------------
/// \brief    Mou el cursor a la posicio especificada.
/// \param    row: La fila.
/// \param    column: La columna.
///
void eos::TTY::cursorTo(
	uint8_t row,
	uint8_t column) {

	if ((row < _numRows) && (column < _numColumns)) {

		_row = row;
		_column = column;

		_writer.writeString("\x1B[");
		_writer.writeU8(row + 1);
		_writer.writeChar(';');
		_writer.writeU8(column + 1);
		_writer.writeChar('H');
	}
}


/// ----------------------------------------------------------------------
/// \brief     Mou el cursor cap a l'esquerra
/// \param     columns: El nombre de columnes a moure.
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void eos::TTY::cursorLeft(
	uint8_t columns) {

	if ((columns > 0) && (columns < _column)) {

		_column -= columns;

		_writer.writeString("\x1B[");
		_writer.writeU8(columns);
		_writer.writeChar('D');
	}
}


/// ----------------------------------------------------------------------
/// \brief     Mou el cursor cap a la dreta
/// \brief     columns: El nombre de columnes a moure.
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void eos::TTY::cursorRight(
	uint8_t columns) {

	if ((columns > 0) && ((columns + _column) < _numColumns)) {

		_column += columns;

		_writer.writeString("\x1B[");
		_writer.writeU8(columns);
		_writer.writeChar('C');
	}
}


/// ----------------------------------------------------------------------
/// \brief     Mou el cursor cap a munt
/// \brief     rows: El nombre de fileres
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void eos::TTY::cursorUp(
	uint8_t rows) {

	if ((rows > 0) && (rows < _row)) {

		_row -= rows;

		_writer.writeString("\x1B[");
		_writer.writeU8(rows);
		_writer.writeChar('A');
	}
}


/// ----------------------------------------------------------------------
/// \brief     Mou el cursor cap a vall.
/// \brief     rows: El nombre de fileres
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void eos::TTY::cursorDown(
	uint8_t rows) {

	if ((rows > 0) && ((rows + _row) < _numRows)) {

		_row += rows;

		_writer.writeString("\x1B[");
		_writer.writeU8(rows);
		_writer.writeChar('B');
	}
}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla complerta.
///
void eos::TTY::clear() {

	_column = 0;
	_row = 0;

	_writer.writeString("\x1B[8;");
	_writer.writeU8(_numRows);
	_writer.writeChar(';');
	_writer.writeU8(_numColumns);
	_writer.writeChar('t');

	_writer.writeString("\x1B[H\x1B[2J");
}


/// ----------------------------------------------------------------------
/// \brief    Borra desde la posicio del cursor fins al final de la linia.
///
void eos::TTY::clearRowEnd() {

	_writer.writeString("\x1B[K");
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona els color per defecte
///
void eos::TTY::setDefaultColor() {

	_writer.writeString("\x1B[0m");
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona els color del text
/// \param    color: El color.
/// \param    hi: Indica color d'alta intensitat
///
void eos::TTY::setTextColor(
	Color color,
	bool hi) {

	_writer.writeString("\x1B[");
	if (hi)
		_writer.writeString("1;");
	_writer.writeU8(30 + ((uint8_t) color));
	_writer.writeChar('m');
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona els color del fons.
/// \param    color: El color.
/// \param    hi: Indica color d'alta intensitat
///
void eos::TTY::setBackgroundColor(
	Color color,
	bool hi) {

	_writer.writeString("\x1B[");
	if (hi)
		_writer.writeString("1;");
	_writer.writeU8(40 + ((uint8_t) color));
	_writer.writeChar('m');
}


/// ----------------------------------------------------------------------
/// \brief    Refresca els canvis en el terminal.
///
void eos::TTY::refresh() {

	cursorHide();

	cursorShow();
}
