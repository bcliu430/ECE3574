#include "environment.hpp"

using namespace std;

Expression Environment::PI(){
    double pi = atan2(0, -1);
    Expression Pi(pi);
    return Pi;
}

Expression Environment::And(Expression expres){
    for (int i =0; i <expres.Leaf().size();i++) {
        Expression leaf = expres.getleaf(i);
        if(leaf.getExpression().type == BoolT){
            if(!leaf.getExpression().BoolV ){
                Expression expression_out(false);
                return expression_out;
            }
            Expression expression_out(true);

        }
        else{
              throw InterpreterSemanticError("Does not define");
        }
    }
    Expression expression_out(true);
    return expression_out;
}

Expression Environment::Or(Expression expres){
    for (int i =0; i <expres.Leaf().size();i++) {
        Expression leaf = expres.getleaf(i);
        if(leaf.getExpression().type == BoolT){
            if(leaf.getExpression().BoolV ){
                Expression expression_out(true);
                return expression_out;
            }
            Expression expression_out(false);
        }
        else{
              throw InterpreterSemanticError("Does not define");
        }
    }
    Expression expression_out(false);
    return expression_out;
}
Expression Environment::Not(Expression expres){
        if(expres.Leaf().size() != 1) {
          throw InterpreterSemanticError("Invalid number of argument");
        }
        else {
            Expression leaf = expres.getleaf(0);
            if(leaf.getExpression().type == BoolT){
                if(leaf.getExpression().BoolV ){
                    Expression expression_out(false);
                    return expression_out;
                }
                Expression expression_out(true);
                return expression_out;
                }
            throw InterpreterSemanticError("Does not define");
        }
}

Expression Environment::Comparison(Expression expres){
    if(expres.Leaf().size()!= 2){
      throw InterpreterSemanticError("Invalid number of argument");
    }
    else{
      string Operator = expres.getExpression().StringV;
      Expression arg1 = expres.getleaf(0);
      Expression arg2 = expres.getleaf(1);
      if(!(arg1.getExpression().type == DoubleT)){
          Expression arg_out = findInMap(arg1);
          if(arg1 == arg_out){
              throw InterpreterSemanticError("Invalid argument type");
          }
          else{
              arg1 = arg_out;
          }
      }
      if(!(arg2.getExpression().type == DoubleT)){
          Expression arg_out = findInMap(arg2);
          if(arg2 == arg_out){
              throw InterpreterSemanticError("Invalid argument type");
          }
          else {
              arg2 = arg_out;
          }
      }

      double num1 = arg1.getExpression().DoubleV;
      double num2 = arg2.getExpression().DoubleV;
      bool check;

      if(Operator == "<"){
          check = (num1<num2);
      }
      else if(Operator == "<="){
          check = (num1<=num2);
      }
      else if(Operator == ">"){
          check = (num1>num2);
      }
      else if(Operator == ">="){
          check = (num1>=num2);
      }
      else if(Operator == "="){
          check = (num1 == num2);
      }
      Expression expre(check);
      return expre;
  }

}

Expression Environment::m_ary(Expression expres){
    double result;
    if(expres.Leaf().size()== 0){
      throw InterpreterSemanticError("Invalid number of argument");
    }
    else{
      string Operator = expres.getExpression().StringV;
      if(Operator == "*")
          result = 1.0;
      if(Operator == "+")
          result = 0.0;
      for (int i = 0; i < expres.Leaf().size(); i++ ){
          Expression arg = expres.getleaf(i);
      if(!(arg.getExpression().type == DoubleT) ){
          Expression arg_out = findInMap(arg);
          if(arg_out == arg){
              throw InterpreterSemanticError("Invalid argument type");
          }
          else  {
            arg = arg_out;
            }
      }
      double num = arg.getExpression().DoubleV;
          if(Operator == "+")
              result += num;
          if(Operator == "*")
              result *= num;

      }

      Expression expre(result);
      return expre;
    }
}

Expression Environment::minus(Expression expres){
    if(expres.Leaf().size() != 1 && expres.Leaf().size() != 2){
      throw InterpreterSemanticError("too many arguments");
    }
    else if(expres.Leaf().size()== 1){
        Expression arg = expres.getleaf(0);
        double num = arg.getExpression().DoubleV;
        Expression expre(-num);
        return expre;
    }
    else if(expres.Leaf().size()== 2){
        Expression arg0 = expres.getleaf(0);
        Expression arg1 = expres.getleaf(1);
        double num0 = arg0.getExpression().DoubleV;
        double num1 = arg1.getExpression().DoubleV;

        Expression expre(num0-num1);
        return expre;
    }


}
Expression Environment::division(Expression expres){
    if(expres.Leaf().size() != 2){
      throw InterpreterSemanticError("Invalid number of argument");
    }
    else if(expres.Leaf().size()== 2){
        Expression arg0 = expres.getleaf(0);
        Expression arg1 = expres.getleaf(1);
        double num0 = arg0.getExpression().DoubleV;
        double num1 = arg1.getExpression().DoubleV;

        if(num1 == 0){
          throw InterpreterSemanticError("denominator cannot be 0");
        }

        Expression expre(num0/num1);
        return expre;
    }
}

