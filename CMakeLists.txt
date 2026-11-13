cmake_minimum_required(VERSION 3.20)
project(shell LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(
    SOURCE_FILES
    src/main.c
    src/shell/shell.c
    src/shell/builtins/builtins.c
    src/shell/input/input.c
)

set(
    HEADER_FILES
    src/shell/shell.h
    src/shell/builtins/builtins.h
    src/shell/input/input.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src/)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -fsanitize=address
)

find_program(CLANG_FORMAT clang-format REQUIRED)

add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES} ${HEADER_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting C source and header files"
    VERBATIM
)

add_custom_target(format-check
    COMMAND ${CLANG_FORMAT} --dry-run --Werror ${SOURCE_FILES} ${HEADER_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Checking C source and header formatting"
    VERBATIM
)
