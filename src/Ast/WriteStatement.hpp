#ifndef PL0_AST_WRITE_STATEMENT_HPP
#define PL0_AST_WRITE_STATEMENT_HPP

#include "Ast/Statement.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Expression;

struct WriteStatement final : public Statement
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Expression> expression;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_WRITE_STATEMENT_HPP
