#include "Evaluator.hpp"

#include <boost/range/adaptors.hpp>
#include <sstream>

namespace PL0 {

void Evaluator::visit(Ast::Program& program)
{
    program.block->accept(*this);
}

void Evaluator::visit(Ast::Block& block)
{
    for (auto& constant : block.constants) {
        constant->accept(*this);
    }

    for (auto& variable : block.variables) {
        auto& scope = scopes.back();
        scope.variables.emplace(variable->name, 0);
    }

    for (auto& procedure : block.procedures) {
        auto& scope = scopes.back();
        scope.procedures.emplace(procedure->identifier->name, *procedure);
    }

    block.statement->accept(*this);
}

void Evaluator::visit(Ast::Constant& constant)
{
    auto& scope = scopes.back();
    scope.constants.emplace(constant.identifier->name, constant.number->value);
}

void Evaluator::visit(Ast::Procedure& procedure)
{
    scopes.emplace_back();
    procedure.block->accept(*this);
    scopes.pop_back();
}

void Evaluator::visit(Ast::AssignmentStatement& statement)
{
    for (auto& scope : boost::adaptors::reverse(scopes)) {
        auto it = scope.variables.find(statement.left->name);
        if (it != scope.variables.end()) {
            statement.right->accept(*this);
            it->second = stack.top();
            return;
        }
    }

    std::ostringstream stream;
    stream << "unrecognized variable name \"" << statement.left->name << "\" during assignment";
    throw std::runtime_error(stream.str());
}

void Evaluator::visit(Ast::CallStatement& statement)
{
    for (const auto& scope : boost::adaptors::reverse(scopes)) {
        auto it = scope.procedures.find(statement.callee->name);
        if (it != scope.procedures.end()) {
            it->second.get().accept(*this);
            return;
        }
    }

    std::ostringstream stream;
    stream << "unrecognized procedure name \"" << statement.callee->name << "\" during call";
    throw std::runtime_error(stream.str());
}

void Evaluator::visit(Ast::ReadStatement& statement)
{
    for (auto& scope : boost::adaptors::reverse(scopes)) {
        auto it = scope.variables.find(statement.identifier->name);
        if (it != scope.variables.end()) {
            int value;
            out << "> ";
            in >> value;
            it->second = value;
            return;
        }
    }

    std::ostringstream stream;
    stream << "unrecognized variable name \"" << statement.identifier->name << "\" during read";
    throw std::runtime_error(stream.str());
}

void Evaluator::visit(Ast::WriteStatement& statement)
{
    statement.expression->accept(*this);
    out << stack.top() << '\n';
}

void Evaluator::visit(Ast::BeginStatement& statement)
{
    for (auto& child : statement.children) {
        child->accept(*this);
    }
}

void Evaluator::visit(Ast::IfStatement& statement)
{
    statement.condition->accept(*this);
    if (consequence) {
        statement.consequent->accept(*this);
    }
}

void Evaluator::visit(Ast::WhileStatement& statement)
{
    statement.condition->accept(*this);
    while (consequence) {
        statement.consequent->accept(*this);
        statement.condition->accept(*this);
    }
}

void Evaluator::visit(Ast::OddCondition& condition)
{
    condition.right->accept(*this);
    consequence = stack.top() & 1;
    stack.pop();
}

void Evaluator::visit(Ast::EqualCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() == right;
    stack.pop();
}

void Evaluator::visit(Ast::NotEqualCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() != right;
    stack.pop();
}

void Evaluator::visit(Ast::LessThanCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() < right;
    stack.pop();
}

void Evaluator::visit(Ast::LessEqualCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() <= right;
    stack.pop();
}

void Evaluator::visit(Ast::GreaterThanCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() > right;
    stack.pop();
}

void Evaluator::visit(Ast::GreaterEqualCondition& condition)
{
    condition.left->accept(*this);
    condition.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    consequence = stack.top() >= right;
    stack.pop();
}

void Evaluator::visit(Ast::AdditionExpression& expression)
{
    expression.left->accept(*this);
    expression.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    stack.top() += right;
}

void Evaluator::visit(Ast::SubtractionExpression& expression)
{
    expression.left->accept(*this);
    expression.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    stack.top() -= right;
}

void Evaluator::visit(Ast::MultiplicationExpression& expression)
{
    expression.left->accept(*this);
    expression.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    stack.top() *= right;
}

void Evaluator::visit(Ast::DivisionExpression& expression)
{
    expression.left->accept(*this);
    expression.right->accept(*this);

    const auto right = stack.top();
    stack.pop();
    stack.top() /= right;
}

void Evaluator::visit(Ast::NegationExpression& expression)
{
    expression.right->accept(*this);
    stack.top() = -stack.top();
}

void Evaluator::visit(Ast::Identifier& identifier)
{
    for (const auto& scope : boost::adaptors::reverse(scopes)) {
        const auto constantIt = scope.constants.find(identifier.name);
        if (constantIt != scope.constants.end()) {
            stack.push(constantIt->second);
            return;
        }

        const auto variableIt = scope.variables.find(identifier.name);
        if (variableIt != scope.variables.end()) {
            stack.push(variableIt->second);
            return;
        }
    }

    std::ostringstream stream;
    stream << "unrecognized symbol name \"" << identifier.name << '"';
    throw std::runtime_error(stream.str());
}

void Evaluator::visit(Ast::Number& number)
{
    stack.push(number.value);
}

} // namespace PL0
