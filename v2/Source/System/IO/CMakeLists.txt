target_sources(${TARGET_NAME} PUBLIC 
	eosBinaryStreamReader.cpp
	eosBinaryStreamWriter.cpp
#	eosDirectory.cpp
#	eosFile.cpp
#	eosFileStream.cpp
#	eosFileSystem.cpp
	eosParser.cpp
	eosSerialStream.cpp
	eosTextStreamWriter.cpp
)

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    eosMeoryStream.cpp)