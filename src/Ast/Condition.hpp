#ifndef PL0_AST_CONDITION_HPP
#define PL0_AST_CONDITION_HPP

#include "Ast/Node.hpp"

namespace PL0 {
namespace Ast {

struct Condition : public Node
{
    virtual ~Condition() = default;
    virtual void accept(Visitor& visitor) override = 0;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_CONDITION_HPP
