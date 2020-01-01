#ifndef PL0_AST_ODD_CONDITION_HPP
#define PL0_AST_ODD_CONDITION_HPP

#include "Ast/UnaryCondition.hpp"

namespace PL0 {
namespace Ast {

struct OddCondition final : public UnaryCondition
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_ODD_CONDITION_HPP
