cmake_minimum_required(VERSION 3.16)
project(lua_compiler)

# Add flex dependence to project
find_program(FLEX_EXECUTABLE flex)
if (NOT FLEX_EXECUTABLE)
    message(FATAL_ERROR "Flex not found! Install flex and try again.")
endif ()

# Add bison dependence to project
find_program(BISON_EXECUTABLE bison)
if (NOT BISON_EXECUTABLE)
    message(FATAL_ERROR "Bison not found! Install bison and try again.")
endif ()

# Create directory for generated files
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Paths for generated files
set(GENERATED_LEXER_SOURCE "${GENERATED_DIR}/lex.yy.cpp")
set(GENERATED_BISON_SOURCE "${GENERATED_DIR}/lua_parser.tab.c")
set(GENERATED_BISON_HEADER "${GENERATED_DIR}/lua_parser.tab.h")

# Generation bison source file
add_custom_command(
        OUTPUT ${GENERATED_BISON_SOURCE} ${GENERATED_BISON_HEADER}
        COMMAND ${BISON_EXECUTABLE}
        --verbose
        --defines=${GENERATED_BISON_HEADER}
        -o ${GENERATED_BISON_SOURCE}
        src/lua_parser.y
        DEPENDS src/lua_parser.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating C++ parser with Bison"
)

# Generation flex source file
add_custom_command(
        OUTPUT ${GENERATED_LEXER_SOURCE}
        COMMAND ${FLEX_EXECUTABLE}
        --c++
        -o ${GENERATED_LEXER_SOURCE}
        src/lua_lexer.l
        DEPENDS src/lua_lexer.l
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating C++ lexer with Flex"
)

add_subdirectory(jvm-class-builder)

# Paths for nodes classes
set(SOURCE_FILES
        src/main.cpp
        src/node/Node.cpp
        src/node/ExpressionNode.cpp
        src/node/StatementNode.cpp
        src/lexer/LexerStringBuilder.cpp
        src/node/Program.cpp
        include/LiteralExprNode.h
)

# Add files to executable target
add_executable(lua_compiler
        ${SOURCE_FILES}
        ${GENERATED_LEXER_SOURCE}
        ${GENERATED_BISON_SOURCE}
)

target_include_directories(lua_compiler
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GENERATED_DIR}
)

# Set source files properties for C++ and Bison header
set_source_files_properties(${GENERATED_LEXER_SOURCE} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${GENERATED_BISON_SOURCE} PROPERTIES LANGUAGE CXX)

set_target_properties(lua_compiler PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

# Add link to flex library
target_link_libraries(lua_compiler
        PRIVATE
        fl
        jvm::ClassBuilder
)
