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
    COMPILE_DEFINITIONS TF_LITE_STATIC_MEMORY
    # COMPILE_DEFINITIONS LINUX
    COMPILE_DEFINITIONS TF_LITE_USE_CTIME
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_CMATH_FUNCTIONS
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_MIN
    COMPILE_DEFINITIONS TF_LITE_USE_GLOBAL_MAX
)

set_target_properties( tflm
    PROPERTIES
    COMPILE_FLAGS -fno-rtti
    COMPILE_FLAGS -fno-exceptions
    COMPILE_FLAGS -fno-threadsafe-statics
    # COMPILE_FLAGS -nostdlib
    COMPILE_FLAGS -fno-unwind-tables
    COMPILE_FLAGS -ffunction-sections
    COMPILE_FLAGS -fdata-sections
    COMPILE_FLAGS -fmessage-length=0
)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.cc ${CMAKE_CURRENT_LIST_DIR}/*.cxx ${CMAKE_CURRENT_LIST_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/*.hpp)
target_sources( tflm
    PRIVATE
    ${SRC}
)
