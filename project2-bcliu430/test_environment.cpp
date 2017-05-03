#include "catch.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <typeinfo>
#include "environment.hpp"

TEST_CASE("Test and procedure", "[Environemnt]"){

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
      REQUIRE(ok);


      root.pushleaf(false);
      expression = env.And(root);
      Expression False(false);
      ok = (expression == False);
      REQUIRE(ok);

  }
  {
      Environment env;
      string AND = "and";
      string str = "srt";

      Expression root(AND);
      root.pushleaf(str);
      REQUIRE_THROWS_AS(env.And(root), InterpreterSemanticError);


  }
}
TEST_CASE("Test or procedure", "[Environemnt]"){

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
      REQUIRE(ok);

      root.pushleaf(true);
      expression = env.Or(root);
      Expression True(true);
      ok = (expression == True);
      REQUIRE(ok);

  }
  {
      Environment env;
      string OR = "or";
      Expression root(OR);
      string str = "srt";
      root.pushleaf(str);

      REQUIRE_THROWS_AS(env.Or(root), InterpreterSemanticError);


  }
  {
      Environment env;

      string NOT = "not";
      Expression root(NOT);

      root.pushleaf(true);

      Expression expression = env.Not(root);
      Expression False(false);
      bool ok = (expression == False);
      REQUIRE(ok);

  }


}

TEST_CASE("test not procedure", "[Environemnt]"){
  {
      Environment env;

      string NOT = "not";
      Expression root(NOT);

      root.pushleaf(false);

      Expression expression = env.Not(root);
      Expression True(true);
      bool ok = (expression == True);
      REQUIRE(ok);

  }
  {
      Environment env;
      string NOT = "not";
      Expression root(NOT);
      string str = "srt";

      root.pushleaf(str);

      REQUIRE_THROWS_AS(env.Not(root), InterpreterSemanticError);

  }
  {
      Environment env;
      string NOT = "not";
      Expression root(NOT);
      REQUIRE_THROWS_AS(env.Not(root), InterpreterSemanticError);

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
  REQUIRE(!ok);  }
  {
  Environment env;
  string Operator = ">";
  Expression root(Operator);
  root.pushleaf(5.3);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok);  }
  {
  Environment env;
  string Operator = "<=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok);  }
  {
  Environment env;
  string Operator = ">=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok);  }
  {
  Environment env;
  string Operator = "=";
  Expression root(Operator);
  root.pushleaf(3.5);
  root.pushleaf(3.5);
  Expression expression = env.Comparison(root);
  Expression True(true);
  bool ok = (expression == True);
  REQUIRE(ok);  }
  {
  Environment env;
  string Operator = "=";
  Expression root(Operator);
  root.pushleaf(3.5);
  REQUIRE_THROWS_AS( env.Comparison(root),InterpreterSemanticError);  }
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
  REQUIRE(ok);
  }
  {
  Environment env;
  string Operator = "+";
  Expression root(Operator);
  REQUIRE_THROWS_AS(env.m_ary(root),InterpreterSemanticError);

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
  REQUIRE(ok);
  }
  {
  Environment env;
  string Operator = "*";
  Expression root(Operator);
  REQUIRE_THROWS_AS(env.m_ary(root),InterpreterSemanticError);

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
  REQUIRE(ok);
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
  REQUIRE(ok);
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
  REQUIRE(ok);
  }
  {
  Environment env;
  string Operator = "/";
  Expression root(Operator);
  root.pushleaf(1.5);
  root.pushleaf(0.);
  REQUIRE_THROWS_AS(env.division(root), InterpreterSemanticError);
  }
  {
  Environment env;
  string Operator = "/";
  Expression root(Operator);
  root.pushleaf(1.5);
  REQUIRE_THROWS_AS(env.division(root), InterpreterSemanticError);
  }

}
TEST_CASE("Test pi case", "[Environment]"){

  {
  Environment env;

  Expression expression = env.PI();
  Expression pi(atan2(0, -1));
  bool ok = (expression == pi);
  REQUIRE(ok);
  }
}

TEST_CASE("Test define case", "[Environment]"){

  {
  Environment env;
  string define = "define";
  Expression Def(define);
  string str = "a";
  Expression A (str);
  Expression num(3.5);
  Def.pushleaf(A);
  Def.pushleaf(num);

  Expression expression = env.Define(Def);
  Expression ans(3.5);
  bool ok = (expression == ans);
  REQUIRE(ok);
  }
  {
  Environment env;
  string define = "define";
  Expression Def(define);
  string str = "a";
  Expression A (str);
  Expression BL(true);
  Def.pushleaf(A);
  Def.pushleaf(BL);

  Expression expression = env.Define(Def);
  Expression ans(true);
  bool ok = (expression == ans);
  REQUIRE(ok);
  }
  {
  Environment env;
  string str = "define", str2 = "a";
  Expression root(str);

  root.pushleaf(str2);
  REQUIRE_THROWS_AS( env.Define(root),InterpreterSemanticError);
  }
  {
  Environment env;
  string str = "define", str2 = "if";
  Expression root(str);
  root.pushleaf(str2);
  root.pushleaf(str2);

  REQUIRE_THROWS_AS( env.Define(root),InterpreterSemanticError);
  }
  {
  Environment env;
  string str = "define", str2 = "pi";
  Expression root(str);
  root.pushleaf(str2);
  root.pushleaf(str2);
  REQUIRE_THROWS_AS( env.Define(root),InterpreterSemanticError);
  }
}

