target_sources(${TARGET_NAME} PUBLIC
    FILE_SET cxx_modules 
    TYPE CXX_MODULES 
    FILES
        eosCanOpenService.cpp)
        
target_sources(${TARGET_NAME} PUBLIC
    eosCanOpenDictionary.cpp
)