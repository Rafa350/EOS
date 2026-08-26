#pragma once


#include "eos.h"
#include "System/IO/eosTextStreamWriter.h"


namespace eos {

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
			TextStreamWriter _writer;
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
