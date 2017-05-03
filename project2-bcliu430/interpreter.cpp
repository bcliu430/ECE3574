#include "interpreter.hpp"

using namespace std;

Interpreter::Interpreter(){ }

Interpreter::~Interpreter(){ }

bool Interpreter::parse(std::istream & expression) noexcept{

  Tokenize T(expression);
  if(T.AST()){
    root = T.getResult();
    boolmap = env.bool_map;
    doublemap = env.double_map;
  }
  else{
      return false;
  }
  return true;
}

Expression Interpreter::eval(){
  Tokenize t;
  if (root.Leaf().size() ==0){
    if(root.getExpression().type == StringT){
        string str = root.getExpression().StringV;/*
        if (boolmap.find(str) != boolmap.end()) {
            bool B = boolmap[str];
            Expression ans(B);
            return ans;
        }
        else if (doublemap.find(str) != doublemap.end()){
            double d = doublemap[str];
            Expression ans(d);
            return ans;
        }
        else */if (str == "pi"){
            Expression ans = env.PI();
            return ans;
        }
    }
  }
  Expression ans = t.postordertraversal(root);
  return ans;
}
