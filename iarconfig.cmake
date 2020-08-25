
# enable C and assembler source
enable_language(C ASM CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "--c++")
set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "--c++")
### BEGIN CMAKE_TOOLCHAIN_FILE
# "Generic" is used when cross compiling
set(CMAKE_SYSTEM_NAME Generic)

# Set the EW installation root directory
set(EW_ROOT_DIR "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.4/riscv")

# set common compiler flags for all build types
set(CPU_FLAGS "--core=RV32IMAC -e -Ol --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_cross_call --no_cross_jump --debug")

# Set up the CMake and Cpp compilers. But it is already set in high level project settings
set(CMAKE_C_COMPILER "${EW_ROOT_DIR}/bin/iccriscv.exe")
set(CMAKE_CXX_COMPILER "${EW_ROOT_DIR}/bin/iccriscv.exe" )
# Set up the CMake asm compilers
set(CMAKE_ASM_COMPILER "${EW_ROOT_DIR}/bin/iasmriscv.exe")

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Set up the CMake variables for the linker
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/GD32VF103C8T6.icf")
set(CMAKE_CXX_LINK_FLAGS "--config ${LINKER_SCRIPT} --map test.map --no_out_extension --entry __iar_program_start --debug_lib --vfe --text_out locale ")

set(CMAKE_CXX_LINK_EXECUTABLE "${EW_ROOT_DIR}/bin/ilinkriscv.exe ${CMAKE_CXX_LINK_FLAGS}" )

#set(CMAKE_LINKER "${EW_ROOT_DIR}/bin/ilinkriscv.exe " )

#ilinkriscv.exe C:\GitHub\ADC-AND-LED\Debug\Obj\main.o --config_def CSTACK_SIZE=0x1000 --config_def HEAP_SIZE=0 --no_out_extension -o C:\GitHub\ADC-AND-LED\Debug\Exe\test.out --map C:\GitHub\ADC-AND-LED\Debug\List\
#test.map --config C:\Program Files (x86)\IAR Systems\Embedded Workbench RISCV 8.4\riscv\config\linker\generic.icf --entry __iar_program_start --debug_lib --vfe --text_out locale

#Set IAR setting for bedug build
if (CMAKE_BUILD_TYPE  MATCHES Debug)
    message ("IAR Debug")
    # set a preprocessor symbol "DEBUG"
    add_compile_definitions( DEBUG=1 )
    #add_compile_definitions(__TIME__=1)

    # set up the CMake variables for the compiler for DEBUG
    set (CMAKE_C_FLAGS "${CPU_FLAGS} --dlib_config=normal")
    set (CMAKE_ASM_FLAGS  "${CMAKE_ASM_FLAGS} ")
    set (CMAKE_CXX_FLAGS  "${CPU_FLAGS} --dlib_config=normal")

else(CMAKE_BUILD_TYPE  MATCHES Release)
    message ("IAR Release")
    # set up the CMake variables for the compiler for Release
    set (CMAKE_C_FLAGS  "${CPU_FLAGS} --dlib_config=normal")
    set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ")
    set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${CPU_FLAGS} --dlib_config=normal")
endif()
### END CMAKE_TOOLCHAIN_FILE