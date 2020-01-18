#ifndef PL0_LEXER_HPP
#define PL0_LEXER_HPP

#include "Token.hpp"
#include <ostream>
#include <string>
#include <utility>
#include <cstddef>

namespace PL0 {

class Lexer
{
public:
    Lexer(const std::string& input, std::ostream& diagnostic)
        : diagnostic{diagnostic}
        , cursor{input.c_str()}
        , lexeme{cursor}
        , line{1}
        , column{1}
        , value{}
    {}

    Token::ID operator()();

    std::size_t getLine() const
    { return line; }

    std::size_t getColumn() const
    { return column; }

    Token::Value&& getValue()
    { return std::move(value); }

private:
    using ID = Token::ID;
    using Symbol = std::string::value_type;

    std::ostream& diagnostic;
    const Symbol* cursor;
    const Symbol* lexeme;
    std::size_t line;
    std::size_t column;
    Token::Value value;
};

} // namespace PL0

#endif // PL0_LEXER_HPP
