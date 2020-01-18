#include "Parser.hpp"

#include <algorithm>
#include <utility>

// TODO: Skip ahead to some sane position each time an error occurs

namespace PL0 {

std::unique_ptr<Ast::Program> Parser::operator()()
{
    auto program = parseProgram();

    if (!match(Token::ID::EndOfFile)) {
        error("junk after end of program");
    }

    if (failed) {
        return nullptr;
    }

    return program;
}

std::unique_ptr<Ast::Program> Parser::parseProgram()
{
    auto program = std::make_unique<Ast::Program>();

    program->block = parseBlock();

    if (!consume(Token::ID::Period)) {
        error("missing '.' at end of program");
    }

    return program;
}

std::unique_ptr<Ast::Block> Parser::parseBlock()
{
    auto block = std::make_unique<Ast::Block>();

    if (consume(Token::ID::Const)) {
        do {
            auto constant = std::make_unique<Ast::Constant>();

            if (match(Token::ID::Identifier)) {
                constant->identifier = extractIdentifier();
            } else {
                error("identifier expected for const name");
                skip();
                continue;
            }

            if (!consume(Token::ID::Equal)) {
                error("missing '=' after const identifier");
                skip();
                continue;
            }

            if (match(Token::ID::Number)) {
                constant->number = extractNumber();
            } else {
                error("number expected for const value");
                skip();
                continue;
            }

            block->constants.push_back(std::move(constant));
        } while (consume(Token::ID::Comma));

        if (!consume(Token::ID::Semicolon)) {
            error("missing ';' after const definitions");
            skip();
        }
    }

    if (consume(Token::ID::Var)) {
        do {
            if (match(Token::ID::Identifier)) {
                block->variables.push_back(extractIdentifier());
            } else {
                error("identifier expected for var name");
                skip();
                continue;
            }
        } while (consume(Token::ID::Comma));

        if (!consume(Token::ID::Semicolon)) {
            error("missing ';' after var declarations");
            skip();
        }
    }

    while (consume(Token::ID::Procedure)) {
        auto procedure = std::make_unique<Ast::Procedure>();

        if (match(Token::ID::Identifier)) {
            procedure->identifier = extractIdentifier();
        } else {
            error("identifier expected for procedure name");
            skip();
            continue;
        }

        if (!consume(Token::ID::Semicolon)) {
            error("missing ';' after procedure name");
            skip();
            continue;
        }

        procedure->block = parseBlock();

        if (!consume(Token::ID::Semicolon)) {
            error("missing ';' after procedure block");
            skip();
            continue;
        }

        block->procedures.push_back(std::move(procedure));
    }

    block->statement = parseStatement();

    return block;
}

std::unique_ptr<Ast::Statement> Parser::parseStatement()
{
    switch (id) {
        case Token::ID::Identifier: {
            auto statement = std::make_unique<Ast::AssignmentStatement>();

            statement->left = extractIdentifier();

            if (!consume(Token::ID::Assign)) {
                error("missing ':=' after identifier");
                skip();
            }

            statement->right = parseExpression();

            return statement;
        }
        case Token::ID::Call: {
            next();

            auto statement = std::make_unique<Ast::CallStatement>();

            if (match(Token::ID::Identifier)) {
                statement->callee = extractIdentifier();
            } else {
                error("identifier expected after keyword \"call\"");
                skip();
            }

            return statement;
        }
        case Token::ID::Read: {
            next();

            auto statement = std::make_unique<Ast::ReadStatement>();

            if (match(Token::ID::Identifier)) {
                statement->identifier = extractIdentifier();
            } else {
                error("identifier expected after '?'");
                skip();
            }

            return statement;
        }
        case Token::ID::Write: {
            next();
            auto statement = std::make_unique<Ast::WriteStatement>();
            statement->expression = parseExpression();
            return statement;
        }
        case Token::ID::Begin: {
            next();

            auto statement = std::make_unique<Ast::BeginStatement>();

            do {
                statement->children.push_back(parseStatement());
            } while (consume(Token::ID::Semicolon));

            if (!consume(Token::ID::End)) {
                error("expected keyword \"end\" after begin statement");
                skip();
            }

            return statement;
        }
        case Token::ID::If: {
            next();

            auto statement = std::make_unique<Ast::IfStatement>();

            statement->condition = parseCondition();

            if (!consume(Token::ID::Then)) {
                error("missing keyword \"then\" after if-condition");
                skip();
            }

            statement->consequent = parseStatement();

            return statement;
        }
        case Token::ID::While: {
            next();

            auto statement = std::make_unique<Ast::WhileStatement>();

            statement->condition = parseCondition();

            if (!consume(Token::ID::Do)) {
                error("missing keyword \"do\" after while-condition");
                skip();
            }

            statement->consequent = parseStatement();

            return statement;
        }
        default: {
            return nullptr;
        }
    }
}

std::unique_ptr<Ast::Condition> Parser::parseCondition()
{
    if (consume(Token::ID::Odd)) {
        auto condition = std::make_unique<Ast::OddCondition>();
        condition->right = parseExpression();
        return condition;
    }

    return parseBinaryCondition();
}

std::unique_ptr<Ast::BinaryCondition> Parser::parseBinaryCondition()
{
    std::unique_ptr<Ast::BinaryCondition> condition;

    auto left = parseExpression();

    switch (id) {
    case Token::ID::Equal:
        condition = std::make_unique<Ast::EqualCondition>();
        break;
    case Token::ID::NotEqual:
        condition = std::make_unique<Ast::NotEqualCondition>();
        break;
    case Token::ID::LessThan:
        condition = std::make_unique<Ast::LessThanCondition>();
        break;
    case Token::ID::LessEqual:
        condition = std::make_unique<Ast::LessEqualCondition>();
        break;
    case Token::ID::GreaterThan:
        condition = std::make_unique<Ast::GreaterThanCondition>();
        break;
    case Token::ID::GreaterEqual:
        condition = std::make_unique<Ast::GreaterEqualCondition>();
        break;
    default:
        error("expected a conditional operator");
        skip();
        return nullptr;
    }

    next();

    condition->left = std::move(left);
    condition->right = parseExpression();

    return condition;
}

std::unique_ptr<Ast::Expression> Parser::parseExpression()
{
    std::unique_ptr<Ast::Expression> expression;

    if (consume(Token::ID::Plus)) {
        expression = parseTerm();
    } else if (consume(Token::ID::Minus)) {
        auto subExpression = std::make_unique<Ast::NegationExpression>();
        subExpression->right = parseTerm();
        expression = std::move(subExpression);
    } else {
        expression = parseTerm();
    }

    while (match(Token::ID::Plus) || match(Token::ID::Minus)) {
        std::unique_ptr<Ast::BinaryExpression> subExpression;

        if (match(Token::ID::Plus)) {
            subExpression = std::make_unique<Ast::AdditionExpression>();
        } else {
            subExpression = std::make_unique<Ast::SubtractionExpression>();
        }

        next();

        subExpression->left = std::move(expression);
        subExpression->right = parseTerm();
        expression = std::move(subExpression);
    }

    return expression;
}

std::unique_ptr<Ast::Expression> Parser::parseTerm()
{
    auto term = parseFactor();

    while (match(Token::ID::Multiply) || match(Token::ID::Divide)) {
        std::unique_ptr<Ast::BinaryExpression> subTerm;

        if (match(Token::ID::Multiply)) {
            subTerm = std::make_unique<Ast::MultiplicationExpression>();
        } else {
            subTerm = std::make_unique<Ast::DivisionExpression>();
        }

        next();

        subTerm->left = std::move(term);
        subTerm->right = parseFactor();
        term = std::move(subTerm);
    }

    return term;
}

std::unique_ptr<Ast::Expression> Parser::parseFactor()
{
    switch (id) {
        case Token::ID::Identifier: {
            return extractIdentifier();
        }
        case Token::ID::Number: {
            return extractNumber();
        }
        case Token::ID::LParen: {
            next();

            auto expression = parseExpression();

            if (!consume(Token::ID::RParen)) {
                error("missing ')' after expression");
                skip();
            }

            return expression;
        }
        default: {
            return nullptr;
        }
    }
}

std::unique_ptr<Ast::Number> Parser::extractNumber()
{
    auto value = boost::get<int>(lex.getValue());
    next();
    return std::make_unique<Ast::Number>(value);
}

std::unique_ptr<Ast::Identifier> Parser::extractIdentifier()
{
    auto name = boost::get<std::string>(lex.getValue());
    next();
    return std::make_unique<Ast::Identifier>(name);
}

void Parser::error(std::string_view message)
{
    failed = true;
    diagnostic << lex.getLine() << ": error: " << message << '\n';
}

void Parser::skip()
{
    while (id < Token::ID::Const) {
        next();
    }
}

} // namespace PL0
