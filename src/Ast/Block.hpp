#ifndef PL0_AST_BLOCK_HPP
#define PL0_AST_BLOCK_HPP

#include "Ast/Node.hpp"
#include <memory>
#include <vector>

namespace PL0 {
namespace Ast {

struct Constant;
struct Identifier;
struct Procedure;
struct Statement;

struct Block final : public Node
{
    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::vector<std::unique_ptr<Constant>> constants;
    std::vector<std::unique_ptr<Identifier>> variables;
    std::vector<std::unique_ptr<Procedure>> procedures;
    std::unique_ptr<Statement> statement;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_BLOCK_HPP
