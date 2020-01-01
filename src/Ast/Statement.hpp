#ifndef PL0_AST_STATEMENT_HPP
#define PL0_AST_STATEMENT_HPP

#include "Ast/Node.hpp"

namespace PL0 {
namespace Ast {

struct Statement : public Node
{
    virtual ~Statement() = default;
    virtual void accept(Visitor& visitor) override = 0;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_STATEMENT_HPP
