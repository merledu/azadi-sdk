cmake_minimum_required(VERSION 3.16)
enable_language(ASM)
enable_language(CXX)

project(AzadiSDK C)

set(TARGET test)

set(TESTNAME gpio_test CACHE STRING "Enter name of a test.")
option(USE_TFLM "compile with tflm library" ON)

if(USE_TFLM)
        add_subdirectory("${CMAKE_SOURCE_DIR}/external/tflm")
        list(APPEND OPTIONAL_LIBS tflm)
endif()

add_subdirectory(src)

add_executable( ${TARGET}.elf "")
file(GLOB_RECURSE TEST_SRC "${CMAKE_SOURCE_DIR}/softwares/${TESTNAME}/*.c" "${CMAKE_SOURCE_DIR}/softwares/${TESTNAME}/*.cc" "${CMAKE_SOURCE_DIR}/softwares/${TESTNAME}/*.h")
target_sources( ${TARGET}.elf PUBLIC "${CMAKE_SOURCE_DIR}/azadi/start.S" "${CMAKE_SOURCE_DIR}/azadi/trap.c"
									"${CMAKE_SOURCE_DIR}/azadi/trap_entry.S" ${TEST_SRC})
SET(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/azadi/link.ld")

set_target_properties( ${TARGET}.elf PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}" )

target_link_libraries( ${TARGET}.elf PUBLIC src ${OPTIONAL_LIBS} )
target_include_directories( ${TARGET}.elf PUBLIC "${PROJECT_BINARY_DIR}" )


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