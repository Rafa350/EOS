set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PATH                  "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin")
set(TOOLCHAIN_PREFIX                arm-none-eabi-)
set(FLAGS                           "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections --verbose")
set(C_FLAGS                         "-std=gnu18")
set(CPP_FLAGS                       "-fno-rtti -fno-exceptions -fno-threadsafe-statics -fmodules-ts -std=gnu++20")

# Define compiler settings
set(CMAKE_C_COMPILER                ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe ${FLAGS} ${C_FLAGS})
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe ${FLAGS} ${CPP_FLAGS})
set(CMAKE_CXX_SCAN_FOR_MODULES      ON)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objcopy.exe)
set(CMAKE_SIZE                      ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}size.exe)
set(CMAKE_MAKE_PROGRAM              "C:/Program Files/Ninja/ninja.exe")

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)