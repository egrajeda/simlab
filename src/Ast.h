#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>

class AstNode
{
  protected:
    virtual void printOn(std::ostream& out) const = 0;

  public:
    friend std::ostream& operator<< (std::ostream& out, const AstNode& node);
};

class AstExpression : public AstNode
{
  protected:
    virtual void printOn(std::ostream& out) const;
};

class AstInteger : public AstExpression
{
    int m_value;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstInteger(int value);
};

class AstIdentifier : public AstExpression
{
    std::string m_name;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstIdentifier(const std::string& name);
};

class AstAssignment : public AstExpression
{
    AstIdentifier& m_identifier;
    AstExpression& m_expression;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstAssignment(AstIdentifier& identifier, AstExpression& expression);
};

class AstBinaryOperator : public AstExpression
{
    char           m_operator;
    AstExpression& m_left;
    AstExpression& m_right;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstBinaryOperator(AstExpression& left, char op, AstExpression& right);
};

class AstArguments : public AstNode
{
    std::vector<AstExpression*> m_expressions;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstArguments(AstExpression* expression = NULL);
    void add(AstExpression* expression);
};

class AstFunctionCall : public AstExpression
{
    AstIdentifier& m_identifier;
    AstArguments&  m_arguments;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    AstFunctionCall(AstIdentifier& identifier, AstArguments& arguments);
};

struct Ast : public AstNode
{
    AstExpression& m_expression;

  protected:
    virtual void printOn(std::ostream& out) const;

  public:
    Ast(AstExpression& expression); 

    // toString
    //
    // Crea una representación textual de la estructura del AST.
    std::string toString() const;
};

#endif
