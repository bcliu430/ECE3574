#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include <vector>
#include <iostream>

using namespace std;

enum atom_type {  //type
    NoneT,
    BoolT,
    DoubleT,
    StringT};

struct Atom { //value
    atom_type type;
    bool BoolV;
    double DoubleV;
    string StringV;
};
class Expression {

public:
  // Default construct an Expression of type None
  Expression();

  // Construct an Expression with a single Boolean atom with value
  Expression(bool value);

  // Construct an Expression with a single Number atom with value
  Expression(double value);

  // Construct an Expression with a single Symbol atom with value
  Expression(const std::string & value);

  void inExpression(Atom expres);

  Atom getExpression();

  // Equality operator for two Expressions, two expressions are equal if the have the same
  // type, atom value, and number of arguments
  bool operator== (const Expression & exp) const noexcept;

  void DisplayResult();

  void setleaf(Expression expres, uint32_t index);
  void pushleaf(Expression expres);
  vector<Expression> Leaf();
  Expression getleaf(uint32_t index);

private:
    Atom expres;
    vector<Expression> expression;
    vector<Expression> leaf;

};
#endif