Expression Environment::Define(Expression expres){
  if(expres.Leaf().size() != 2){
    throw InterpreterSemanticError("Invalid number of argument");
  }
  else{
    Expression arg0 = expres.getleaf(0);
    Expression arg1 = expres.getleaf(1);
    if(arg0.getExpression().type != StringT)
        throw InterpreterSemanticError("Invalid type.");


    string str = arg0.getExpression().StringV;
    if(str == "if" || str == "begin" || str == "define")
        throw InterpreterSemanticError("redefine special form.");
    else if (str == "pi")
        throw InterpreterSemanticError("redefine builtin symbol.");
    else {
      if (arg1.getExpression().type == DoubleT){
        double dou = arg1.getExpression().DoubleV;
        double_map[str] = dou;

        return dou;
      }
      if (arg1.getExpression().type == BoolT){
        bool TF = arg1.getExpression().BoolV;
        bool_map[str] = TF;

        return TF;
      }
      Expression arg_out = findInMap(arg1);
      if(arg1 == arg_out)
          throw InterpreterSemanticError("Invalid argument type");
      else
          arg1 = arg_out;

      if (arg1.getExpression().type == DoubleT){
        double dou = arg1.getExpression().DoubleV;
        double_map[str] = dou;

        return dou;
      }
      if (arg1.getExpression().type == BoolT){
        bool TF = arg1.getExpression().BoolV;
        bool_map[str] = TF;

        return TF;
      }

    }

  }
}

Expression Environment::Begin(Expression expres){
  if(expres.Leaf().size() == 0){
    throw InterpreterSemanticError("Invalid number of argument");
  }
  Expression lastone = expres.getleaf(expres.Leaf().size()-1);

  if(lastone.getExpression().type == DoubleT || lastone.getExpression().type == BoolT ){
      return lastone;
  }

    string last = lastone.getExpression().StringV;

    for( auto i = bool_map.begin(); i != bool_map.end(); ++i){
        if(i->first == last ){
            Expression e(i->second);
            return e;
        }
    }
    for(auto i = double_map.begin() ; i != double_map.end(); ++i){

        if(i->first == last ){
            Expression e(i->second);
            return e;
        }
    }

}

Expression Environment::IF(Expression expres){
  if(expres.Leaf().size() != 3){
    throw InterpreterSemanticError("Invalid number of argument");
  }
  else{
    Expression arg0 = expres.getleaf(0);

    Expression arg1 = expres.getleaf(1);
    Expression arg2 = expres.getleaf(2);
    if(arg0.getExpression().type != BoolT){
        throw InterpreterSemanticError("Invalid type.");
    }
    bool Bool = arg0.getExpression().BoolV;
    if(Bool){
      return arg1;
    }
    return arg2;

  }

}

Expression Environment::findInMap(Expression expres){
    if (expres.getExpression().type == StringT){
      string last = expres.getExpression().StringV;
      for( auto i = bool_map.begin(); i != bool_map.end(); ++i){
          if(i->first == last ){
              Expression e(i->second);
              return e;
          }
      }
      for(auto i = double_map.begin() ; i != double_map.end(); ++i){

          if(i->first == last ){
              Expression e(i->second);
              return e;
          }

      }
  }
  return expres;

}

Expression Environment::Trig(Expression expres){
    if( expres.Leaf().size()!= 1 || expres.getleaf(0).getExpression().type != DoubleT){
      throw InterpreterSemanticError("Invalid number of argument");
    }
    else{
        double ang = expres.getleaf(0).getExpression().DoubleV;
        if(expres.getExpression().StringV == "sin"){
            Expression e(sin(ang));
            return e;

        }
        if (expres.getExpression().StringV == "cos"){
            Expression e(cos(ang));
            return e;

        }
    }
}

Expression Environment::ATan(Expression expres){
    if(expres.Leaf().size() != 2 || expres.getleaf(0).getExpression().type != DoubleT || expres.getleaf(1).getExpression().type != DoubleT){
      throw InterpreterSemanticError("invalid argument number");
    }
    else{
        double y = expres.getleaf(0).getExpression().DoubleV;
        double x = expres.getleaf(1).getExpression().DoubleV;
        Expression e(atan2(y,x));
        return e;
    }
}

Expression Environment::Point(Expression expres){
    if(expres.Leaf().size()!= 2){
      throw InterpreterSemanticError("invalid argument number");
    }
    else {
        double x = expres.getleaf(0).getExpression().DoubleV;
        double y = expres.getleaf(1).getExpression().DoubleV;
        Expression e(std::make_tuple(x,y));
        return e;
        }
}

Expression Environment::Line(Expression expres){
  if(expres.Leaf().size()!= 2){
    throw InterpreterSemanticError("invalid argument number");
  }
  else {
      auto strat_tup_x = std::get<0>(expres.getleaf(0).getExpression().PointV);
      auto start_tup_y = std::get<1>(expres.getleaf(0).getExpression().PointV);
      auto end_tup_x = std::get<0>(expres.getleaf(1).getExpression().PointV);
      auto end_tup_y = std::get<1>(expres.getleaf(1).getExpression().PointV);
      Expression e(std::make_tuple(strat_tup_x,start_tup_y),std::make_tuple(end_tup_x, end_tup_y));
      return e;
      }
}

Expression Environment::Arc(Expression expres){
  if(expres.Leaf().size()!= 3){
    throw InterpreterSemanticError("invalid argument number");
  }
  else {
      auto arc_center_x = std::get<0>(expres.getleaf(0).getExpression().PointV);
      auto arc_center_y = std::get<1>(expres.getleaf(0).getExpression().PointV);
      auto arc_start_x = std::get<0>(expres.getleaf(1).getExpression().PointV);
      auto arc_start_y = std::get<1>(expres.getleaf(1).getExpression().PointV);
      auto arc_angle = expres.getleaf(2).getExpression().DoubleV;
      Expression e(std::make_tuple(arc_center_x,arc_center_y),std::make_tuple(arc_start_x, arc_start_y),arc_angle);
      return e;
      }
  }

Expression Environment::Draw(Expression expres){
  //    Expression e;
      return expres;
}
