cmake_minimum_required(VERSION 4.0)

add_subdirectory("Core")
add_subdirectory("Graphics")
add_subdirectory("IO")


target_sources(${CMAKE_PROJECT_NAME} PUBLIC FILE_SET system_fileset TYPE CXX_MODULES FILES
	${CMAKE_CURRENT_SOURCE_DIR}/eosApplicationBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosDebug.cpp	
	${CMAKE_CURRENT_SOURCE_DIR}/eosRTOSApplication.cpp	
)	