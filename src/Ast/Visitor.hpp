#ifndef PL0_AST_VISITOR_HPP
#define PL0_AST_VISITOR_HPP

namespace PL0 {
namespace Ast {

struct Program;
struct Block;
struct Constant;
struct Procedure;
struct AssignmentStatement;
struct CallStatement;
struct ReadStatement;
struct WriteStatement;
struct BeginStatement;
struct IfStatement;
struct WhileStatement;
struct OddCondition;
struct EqualCondition;
struct NotEqualCondition;
struct LessThanCondition;
struct LessEqualCondition;
struct GreaterThanCondition;
struct GreaterEqualCondition;
struct AdditionExpression;
struct SubtractionExpression;
struct MultiplicationExpression;
struct DivisionExpression;
struct NegationExpression;
struct Identifier;
struct Number;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(Program& program) = 0;
    virtual void visit(Block& block) = 0;
    virtual void visit(Constant& constant) = 0;
    virtual void visit(Procedure& procedure) = 0;
    virtual void visit(AssignmentStatement& statement) = 0;
    virtual void visit(CallStatement& statement) = 0;
    virtual void visit(ReadStatement& statement) = 0;
    virtual void visit(WriteStatement& statement) = 0;
    virtual void visit(BeginStatement& statement) = 0;
    virtual void visit(IfStatement& statement) = 0;
    virtual void visit(WhileStatement& statement) = 0;
    virtual void visit(OddCondition& condition) = 0;
    virtual void visit(EqualCondition& condition) = 0;
    virtual void visit(NotEqualCondition& condition) = 0;
    virtual void visit(LessThanCondition& condition) = 0;
    virtual void visit(LessEqualCondition& condition) = 0;
    virtual void visit(GreaterThanCondition& condition) = 0;
    virtual void visit(GreaterEqualCondition& condition) = 0;
    virtual void visit(AdditionExpression& expression) = 0;
    virtual void visit(SubtractionExpression& expression) = 0;
    virtual void visit(MultiplicationExpression& expression) = 0;
    virtual void visit(DivisionExpression& expression) = 0;
    virtual void visit(NegationExpression& expression) = 0;
    virtual void visit(Identifier& identifier) = 0;
    virtual void visit(Number& number) = 0;
};

} // namespace Ast
} // namespace PL0

#endif // PL0_AST_VISITOR_HPP
