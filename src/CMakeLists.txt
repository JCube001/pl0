find_program(RE2C re2c)

set(LEXER_RE ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.re)
set(LEXER_CPP ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)

add_custom_command(
OUTPUT
    ${LEXER_CPP}
COMMAND
    ${RE2C} -W -o ${LEXER_CPP} ${LEXER_RE}
MAIN_DEPENDENCY
    ${LEXER_RE}
VERBATIM
)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(pl0 ${LEXER_CPP} Evaluator.cpp Parser.cpp)
target_compile_features(pl0 PUBLIC cxx_std_17)
target_include_directories(pl0 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(app ${LEXER_CPP} Evaluator.cpp Parser.cpp main.cpp)
target_link_libraries(app PRIVATE pl0 Boost::boost Boost::filesystem)
