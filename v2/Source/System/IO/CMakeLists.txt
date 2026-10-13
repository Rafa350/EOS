target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
        FILES
            stream.cpp
            stream_serial.cpp
            stream_memory.cpp
            #stream_file.cpp
            eosFormatterText.cpp
            eosFormatterBinary.cpp
            eosParser.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        eosFormatterBinary_Reader.cpp
        eosFormatterBinary_Writer.cpp
        eosFormatterText_Writer.cpp
)
