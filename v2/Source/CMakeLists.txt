target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        eosBits.cpp
        eosConcepts.cpp
        eosConfiguration.cpp
        eosMath.cpp
        eosPlatform.cpp
        eosResult.cpp
        eosToolchain.cpp
        eosTypes.cpp
)

add_subdirectory("Controllers")
add_subdirectory("HTL")
add_subdirectory("Services")
add_subdirectory("StartUp")
add_subdirectory("System")
