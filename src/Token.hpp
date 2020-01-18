#ifndef PL0_TOKEN_HPP
#define PL0_TOKEN_HPP

#include <string>
#include <variant>

namespace PL0 {
namespace Token {

enum class ID
{
    // Weak symbols

    // Special markers
    Unknown,

    // Keywords
    Then,
    Do,

    // Operators and punctuation
    Assign,
    Equal,
    NotEqual,
    LessThan,
    LessEqual,
    GreaterThan,
    GreaterEqual,
    Plus,
    Minus,
    Multiply,
    Divide,
    LParen,
    RParen,

    // Identifiers and literals
    Number,
    Identifier,

    // Strong symbols

    // Keywords
    Const,
    Var,
    Procedure,
    Call,
    Begin,
    End,
    If,
    While,
    Odd,

    // Operators and punctuation
    Period,
    Comma,
    Semicolon,
    Read,
    Write,

    // Special markers
    EndOfFile,
};

using Value = std::variant<int, std::string>;

} // namespace Token
} // namespace PL0

#endif // PL0_TOKEN_HPP
