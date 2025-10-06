cmake_minimum_required(VERSION 4.0)


list(APPEND SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/eosDigInputService.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosLedService.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosDigOutputService.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosService.cpp
)


target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
	${SOURCES}
)	