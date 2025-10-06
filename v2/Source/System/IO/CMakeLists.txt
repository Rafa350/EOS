cmake_minimum_required(VERSION 4.0)

list(APPEND SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/eosBinaryStreamReader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosBinaryStreamWriter.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/eosDirectory.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/eosFile.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/eosFileStream.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/eosFileSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosMemoryStream.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosParser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosSerialStream.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosTextStreamWriter.cpp
)	

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
	${SOURCES}
)
