target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
        FILES
            htlRegs.cpp
)


if(EOS_PLATFORM_NAME MATCHES "^STM32")
	add_subdirectory("STM32")
elseif(EOS_PLATFORM_NAME MATCHES "^PIC32")
	add_subdirectory("PIC32")
endif()
