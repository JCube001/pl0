#ifndef PL0_AST_IF_STATEMENT_HPP
#define PL0_AST_IF_STATEMENT_HPP

#include "Ast/Statement.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Condition;

struct IfStatement final : public Statement
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Condition> condition;
    std::unique_ptr<Statement> consequent;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_IF_STATEMENT_HPP
