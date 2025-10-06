cmake_minimum_required(VERSION 4.0)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
	${SOURCES}
)
