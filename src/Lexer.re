#include "Lexer.hpp"

#include <boost/lexical_cast.hpp>

namespace PL0 {

Token::ID Lexer::operator()()
{
loop:
    column += cursor - lexeme;
    lexeme = cursor;
    /*!re2c
        re2c:define:YYCTYPE = 'Symbol';
        re2c:define:YYCURSOR = 'cursor';
        re2c:flags:case-insensitive = 1;
        re2c:yyfill:enable = 0;

        // Special symbols
        *
        {
            diagnostic << line << ": error: unrecognized symbol '" << yych << "'\n";
            return Token::ID::Unknown;
        }

        "\x00" { return Token::ID::EndOfFile; }

        // Whitespace
        "\n"         { ++line; column = 0; goto loop; }
        [ \r\f\t\v]+ { goto loop; }

        // Keywords
        "const"     { return Token::ID::Const; }
        "var"       { return Token::ID::Var; }
        "procedure" { return Token::ID::Procedure; }
        "call"      { return Token::ID::Call; }
        "begin"     { return Token::ID::Begin; }
        "end"       { return Token::ID::End; }
        "if"        { return Token::ID::If; }
        "then"      { return Token::ID::Then; }
        "while"     { return Token::ID::While; }
        "do"        { return Token::ID::Do; }
        "odd"       { return Token::ID::Odd; }

        // Operators and punctuation
        "."  { return Token::ID::Period; }
        ","  { return Token::ID::Comma; }
        ";"  { return Token::ID::Semicolon; }
        ":=" { return Token::ID::Assign; }
        "?"  { return Token::ID::Read; }
        "!"  { return Token::ID::Write; }
        "="  { return Token::ID::Equal; }
        "#"  { return Token::ID::NotEqual; }
        "<"  { return Token::ID::LessThan; }
        "<=" { return Token::ID::LessEqual; }
        ">"  { return Token::ID::GreaterThan; }
        ">=" { return Token::ID::GreaterEqual; }
        "+"  { return Token::ID::Plus; }
        "-"  { return Token::ID::Minus; }
        "*"  { return Token::ID::Multiply; }
        "/"  { return Token::ID::Divide; }
        "("  { return Token::ID::LParen; }
        ")"  { return Token::ID::RParen; }

        // Number
        [0-9]+
        {
            value = boost::lexical_cast<int>(lexeme, getSize());
            return Token::ID::Number;
        }

        // Identifier
        [A-Za-z_][A-Za-z0-9_]*
        {
            value = std::string(lexeme, getSize());
            return Token::ID::Identifier;
        }
    */
}

} // namespace PL0
