cmake_minimum_required(VERSION 3.10)

project(fp-fault VERSION 0.1 LANGUAGES C)

if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU")
    message(FATAL_ERROR "Only GCC is supported")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/arch/x86/mul_avx.s
    ${PROJECT_SOURCE_DIR}/arch/x86/mul_sse.s
    ${PROJECT_SOURCE_DIR}/arch/x86/mul_x87.s
    ${PROJECT_SOURCE_DIR}/benchmark/fp-fault.c
    ${PROJECT_SOURCE_DIR}/benchmark/operator/mul.c
    ${PROJECT_SOURCE_DIR}/benchmark/benchmark.c
    ${PROJECT_SOURCE_DIR}/driver/x87.c
    ${PROJECT_SOURCE_DIR}/driver/mxcsr.c
)

add_executable(fp-fault ${SRC_FILES})
target_compile_options(fp-fault PRIVATE -Wall -Wextra -Werror)

add_custom_command(TARGET fp-fault POST_BUILD
    COMMENT "Generating objdump of the executable"
    COMMAND objdump -d $<TARGET_FILE:fp-fault> > ${PROJECT_BINARY_DIR}/fp-fault.objdump
)