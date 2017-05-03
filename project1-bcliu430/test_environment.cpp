#include "catch.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <typeinfo>
#include "environment.hpp"

TEST_CASE("Test and or not procedure", "[Environemnt]"){

  {
      Environment env;

      string AND = "and";
      Expression root(AND);

      root.pushleaf(true);
      root.pushleaf(true);
      root.pushleaf(true);


      Expression expression = env.And(root);
      Expression True (true);
      bool ok = (expression == True);
      REQUIRE(ok == true);


      root.pushleaf(false);
      expression = env.And(root);
      Expression False(false);
      ok = (expression == False);
      REQUIRE(ok == true);

  }
  {
      Environment env;

      string OR = "or";
      Expression root(OR);

      root.pushleaf(false);
      root.pushleaf(false);
      root.pushleaf(false);

      Expression expression = env.Or(root);
      Expression False (false);
      bool ok = (expression == False);
      REQUIRE(ok == true);

      root.pushleaf(true);
      expression = env.Or(root);
      Expression True(true);
      ok = (expression == True);
      REQUIRE(ok == true);

  }
  {
      Environment env;

      string NOT = "not";
      Expression root(NOT);

      root.pushleaf(true);

      Expression expression = env.Not(root);
      Expression False(false);
      bool ok = (expression == False);
      REQUIRE(ok == true);

  }
  {
      Environment env;

      string NOT = "not";
      Expression root(NOT);

      root.pushleaf(false);

      Expression expression = env.Not(root);
      Expression True(true);
      bool ok = (expression == True);
      REQUIRE(ok == true);

  }
}

TEST_CASE("Test Comparison procedure", "[Environemnt]"){
  {
  Environment env;

  string Operator = "<";
  Expression root(Operator);
  root.pushleaf(5.3);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok == false);
  }

  {
  Environment env;

  string Operator = ">";
  Expression root(Operator);
  root.pushleaf(5.3);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok == true);
  }

  {
  Environment env;

  string Operator = "<=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok == true);

  }

  {
  Environment env;

  string Operator = ">=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok == true);
  }
  {
  Environment env;

  string Operator = "=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok == true);
  }
}

TEST_CASE("Test + and * case", "[Environment]"){

  {
  Environment env;

  string Operator = "+";
  Expression root(Operator);

  root.pushleaf(1.5);
  root.pushleaf(2.5);
  root.pushleaf(3.5);
  root.pushleaf(4.5);
  Expression expression = env.m_ary(root);
  Expression sum(12.0);
  bool ok = (expression == sum);
  REQUIRE(ok == true);
  }
  {
  Environment env;

  string Operator = "*";
  Expression root(Operator);

  root.pushleaf(1.5);
  root.pushleaf(2.5);
  root.pushleaf(3.5);
  root.pushleaf(4.5);

  Expression expression = env.m_ary(root);
  Expression product(59.0625);
  bool ok = (expression == product);
  REQUIRE(ok == true );
  }

}
TEST_CASE("Test minus and negate case", "[Environment]"){

  {
  Environment env;

  string Operator = "-";
  Expression root(Operator);

  root.pushleaf(1.5);
  Expression expression = env.minus(root);
  Expression Minus(-1.5);
  bool ok = (expression == Minus);
  REQUIRE(ok == true);
  }

  {
  Environment env;

  string Operator = "-";
  Expression root(Operator);

  root.pushleaf(3.5);
  root.pushleaf(1.5);
  Expression expression = env.minus(root);
  Expression Minus(2.);
  bool ok = (expression == Minus);
  REQUIRE(ok == true);
  }
}
TEST_CASE("Test division case", "[Environment]"){

  {
  Environment env;

  string Operator = "/";
  Expression root(Operator);

  root.pushleaf(1.5);
  root.pushleaf(1.5);
  Expression expression = env.division(root);
  Expression divi(1.);
  bool ok = (expression == divi);
  REQUIRE(ok == true);
  }
/*
  {
  Environment env;

  string Operator = "/";
  Expression root(Operator);

  root.pushleaf(1.5);
  root.pushleaf(0.0);
  Expression expression = env.division(root);
  REQUIRE_THROWS_AS(env.division(root),InterpreterSemanticError);
  }
*/
}
TEST_CASE("Test pi case", "[Environment]"){

  {
  Environment env;

  Expression expression = env.PI();
  Expression pi(atan2(0, -1));
  bool ok = (expression == pi);
  REQUIRE(ok == true);
  }
}

TEST_CASE("Test define case", "[Environment]"){

  {
  Environment env;
  Expression Def("define");
  string str = "a";
  Expression A (str);
  Expression num(3.5);
  Def.pushleaf(A);
  Def.pushleaf(num);

  Expression expression = env.Define(Def);
  Expression ans(3.5);
  bool ok = (expression == ans);
  REQUIRE(ok == true);
  }
}
/*
TEST_CASE("Test BEGIN case", "[Environment]"){

  {
  Environment env;
  Expression BEGIN("begin");
  Expression num1(3.5);
  Expression num2(3.);
  Expression num3(2.3);
  string A = "aa";
  string B = "bb";
  string C = "cc";
  Expression str1(A);
  Expression str2(B);
  Expression str3(C);

  str1.pushleaf(num1);
  str2.pushleaf(num2);
  str3.pushleaf(num3);
  BEGIN.pushleaf(str1);
  BEGIN.pushleaf(str2);
  BEGIN.pushleaf(str3);


  Expression expression = env.Begin(BEGIN);
  Expression ans(2.3);
  bool ok = (expression == num3);
  REQUIRE(ok == true);
  }
}
*/
TEST_CASE("Test IF case", "[Environment]"){

  {
  Environment env;
  Expression If("if");
  Expression T(true);
  Expression num1(3.5);
  Expression num2(3.);
  If.pushleaf(T);
  If.pushleaf(num1);
  If.pushleaf(num2);


  Expression expression = env.IF(If);
  Expression ans(3.5);
  bool ok = (expression == ans);
  REQUIRE(ok == true);
  }

  {
  Environment env;
  Expression If("if");
  Expression F(false);
  Expression num1(3.5);
  Expression num2(3.);
  If.pushleaf(F);
  If.pushleaf(num1);
  If.pushleaf(num2);


  Expression expression = env.IF(If);
  Expression ans(3.);
  bool ok = (expression == ans);
  REQUIRE(ok == true);
  }
}
