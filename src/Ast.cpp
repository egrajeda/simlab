#include <iostream>
#include <string>
#include <sstream>

#include "Ast.h"

// 
// AstNode
//

inline std::ostream& operator<< (std::ostream& out, const AstNode& node)
{
    node.printOn(out);
    return out;
}

//
// AstExpression
//

void AstExpression::printOn(std::ostream& out) const
{
    out << "[(E)]";
}

//
// AstInteger
//

AstInteger::AstInteger(int value) : m_value(value)
{ }

void AstInteger::printOn(std::ostream& out) const
{
    out << "[(1)" << m_value << "]";
}

// 
// AstIdentifier
//

AstIdentifier::AstIdentifier(const std::string& name) : m_name(name)
{ }

void AstIdentifier::printOn(std::ostream& out) const
{
    out << "[(I)" << m_name << "]";
}

//
// AstAssignment
//

AstAssignment::AstAssignment(AstIdentifier& identifier, 
    AstExpression& expression) : m_identifier(identifier), 
    m_expression(expression)
{ }

void AstAssignment::printOn(std::ostream& out) const
{
    out << "[(=)" << m_identifier << "," << m_expression << "]";
}

//
// AstBinaryOperator
//

AstBinaryOperator::AstBinaryOperator(AstExpression& left, char op,
    AstExpression& right) : m_left(left), m_operator(op), m_right(right) 
{ }

void AstBinaryOperator::printOn(std::ostream& out) const
{
    out << "[(+)" << m_left << "," << m_operator << "," << m_right << "]";
}

//
// AstFunctionCall
//

AstFunctionCall::AstFunctionCall(AstIdentifier& identifier, 
    AstArguments& arguments) : m_identifier(identifier), m_arguments(arguments)
{ }

void AstFunctionCall::printOn(std::ostream& out) const
{
    out << "[(F)" << m_identifier << "," << m_arguments << "]";
}

//
// AstArguments
//
AstArguments::AstArguments(AstExpression* expression)
{
    if (expression) {
        add(expression);
    }
}

void AstArguments::add(AstExpression* expression)
{
    m_expressions.push_back(expression);
}

void AstArguments::printOn(std::ostream& out) const
{
    out << "[(A)";
    std::vector<AstExpression*>::const_iterator it = m_expressions.begin();
    for (it; it != m_expressions.end(); ++it) {
        out << *(*it) << ",";
    }
    if (m_expressions.size() > 0) {
        out << "\b";
    }
    out << "]";
}

//
// Ast
//

Ast::Ast(AstExpression& expression) : m_expression(expression)
{ }

void Ast::printOn(std::ostream& out) const
{
    out << "[" << m_expression << "]";
}

std::string Ast::toString() const
{
    std::stringstream out;
    printOn(out);
    return out.str(); 
}
