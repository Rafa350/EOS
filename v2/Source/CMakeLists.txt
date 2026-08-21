add_subdirectory("Controllers")
add_subdirectory("HTL")
add_subdirectory("RTOS")
add_subdirectory("Services")
add_subdirectory("StartUp")
add_subdirectory("System")


target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    eosBits.cpp
    eosMath.cpp)
    
