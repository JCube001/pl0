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
            return ID::Unknown;
        }

        "\x00" { return ID::EndOfFile; }

        // Whitespace
        "\n"         { ++line; column = 0; goto loop; }
        [ \r\f\t\v]+ { goto loop; }

        // Keywords
        "const"     { return ID::Const; }
        "var"       { return ID::Var; }
        "procedure" { return ID::Procedure; }
        "call"      { return ID::Call; }
        "begin"     { return ID::Begin; }
        "end"       { return ID::End; }
        "if"        { return ID::If; }
        "then"      { return ID::Then; }
        "while"     { return ID::While; }
        "do"        { return ID::Do; }
        "odd"       { return ID::Odd; }

        // Operators and punctuation
        "."  { return ID::Period; }
        ","  { return ID::Comma; }
        ";"  { return ID::Semicolon; }
        ":=" { return ID::Assign; }
        "?"  { return ID::Read; }
        "!"  { return ID::Write; }
        "="  { return ID::Equal; }
        "#"  { return ID::NotEqual; }
        "<"  { return ID::LessThan; }
        "<=" { return ID::LessEqual; }
        ">"  { return ID::GreaterThan; }
        ">=" { return ID::GreaterEqual; }
        "+"  { return ID::Plus; }
        "-"  { return ID::Minus; }
        "*"  { return ID::Multiply; }
        "/"  { return ID::Divide; }
        "("  { return ID::LParen; }
        ")"  { return ID::RParen; }

        // Number
        [0-9]+
        {
            value = boost::lexical_cast<int>(lexeme, cursor - lexeme);
            return ID::Number;
        }

        // Identifier
        [A-Za-z_][A-Za-z0-9_]*
        {
            value = std::string(lexeme, cursor);
            return ID::Identifier;
        }
    */
}

} // namespace PL0
