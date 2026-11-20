target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        CanOpen_PDOProducer.cpp
        CanOpen_SDOClient.cpp
        CanOpen_SDOCommon.cpp
        CanOpen_SDOServer.cpp
        CanOpen_NMTMaster.cpp
        CanOpen_HBProducer.cpp
)
