target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        bits.cpp
        concepts.cpp
        configuration.cpp
        math.cpp
        platform.cpp
        result.cpp
        eosToolchain.cpp
        types.cpp
)

add_subdirectory("Controllers")
add_subdirectory("HTL")
add_subdirectory("Hardware")
add_subdirectory("Services")
add_subdirectory("StartUp")
add_subdirectory("System")
