target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
      eosCriticalSection.cpp
      eosHeapAllocator.cpp
      eosQueue.cpp
      eosSemaphore.cpp
)
