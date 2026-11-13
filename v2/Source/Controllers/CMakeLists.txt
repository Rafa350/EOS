add_subdirectory("CLI")

if(EOS_USE_GRAPHICS)
    add_subdirectory("Display")
endif()

add_subdirectory("EEPROM")
add_subdirectory("Pin")
add_subdirectory("Serial")
add_subdirectory("TTY")
