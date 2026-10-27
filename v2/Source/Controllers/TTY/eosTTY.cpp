export module Eos.Controllers.TTY;

import Eos.System.IO.Streams;
import Eos.System.IO.Formatters.Text;
import Eos.Types;


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
			UInt8 const _numRows;
			UInt8 const _numColumns;
			UInt8 _row;
			UInt8 _column;
			// UInt16 _buffer[]
			// UInt16 *_localBuffer;
			// UInt16 *_remoteBuffer;

		public:
			TTY(Stream *stream, UInt8 numRows, UInt8 nulColumns);

			void writeText(const char *s);
			void writeText(Color color, const char *s);
			void writeFormatedText(const char *fmt, ...);
			void writeFormatedText(Color color, const char *fmt, ...);
			void writeChar(char c);
			void writeChar(char c, UInt32 count);
			void writeNewLine();
			void writeU8(UInt8 value);
			void writeU16(UInt16 value);
			void writeU32(UInt32 value);
			void writeU8Hex(UInt8 value);
			void writeU16Hex(UInt16 value);
			void writeU32Hex(UInt32 value);
			void writeI8(Int8 value);
			void writeI16(Int16 value);
			void writeI32(Int32 value);

			UInt32 read(char *buffer, UInt32 bufferSize);

			void cursorShow();
			void cursorHide();
			void cursorAdvance();
			void cursorHome();
     		void cursorTo(UInt8 row, UInt8 column);
			void cursorLeft(UInt8 columns = 1);
			void cursorRight(UInt8 columns = 1);
			void cursorUp(UInt8 rows = 1);
			void cursorDown(UInt8 rows = 1);

			void clear();
			void clearRow();
			void clearRowEnd();

			void refresh();

			void resetTextColor();
			void setTextColor(Color color, bool hi = false);
			void setBackgroundColor(Color color, bool hi = false);
	};
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Contructor.
/// @param    stream: El stream.
/// @param    numRows: Nombre de fileres.
/// @param    numColumns: Nombre de columnes.
///
TTY::TTY(
	Stream *stream,
	UInt8 numRows,
	UInt8 numColumns) :

	_stream {stream},
	_writer {stream},
	_numRows {numRows},
	_numColumns {numColumns},
	_row {0},
	_column {0} {
}


