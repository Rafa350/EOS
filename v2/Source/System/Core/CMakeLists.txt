cmake_minimum_required(VERSION 4.0)

list(APPEND SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/eosErrorHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGlobalAlloc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosHeapAllocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosMutex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosPoolAllocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosQueue.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosSemaphore.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosTask.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosTimer.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
	${SOURCES}
)	