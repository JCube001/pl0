#ifndef PL0_AST_BINARY_EXPRESSION_HPP
#define PL0_AST_BINARY_EXPRESSION_HPP

#include "Ast/Expression.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct BinaryExpression : public Expression
{
    virtual ~BinaryExpression() = default;
    virtual void accept(Visitor& visitor) override = 0;

    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_BINARY_EXPRESSION_HPP
