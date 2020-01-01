#ifndef PL0_AST_BINARY_CONDITION_HPP
#define PL0_AST_BINARY_CONDITION_HPP

#include "Ast/Condition.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Expression;

struct BinaryCondition : public Condition
{
    virtual ~BinaryCondition() = default;
    virtual void accept(Visitor& visitor) override = 0;

    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_BINARY_CONDITION_HPP
