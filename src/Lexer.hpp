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
    explicit Lexer(const std::string& input, std::ostream& diagnostic)
        : diagnostic{diagnostic}
        , cursor{input.c_str()}
        , lexeme{}
        , line{1}
        , value{}
    {}

    Token::ID operator()();

    std::size_t getLine() const
    { return line; }

    Token::Value&& getValue()
    { return std::move(value); }

private:
    using Symbol = std::string::value_type;

    std::size_t getSize() const
    { return cursor - lexeme; }

    std::ostream& diagnostic;
    const Symbol* cursor;
    const Symbol* lexeme;
    std::size_t line;
    Token::Value value;
};

} // namespace PL0

#endif // PL0_LEXER_HPP
