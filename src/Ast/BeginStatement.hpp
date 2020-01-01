#ifndef PL0_AST_BEGIN_STATEMENT_HPP
#define PL0_AST_BEGIN_STATEMENT_HPP

#include "Ast/Statement.hpp"
#include <memory>
#include <vector>

namespace PL0 {
namespace Ast {

struct BeginStatement final : public Statement
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::vector<std::unique_ptr<Statement>> children;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_BEGIN_STATEMENT_HPP
