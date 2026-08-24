# Afegeix els moduls C++
#
target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules 
    TYPE CXX_MODULES 
    FILES
        htlRegs.cpp)


# Afegeix els subdirectoris
#
if(EOS_PLATFORM_NAME MATCHES "^STM32")
	add_subdirectory("STM32")
elseif(EOS_PLATFORM_NAME MATCHES "^PIC32")
	add_subdirectory("PIC32")
endif()
