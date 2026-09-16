target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
		eosCore.cpp
		eosPoolAllocator.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
		eosErrorHandler.cpp
		eosGlobalAlloc.cpp
)

if(EOS_RTOS_NAME MATCHES "FreeRTOS")
	add_subdirectory("FreeRTOS")
endif()
