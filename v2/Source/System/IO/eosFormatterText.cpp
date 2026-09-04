module;


#include "eos.h"


export module Eos.System.IO.Formatters.Text;


export import Eos.System.IO.Streams;


export namespace eos {

    /// \brief Objecte per escriure en un stream.
    ///
    class TextWriter final {
      	public:
    	  	static constexpr const char *newLine = "\r\n";
    		  static constexpr char cr = '\r';
    		  static constexpr char lf = '\n';
    		  static constexpr char tab = '\t';

      private:
    		  Stream *_stream;

        public:
            TextWriter(Stream *stream);

            bool writeU8(uint8_t data);
            bool writeU16(uint16_t data);
            bool writeU32(uint32_t data);
            bool writeU8Hex(uint8_t data);
            bool writeU16Hex(uint16_t data);
            bool writeU32Hex(uint32_t data);
            bool writeI8(int8_t data);
            bool writeI16(int16_t data);
            bool writeI32(int32_t data);
            bool writeChar(char data);
            bool writeString(const char *data);
            bool writeBool(bool data);

            inline TextWriter& operator << (const uint8_t data) {

            	writeU8(data);
            	return *this;
            }

            inline TextWriter& operator << (const uint16_t data) {

            	writeU16(data);
            	return *this;
            }

            inline TextWriter& operator << (const uint32_t data) {

            	writeU32(data);
            	return *this;
            }

            inline TextWriter& operator << (const char data) {

            	writeChar(data);
            	return *this;
            }

            inline TextWriter& operator << (const char *data) {

            	writeString(data);
            	return *this;
            }
    };

}