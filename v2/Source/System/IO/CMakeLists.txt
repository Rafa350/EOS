target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        eosStreams.cpp
#        eosStreamsFile.cpp
        eosStreamsSerial.cpp
        eosStreamsMemory.cpp
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
