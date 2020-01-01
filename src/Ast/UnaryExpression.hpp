#ifndef PL0_AST_UNARY_EXPRESSION_HPP
#define PL0_AST_UNARY_EXPRESSION_HPP

#include "Ast/Expression.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct UnaryExpression : public Expression
{
    virtual ~UnaryExpression() = default;
    virtual void accept(Visitor& visitor) override = 0;

    std::unique_ptr<Expression> right;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_UNARY_EXPRESSION_HPP
