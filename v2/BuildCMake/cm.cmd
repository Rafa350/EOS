@echo off 
cmake --toolchain ..\BuildCMake\gcc-arm-none-eabi.cmake --preset Release -S ..\Source -B .\Build -G Ninja