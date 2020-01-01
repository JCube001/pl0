#ifndef PL0_AST_EXPRESSION_HPP
#define PL0_AST_EXPRESSION_HPP

#include "Ast/Node.hpp"

namespace PL0 {
namespace Ast {

struct Expression : public Node
{
    virtual ~Expression() = default;
    virtual void accept(Visitor& visitor) override = 0;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_EXPRESSION_HPP
