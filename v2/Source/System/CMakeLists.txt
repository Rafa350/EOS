add_subdirectory("Core")
if(EOS_USE_GRAPHICS)
add_subdirectory("Graphics")
endif()
add_subdirectory("IO")

target_sources(${TARGET_NAME} PUBLIC 
	eosApplicationBase.cpp
	eosDebug.cpp	
	eosRTOSApplication.cpp	
)
