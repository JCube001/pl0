#ifndef PL0_DOT_GENERATOR_HPP
#define PL0_DOT_GENERATOR_HPP

#include "Ast/Ast.hpp"
#include <ostream>
#include <vector>
#include <cstdint>

namespace PL0 {

class DotGenerator final : public Ast::Visitor
{
public:
    DotGenerator(std::ostream& out)
        : out{out}
        , id{0}
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
    void startVertex(const char* name);
    void startVertex(const char* name, const char* shape);
    void startVertex(const int value, const char* shape);
    void startUnlinkedVertex(const char* name);
    void startUnlinkedVertex(const char* name, const char* shape);
    void startUnlinkedVertex(const int value, const char* shape);
    void endVertex();
    void addEdgeToParent();

    std::ostream& out;
    std::uint64_t id;
    std::vector<std::uint64_t> stack;
};

} // namespace PL0

#endif // PL0_DOT_GENERATOR_HPP
