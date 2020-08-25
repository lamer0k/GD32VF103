cmake_minimum_required(VERSION 3.16)
project(RiscV)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_SOURCE_DIR "C:/GitHub/GD32VF")
#set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(iarconfig.cmake)
#add_compile_definitions(STM32F413xx)

include_directories({CMAKE_SOURCE_DIR}/)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers)
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers/CoreRegisters)
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers/RISCV32)
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers/GD32VF103)
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers/GD32VF103/FieldValues)
include_directories(${CMAKE_SOURCE_DIR}/AbstractHardware/Registers/RISCV32/FieldValues)
include_directories(${CMAKE_SOURCE_DIR}/Common)
include_directories(${CMAKE_SOURCE_DIR}/Common/CriticalSection)
include_directories(${CMAKE_SOURCE_DIR}/IarEvalGd32Kit)

add_executable(RiscV
        main.cpp
        )
