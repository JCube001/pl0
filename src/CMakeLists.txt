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

add_library(pl0 ${LEXER_CPP} Parser.cpp Evaluator.cpp DotGenerator.cpp)
target_compile_features(pl0 PUBLIC cxx_std_17)
target_include_directories(pl0 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pl0 PUBLIC Boost::boost)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE pl0 Boost::filesystem)
set_target_properties(app PROPERTIES OUTPUT_NAME pl0)
