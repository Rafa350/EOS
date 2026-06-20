add_subdirectory("Core")
add_subdirectory("Graphics")
add_subdirectory("IO")

target_sources(${TARGET_NAME} PUBLIC 
	eosApplicationBase.cpp
	eosDebug.cpp	
	eosRTOSApplication.cpp	
)
