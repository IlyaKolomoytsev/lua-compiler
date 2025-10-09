cmake_minimum_required(VERSION 3.16)
project(lua_compiler)

set(CMAKE_CXX_STANDARD 11)

# Add flex dependence to project
find_program(FLEX_EXECUTABLE flex)
if(NOT FLEX_EXECUTABLE)
    message(FATAL_ERROR "Flex not found! Install flex and try again.")
endif()

# Add bison dependence to project
find_program(BISON_EXECUTABLE bison)
if(NOT BISON_EXECUTABLE)
    message(FATAL_ERROR "Bison not found! Install bison and try again.")
endif()

# Paths for generated files
set(GENERATED_LEXER_FILE "${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp")
set(GENERATED_BISON_FILE "${CMAKE_CURRENT_BINARY_DIR}/lua_parser.tab.c")
set(GENERATED_BISON_HEADER "${CMAKE_CURRENT_BINARY_DIR}/lua_parser.tab.h")

# Generation bison source file
add_custom_command(
        OUTPUT ${GENERATED_BISON_FILE} ${GENERATED_BISON_HEADER}
        COMMAND ${BISON_EXECUTABLE} -d -o ${GENERATED_BISON_FILE} lua_parser.y
        DEPENDS lua_parser.y
        COMMENT "Generating C++ parser with Bison"
)

# Generation flex source file
add_custom_command(
        OUTPUT ${GENERATED_LEXER_FILE}
        COMMAND ${FLEX_EXECUTABLE} --c++ -o ${GENERATED_LEXER_FILE} lua_lexer.l
        DEPENDS lua_lexer.l
        COMMENT "Generating C++ lexer with Flex"
)

# Add files to executable target
add_executable(lua_compiler
        main.cpp
        ${GENERATED_LEXER_FILE}
        ${GENERATED_BISON_FILE}
        ${GENERATED_BISON_HEADER}
)

# Set source files properties for C++ and Bison header
set_source_files_properties(${GENERATED_LEXER_FILE} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${GENERATED_BISON_FILE} PROPERTIES LANGUAGE CXX)


# Add link to flex library
target_link_libraries(lua_compiler PRIVATE fl)
