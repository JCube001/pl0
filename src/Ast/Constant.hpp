#ifndef PL0_AST_CONSTANT_HPP
#define PL0_AST_CONSTANT_HPP

#include "Ast/Node.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Identifier;
struct Number;

struct Constant final : public Node
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Identifier> identifier;
    std::unique_ptr<Number> number;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_CONSTANT_HPP
