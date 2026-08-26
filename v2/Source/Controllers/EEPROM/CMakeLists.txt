# Afegeix els moduls C++
#
target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules 
    TYPE CXX_MODULES 
    FILES
        eosEEPROMDriver.cpp)

# Afegeix subdirectoris
#
add_subdirectory("Drivers")
