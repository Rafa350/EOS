# Afegeix els moduls C++
#
target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules 
    TYPE CXX_MODULES
    BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        eosBits.cpp
        eosMath.cpp)
        
        
# Afegeix els subdirectoris adicionals
#        
add_subdirectory("Controllers")
add_subdirectory("HTL")
add_subdirectory("RTOS")
add_subdirectory("Services")
add_subdirectory("StartUp")
add_subdirectory("System")
