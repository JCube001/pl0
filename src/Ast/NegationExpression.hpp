#ifndef PL0_AST_NEGATION_EXPRESSION_HPP
#define PL0_AST_NEGATION_EXPRESSION_HPP

#include "Ast/UnaryExpression.hpp"

namespace PL0 {
namespace Ast {

struct NegationExpression final : public UnaryExpression
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_NEGATION_EXPRESSION_HPP
