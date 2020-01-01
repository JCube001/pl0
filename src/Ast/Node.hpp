#ifndef PL0_AST_NODE_HPP
#define PL0_AST_NODE_HPP

#include "Ast/Visitor.hpp"

namespace PL0 {
namespace Ast {

struct Node
{
    virtual ~Node() = default;
    virtual void accept(Visitor& visitor) = 0;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_NODE_HPP
