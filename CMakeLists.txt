cmake_minimum_required(VERSION 3.16)
enable_language(ASM)

project(AzadiSDK C)

set(TARGET test)

set(TESTNAME gpio_test CACHE STRING "Enter name of a test.")

add_subdirectory(src)
add_executable( ${TARGET}.elf softwares/${TESTNAME}/${TESTNAME}.c azadi/start.S)
target_sources( ${TARGET}.elf PUBLIC "${CMAKE_SOURCE_DIR}/azadi/start.S"
									"${CMAKE_SOURCE_DIR}/azadi/trap.c"
									"${CMAKE_SOURCE_DIR}/azadi/trap_entry.S" )
SET(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/azadi/link.ld")

set_target_properties( ${TARGET}.elf PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}" )

target_link_libraries( ${TARGET}.elf PUBLIC src )
target_include_directories( ${TARGET}.elf PUBLIC "${PROJECT_SOURCE_DIR}/include" )
target_include_directories( src PUBLIC "${PROJECT_SOURCE_DIR}/include" )


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -T ${LINKER_SCRIPT}")

# Post processing command to create a disassembly file 
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S  ${TARGET}.elf > ${TARGET}.disasm
        COMMENT "Invoking: Disassemble")

# Post processing command to create a hex file 
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O verilog  ${TARGET}.elf  ${TARGET}.hex
        COMMENT "Invoking: Hexdump")

# Post processing command to add terminating instruction to hex file 
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND echo -n "00 FF FF 00" >> ${TARGET}.hex)