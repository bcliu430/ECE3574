#include "interpreter.hpp"

using namespace std;


Interpreter::Interpreter(){ }

Interpreter::~Interpreter(){ }

bool Interpreter::parse(std::istream & expression) noexcept{

  Tokenize T(expression);
  if(T.AST()){
    root = T.getResult();
    return true;
  }
  else
    return false;
}

Expression Interpreter::eval(){
  Tokenize t;
  Expression ans = t.postordertraversal(root);
  return ans;
}
