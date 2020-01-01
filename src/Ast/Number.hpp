#ifndef PL0_AST_NUMBER_HPP
#define PL0_AST_NUMBER_HPP

#include "Ast/Expression.hpp"

namespace PL0 {
namespace Ast {

struct Number final : public Expression
{
    Number(const int value)
        : value{value}
    {}

    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    int value;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_NUMBER_HPP
