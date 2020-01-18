#ifndef PL0_EVALUATOR_HPP
#define PL0_EVALUATOR_HPP

#include "Ast/Ast.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace PL0 {

class Evaluator final : public Ast::Visitor
{
public:
    Evaluator(std::istream& in, std::ostream& out)
        : in{in}
        , out{out}
        , consequence{false}
        , stack{}
        , scopes{Scope{}}
    {}

    void visit(Ast::Program& program) override;
    void visit(Ast::Block& block) override;
    void visit(Ast::Constant& constant) override;
    void visit(Ast::Procedure& procedure) override;
    void visit(Ast::AssignmentStatement& statement) override;
    void visit(Ast::CallStatement& statement) override;
    void visit(Ast::ReadStatement& statement) override;
    void visit(Ast::WriteStatement& statement) override;
    void visit(Ast::BeginStatement& statement) override;
    void visit(Ast::IfStatement& statement) override;
    void visit(Ast::WhileStatement& statement) override;
    void visit(Ast::OddCondition& condition) override;
    void visit(Ast::EqualCondition& condition) override;
    void visit(Ast::NotEqualCondition& condition) override;
    void visit(Ast::LessThanCondition& condition) override;
    void visit(Ast::LessEqualCondition& condition) override;
    void visit(Ast::GreaterThanCondition& condition) override;
    void visit(Ast::GreaterEqualCondition& condition) override;
    void visit(Ast::AdditionExpression& expression) override;
    void visit(Ast::SubtractionExpression& expression) override;
    void visit(Ast::MultiplicationExpression& expression) override;
    void visit(Ast::DivisionExpression& expression) override;
    void visit(Ast::NegationExpression& expression) override;
    void visit(Ast::Identifier& identifier) override;
    void visit(Ast::Number& number) override;

private:
    struct Scope
    {
        std::map<std::string, const int> constants;
        std::map<std::string, int> variables;
        std::map<std::string, std::reference_wrapper<Ast::Procedure>> procedures;
    };

    std::istream& in;
    std::ostream& out;
    bool consequence;
    std::stack<int, std::vector<int>> stack;
    std::vector<Scope> scopes;
};

} // namespace PL0

#endif // PL0_EVALUATOR_HPP
