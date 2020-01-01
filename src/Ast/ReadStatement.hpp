#ifndef PL0_AST_READ_STATEMENT_HPP
#define PL0_AST_READ_STATEMENT_HPP

#include "Ast/Statement.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Identifier;

struct ReadStatement final : public Statement
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Identifier> identifier;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_READ_STATEMENT_HPP