/// ----------------------------------------------------------------------
/// @brief    Escriu una cadena de text.
/// @param    s: El text.
///
void TTY::writeText(
	const char *s) {

	_writer.writeString(s);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu una cadena de text.
/// @param    color: Color del text.
/// @param    s: El text.
///
void TTY::writeText(
	Color color,
	const char *s) {

	setTextColor(color);
	_writer.writeString(s);
	resetTextColor();
}


/// ----------------------------------------------------------------------
/// @brief    Escriu una cadena de text formatejat
/// @param    fmt: La cadena de format.
///
void TTY::writeFormatedText(
	const char *fmt,
	...) {

}


/// ----------------------------------------------------------------------
/// @brief    Escriu un salt de linia.
///
void TTY::writeNewLine() {

	_writer.writeString("\r\n");

	_row++;
	_column = 0;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu una caracter
/// @param    c: El caracter
///
void TTY::writeChar(
	char c) {

	_writer.writeChar(c);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu una caracter
/// @param    c: El caracter.
/// @param    count: El nombre de repeticions.
///
void TTY::writeChar(
	char c,
	UInt32 count) {

	while (count--)
		_writer.writeChar(c);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 8 bits en hexadecimal.
/// @param    value: El valor.
///
void TTY::writeU8Hex(
	UInt8 value) {

	_writer.writeU8Hex(value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 16 bits en hexadecimal.
/// @param    value: El valor.
///
void TTY::writeU16Hex(
	UInt16 value) {

	_writer.writeU16Hex(value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 32 bits en hexadevimal.
/// @param    value: El valor.
///
void TTY::writeU32Hex(
	UInt32 value) {

	_writer.writeU32Hex(value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 8 bits.
/// @param    value: El valor.
///
void TTY::writeU8(
	UInt8 value) {

	_writer.writeU8(value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 18 bits.
/// @param    value: El valor.
///
void TTY::writeU16(
	UInt16 value) {

	_writer.writeU16(value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor numeric de 32 bits.
/// @param    value: El valor.
///
void TTY::writeU32(
	UInt32 value) {

	_writer.writeU32(value);
}


/// ----------------------------------------------------------------------
/// @brief    Llegeix la entrada del terminal.
/// @param    buffer: El buffer de recepcio.
/// @param    bufferSize: El tamany del buffer en bytes.
/// @return   El nombre de bytes lleigits.
///
UInt32 eos::TTY::read(
	char *buffer,
	UInt32 bufferSize) {

	auto readResult = _stream->read((UInt8 *)buffer, bufferSize);
	if (readResult.isOk())
		return readResult.getValue();
	else
		return 0;
}


/// ----------------------------------------------------------------------
/// @brief    Mostra el cursor.
///
void TTY::cursorShow() {

	_writer.writeString("\x1B[?25h");
}


/// ----------------------------------------------------------------------
/// @brief    Oculta el cursor.
///
void TTY::cursorHide() {

	_writer.writeString("\x1B[?25l");
}


/// ----------------------------------------------------------------------
/// @brief    Avança el cursor a la seguent posicio.
///
void TTY::cursorAdvance() {

	_column += 1;
	if (_column == _numColumns) {
		_column = 0;
		_row += 1;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Mou el cursor al origen.
///
void TTY::cursorHome() {

	_column = 0;
	_row = 0;

	_writer.writeString("\x1B[H");
}


/// ----------------------------------------------------------------------
/// @brief    Mou el cursor a la posicio especificada.
/// @param    row: La fila.
/// @param    column: La columna.
///
void TTY::cursorTo(
	UInt8 row,
	UInt8 column) {

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
/// @brief     Mou el cursor cap a l'esquerra
/// @param     columns: El nombre de columnes a moure.
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void TTY::cursorLeft(
	UInt8 columns) {

	if ((columns > 0) && (columns < _column)) {

		_column -= columns;

		_writer.writeString("\x1B[");
		_writer.writeU8(columns);
		_writer.writeChar('D');
	}
}


/// ----------------------------------------------------------------------
/// @brief     Mou el cursor cap a la dreta
/// @brief     columns: El nombre de columnes a moure.
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void TTY::cursorRight(
	UInt8 columns) {

	if ((columns > 0) && ((columns + _column) < _numColumns)) {

		_column += columns;

		_writer.writeString("\x1B[");
		_writer.writeU8(columns);
		_writer.writeChar('C');
	}
}


/// ----------------------------------------------------------------------
/// @brief     Mou el cursor cap a munt
/// @brief     rows: El nombre de fileres
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void TTY::cursorUp(
	UInt8 rows) {

	if ((rows > 0) && (rows < _row)) {

		_row -= rows;

		_writer.writeString("\x1B[");
		_writer.writeU8(rows);
		_writer.writeChar('A');
	}
}


/// ----------------------------------------------------------------------
/// @brief     Mou el cursor cap a vall.
/// @brief     rows: El nombre de fileres
/// \remarks   Si no hi ha espai per moures, no fa res.
///
void TTY::cursorDown(
	UInt8 rows) {

	if ((rows > 0) && ((rows + _row) < _numRows)) {

		_row += rows;

		_writer.writeString("\x1B[");
		_writer.writeU8(rows);
		_writer.writeChar('B');
	}
}


/// ----------------------------------------------------------------------
/// @brief    Borra la pantalla complerta.
///
void TTY::clear() {

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
/// @brief    Borra desde la posicio del cursor fins al final de la linia.
///
void TTY::clearRowEnd() {

	_writer.writeString("\x1B[K");
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona els color per defecte del text.
///
void TTY::resetTextColor() {

	_writer.writeString("\x1B[0m");
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona els color del text
/// @param    color: El color.
/// @param    hi: Indica color d'alta intensitat
///
void TTY::setTextColor(
	Color color,
	bool hi) {

	_writer.writeString("\x1B[");
	if (hi)
		_writer.writeString("1;");
	_writer.writeU8(30 + ((UInt8) color));
	_writer.writeChar('m');
}


/// ----------------------------------------------------------------------
/// @brief    Selecciona els color del fons.
/// @param    color: El color.
/// @param    hi: Indica color d'alta intensitat
///
void TTY::setBackgroundColor(
	Color color,
	bool hi) {

	_writer.writeString("\x1B[");
	if (hi)
		_writer.writeString("1;");
	_writer.writeU8(40 + ((UInt8) color));
	_writer.writeChar('m');
}


/// ----------------------------------------------------------------------
/// @brief    Refresca els canvis en el terminal.
///
void TTY::refresh() {

	cursorHide();

	cursorShow();
}
