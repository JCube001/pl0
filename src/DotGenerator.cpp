#include "DotGenerator.hpp"

namespace PL0 {

void DotGenerator::visit(Ast::Program& program)
{
    out << "digraph G {\n";
    out << "node [shape=oval];\n";

    startUnlinkedVertex("Program");
    program.block->accept(*this);
    endVertex();

    out << "}\n";
}

void DotGenerator::visit(Ast::Block& block)
{
    startVertex("Block");

    startVertex("Constants");
    for (auto& constant : block.constants) {
        constant->accept(*this);
    }
    endVertex();

    startVertex("Variables");
    for (auto& variable : block.variables) {
        variable->accept(*this);
    }
    endVertex();

    startVertex("Procedures");
    for (auto& procedure : block.procedures) {
        procedure->accept(*this);
    }
    endVertex();

    if (block.statement)
        block.statement->accept(*this);

    endVertex();
}

void DotGenerator::visit(Ast::Constant& constant)
{
    startVertex("Constant");
    constant.identifier->accept(*this);
    constant.number->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::Procedure& procedure)
{
    startVertex("Procedure");
    procedure.block->accept(*this);
    procedure.identifier->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::AssignmentStatement& statement)
{
    startVertex("AssignmentStatement");
    statement.left->accept(*this);
    statement.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::CallStatement& statement)
{
    startVertex("CallStatement");
    statement.callee->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::ReadStatement& statement)
{
    startVertex("ReadStatement");
    statement.identifier->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::WriteStatement& statement)
{
    startVertex("WriteStatement");
    statement.expression->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::BeginStatement& statement)
{
    startVertex("BeginStatement");
    for (auto& child : statement.children) {
        child->accept(*this);
    }
    endVertex();
}

void DotGenerator::visit(Ast::IfStatement& statement)
{
    startVertex("IfStatement");
    statement.condition->accept(*this);
    statement.consequent->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::WhileStatement& statement)
{
    startVertex("WhileStatement");
    statement.condition->accept(*this);
    statement.consequent->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::OddCondition& condition)
{
    startVertex("OddCondition");
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::EqualCondition& condition)
{
    startVertex("EqualCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::NotEqualCondition& condition)
{
    startVertex("NotEqualCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::LessThanCondition& condition)
{
    startVertex("LessThanCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::LessEqualCondition& condition)
{
    startVertex("LessEqualCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::GreaterThanCondition& condition)
{
    startVertex("GreaterThanCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::GreaterEqualCondition& condition)
{
    startVertex("GreaterEqualCondition");
    condition.left->accept(*this);
    condition.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::AdditionExpression& expression)
{
    startVertex("AdditionExpression");
    expression.left->accept(*this);
    expression.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::SubtractionExpression& expression)
{
    startVertex("SubtractionExpression");
    expression.left->accept(*this);
    expression.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::MultiplicationExpression& expression)
{
    startVertex("MultiplicationExpression");
    expression.left->accept(*this);
    expression.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::DivisionExpression& expression)
{
    startVertex("DivisionExpression");
    expression.left->accept(*this);
    expression.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::NegationExpression& expression)
{
    startVertex("NegationExpression");
    expression.right->accept(*this);
    endVertex();
}

void DotGenerator::visit(Ast::Identifier& identifier)
{
    startVertex("Identifier");

    startVertex(identifier.name.c_str(), "box");
    endVertex();

    endVertex();
}

void DotGenerator::visit(Ast::Number& number)
{
    startVertex("Number");

    startVertex(number.value, "box");
    endVertex();

    endVertex();
}

void DotGenerator::startVertex(const char* name)
{
    startUnlinkedVertex(name);
    addEdgeToParent();
}

void DotGenerator::startVertex(const char* name, const char* shape)
{
    startUnlinkedVertex(name, shape);
    addEdgeToParent();
}

void DotGenerator::startVertex(const int value, const char* shape)
{
    startUnlinkedVertex(value, shape);
    addEdgeToParent();
}

void DotGenerator::startUnlinkedVertex(const char* name)
{
    stack.push_back(id);
    out << id++ << " [label=\"" << name << "\"];\n";
}

void DotGenerator::startUnlinkedVertex(const char* name, const char* shape)
{
    stack.push_back(id);
    out << id++ << " [label=\"" << name << "\" shape=" << shape << "];\n";
}

void DotGenerator::startUnlinkedVertex(const int value, const char* shape)
{
    stack.push_back(id);
    out << id++ << " [label=\"" << value << "\" shape=" << shape << "];\n";
}

void DotGenerator::endVertex()
{
    stack.pop_back();
}

void DotGenerator::addEdgeToParent()
{
    out << *(stack.end() - 2) << " -> " << *(stack.end() - 1) << ";\n";
}

} // namespace PL0
