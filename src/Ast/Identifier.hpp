#ifndef PL0_AST_IDENTIFIER_HPP
#define PL0_AST_IDENTIFIER_HPP

#include "Ast/Expression.hpp"
#include <string>

namespace PL0 {
namespace Ast {

struct Identifier final : public Expression
{
    Identifier(std::string name)
        : name{name}
    {}

    void accept(Visitor& visitor) override
    { visitor.visit(*this); }

    std::string name;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_IDENTIFIER_HPP
