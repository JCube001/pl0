#ifndef PL0_PARSER_HPP
#define PL0_PARSER_HPP

#include "Ast/Ast.hpp"
#include "Lexer.hpp"
#include <ostream>
#include <string>
#include <string_view>

namespace PL0 {

class Parser
{
public:
    Parser(const std::string& input, std::ostream& diagnostic)
        : diagnostic{diagnostic}
        , lex{input, diagnostic}
        , id{lex()}
        , failed{false}
    {}

    std::unique_ptr<Ast::Program> operator()();

private:
    using ID = Token::ID;

    std::unique_ptr<Ast::Program> parseProgram();
    std::unique_ptr<Ast::Block> parseBlock();
    std::unique_ptr<Ast::Statement> parseStatement();
    std::unique_ptr<Ast::Condition> parseCondition();
    std::unique_ptr<Ast::BinaryCondition> parseBinaryCondition();
    std::unique_ptr<Ast::Expression> parseExpression();
    std::unique_ptr<Ast::Expression> parseTerm();
    std::unique_ptr<Ast::Expression> parseFactor();
    std::unique_ptr<Ast::Number> extractNumber();
    std::unique_ptr<Ast::Identifier> extractIdentifier();

    void error(std::string_view message);
    void skip();

    bool match(const ID expected) const
    { return id == expected; }

    bool consume(const ID expected)
    {
        if (match(expected)) {
            next();
            return true;
        }

        return false;
    }

    void next()
    { id = lex(); }

    std::ostream& diagnostic;
    Lexer lex;
    ID id;
    bool failed;
};

} // namespace

#endif // PL0_PARSER_HPP
