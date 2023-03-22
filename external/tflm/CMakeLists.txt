add_library(tflm "")

target_include_directories( tflm
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/third_party/gemmlowp
    ${CMAKE_CURRENT_LIST_DIR}/third_party/flatbuffers/include
    ${CMAKE_CURRENT_LIST_DIR}/third_party/ruy
    ${CMAKE_CURRENT_LIST_DIR}/third_party/kissfft
)

target_compile_definitions( tflm
    PUBLIC
    COMPILE_DEFINITIONS TF_LITE_MCU_DEBUG_LOG
    # COMPILE_DEFINITIONS LINUX
    COMPILE_DEFINITIONS TF_LITE_USE_CTIME
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_CMATH_FUNCTIONS
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_MIN
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_MAX
)

target_compile_options( tflm
    PUBLIC -funsigned-char
    PUBLIC -fno-delete-null-pointer-checks
    PUBLIC -fomit-frame-pointer
    PUBLIC -fpermissive
    PUBLIC -fno-builtin-printf
    PUBLIC -nostdlib
    PUBLIC -fno-use-cxa-atexit
	PUBLIC -fno-exceptions
	PUBLIC -mexplicit-relocs
	PUBLIC -fno-rtti
	PUBLIC -fno-threadsafe-statics
)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.cc ${CMAKE_CURRENT_LIST_DIR}/*.cxx ${CMAKE_CURRENT_LIST_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/*.hpp)
target_sources( tflm
    PRIVATE
    ${SRC}
)
