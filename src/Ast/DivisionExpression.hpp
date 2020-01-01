#ifndef PL0_AST_DIVISION_EXPRESSION_HPP
#define PL0_AST_DIVISION_EXPRESSION_HPP

#include "Ast/BinaryExpression.hpp"

namespace PL0 {
namespace Ast {

struct DivisionExpression final : public BinaryExpression
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_DIVISION_EXPRESSION_HPP
