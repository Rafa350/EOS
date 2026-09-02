target_sources(${TARGET_NAME} 
    PUBLIC 
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
			eosApplication.cpp
			eosRTOSApplication.cpp	
)


target_sources(${TARGET_NAME} 
	PUBLIC 
		eosDebug.cpp	
)


add_subdirectory("Core")
if(EOS_USE_GRAPHICS)
	add_subdirectory("Graphics")
endif()
add_subdirectory("IO")