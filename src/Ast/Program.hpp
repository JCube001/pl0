#ifndef PL0_AST_PROGRAM_HPP
#define PL0_AST_PROGRAM_HPP

#include "Ast/Node.hpp"
#include <memory>

namespace PL0 {
namespace Ast {

struct Block;

struct Program final : public Node
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::unique_ptr<Block> block;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_PROGRAM_HPP