TEST_CASE("Test Begin case", "[Environment]"){

  {
  Environment env;
  string str = "begin";
  Expression root(str);
  REQUIRE_THROWS_AS( env.Begin(root),InterpreterSemanticError);
  }

}

TEST_CASE("Test IF case", "[Environment]"){

  {
  Environment env;
  string iff = "if";
  Expression If(iff);
  Expression T(true);
  Expression num1(3.5);
  Expression num2(3.);
  If.pushleaf(T);
  If.pushleaf(num1);
  If.pushleaf(num2);
  Expression expression = env.IF(If);
  Expression ans(3.5);
  bool ok = (expression == ans);
  REQUIRE(ok);
  }

  {
  Environment env;
  string iff = "if";
  Expression If(iff);
  Expression F(false);
  Expression num1(3.5);
  Expression num2(3.);
  If.pushleaf(F);
  If.pushleaf(num1);
  If.pushleaf(num2);


  Expression expression = env.IF(If);
  Expression ans(3.);
  bool ok = (expression == ans);
  REQUIRE(ok);
  }
  {
  Environment env;
  string iff = "if";
  Expression If(iff);
  string str = " 123";
  Expression F(str);
  If.pushleaf(F);
  REQUIRE_THROWS_AS(env.IF(If), InterpreterSemanticError);
  }
  {
  Environment env;
  string iff = "if";
  Expression If(iff);
  string str = " 123";
  Expression F(str);
  If.pushleaf(F);
  If.pushleaf(F);
  If.pushleaf(F);
  REQUIRE_THROWS_AS(env.IF(If), InterpreterSemanticError);
  }

}

TEST_CASE("Test trig function","[Environment]"){
    {
      Environment env;
      string str = "sin";
      Expression SIN(str);
      Expression num(atan2(0,-1));
      SIN.pushleaf(num);
      Expression e = env.Trig(SIN);
      Expression ans(sin(atan2(0,-1)));

      bool ok = (e == ans);
      REQUIRE(ok);

    }
    {
      Environment env;
      string str = "cos";
      Expression COS(str);
      Expression num(atan2(0,-1));
      COS.pushleaf(num);
      Expression e = env.Trig(COS);
      Expression ans(cos(atan2(0,-1)));

      bool ok = (e == ans);
      REQUIRE(ok);

    }
}
TEST_CASE("Test arctan function", "[Environment]"){
    {
        Environment env;
        string str = "arctan";
        Expression aTan(str);
        Expression num(1.);
        aTan.pushleaf(num);
        aTan.pushleaf(num);
        Expression e = env.ATan(aTan);
        Expression ans(atan2(0,-1)/4);
        bool ok = (e == ans);
        REQUIRE(ok);
    }
}

TEST_CASE("Test point", "Environment"){
    {
        Atom A;
        A.type = PointT;
        A.PointV = std::make_tuple(1.,2.);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,2.));
        bool ok = (e == ans);
        REQUIRE (ok);
    }
    {
        Atom A;
        A.type = PointT;
        A.PointV = std::make_tuple(1.,2.);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,3.));
        bool ok = (e == ans);
        REQUIRE (!ok);
    }
    {
        Environment env;
        string str = "point";
        double num  =1;
        Expression e (str);
        e.pushleaf(num);
        REQUIRE_THROWS_AS(env.Point(e), InterpreterSemanticError);


    }
}


TEST_CASE("Test line", "Environment"){
    {
        Atom A;
        A.type = LineT;
        A.line_start = std::make_tuple(1.,2.);
        A.line_end = std::make_tuple(1.,2.);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,2.),make_tuple(1.,2.));
        bool ok = (e == ans);
        REQUIRE (ok);
    }
    {
        Atom A;
        A.type = LineT;
        A.line_start = std::make_tuple(1.,2.);
        A.line_end = std::make_tuple(1.,2.);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,2.),make_tuple(1.,3.));
        bool ok = (e == ans);
        REQUIRE (!ok);
    }
    {
        Environment env;
        Expression e (std::make_tuple(1.,2.));
        REQUIRE_THROWS_AS(env.Line(e), InterpreterSemanticError);
    }
}
TEST_CASE("Test arc", "Environment"){
    {
        Atom A;
        A.type = ArcT;
        A.arc_center = std::make_tuple(1.,2.);
        A.arc_start = std::make_tuple(1.,2.);
        A.arc_angle = atan2(0,-1);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,2.),make_tuple(1.,2.), atan2(0,-1));
        bool ok = (e == ans);
        REQUIRE (ok);
    }
    {
        Atom A;
        A.type = ArcT;
        A.arc_center = std::make_tuple(1.,2.);
        A.arc_start = std::make_tuple(1.,2.);
        A.arc_angle = atan2(0,-1);
        Expression e;
        e.inExpression(A);
        Expression ans(make_tuple(1.,2.),make_tuple(2.,2.), atan2(0,-1));
        bool ok = (e == ans);
        REQUIRE (!ok);
    }
    {
        Environment env;
        Expression e (std::make_tuple(1.,2.));
        REQUIRE_THROWS_AS(env.Arc(e), InterpreterSemanticError);
    }
}
