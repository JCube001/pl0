#ifndef PL0_AST_LESS_EQUAL_CONDITION_HPP
#define PL0_AST_LESS_EQUAL_CONDITION_HPP

#include "Ast/BinaryCondition.hpp"

namespace PL0 {
namespace Ast {

struct LessEqualCondition final : public BinaryCondition
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_LESS_EQUAL_CONDITION_HPP
