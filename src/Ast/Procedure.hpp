#ifndef PL0_AST_PROCEDURE_HPP
#define PL0_AST_PROCEDURE_HPP

#include "Ast/Node.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Identifier;
struct Block;

struct Procedure final : public Node
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Identifier> identifier;
    std::unique_ptr<Block> block;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_PROCEDURE_HPP
