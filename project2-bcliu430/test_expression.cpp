#include "catch.hpp"
#include "expression.hpp"
#include "tokenize.hpp"
#include <string>
#include <iostream>
#include <tuple>
#include <sstream>

TEST_CASE("Test Expression constructor", "[Expression]"){
    {
        Expression e;
        REQUIRE(e.getExpression().type == NoneT);
    }
    {
        Expression e(false);
        REQUIRE(e.getExpression().type == BoolT);
        REQUIRE(!e.getExpression().BoolV);
    }
    {
        Expression e(true);
        REQUIRE(e.getExpression().type == BoolT);
        REQUIRE(e.getExpression().BoolV);
    }
    {
        std::string str = "this_is_a_test_string";
        Expression e(str);
        REQUIRE(e.getExpression().type == StringT);
        REQUIRE(e.getExpression().StringV == "this_is_a_test_string");
    }
    {
        double d = 35.74;
        Expression e(d);
        REQUIRE(e.getExpression().type == DoubleT);
        REQUIRE(e.getExpression().DoubleV == 35.74);
    }
    {
        tuple<double, double> t(std::make_tuple(0.,0.));
        Expression e(t);
        REQUIRE(e.getExpression().type == PointT);
        REQUIRE(e.getExpression().PointV == std::make_tuple(0., 0.));
    }
    {
        tuple<double, double> p1(std::make_tuple(0.,0.));
        tuple<double, double> p2(std::make_tuple(1.,1.));
        Expression e(p1,p2);
        REQUIRE(e.getExpression().type == LineT);
        REQUIRE(e.getExpression().line_start == std::make_tuple(0., 0.));
        REQUIRE(e.getExpression().line_end == std::make_tuple(1., 1.));

    }
    {
        tuple<double, double> p1(std::make_tuple(0.,0.));
        tuple<double, double> p2(std::make_tuple(1.,1.));
        Expression e(p1,p2, atan2(0,-1));
        REQUIRE(e.getExpression().type == ArcT);
        REQUIRE(e.getExpression().arc_center == std::make_tuple(0., 0.));
        REQUIRE(e.getExpression().arc_start == std::make_tuple(1., 1.));
        REQUIRE(e.getExpression().arc_angle == atan2(0,-1));


    }

}

TEST_CASE("Test == ", "[Expression]"){
    {
      string begin = "begin";
      string a     = "a";
      double d     = 3.14;
      Expression A(begin);
      Expression B(a);
      Expression C(d);
      A.pushleaf(B);
      A.pushleaf(C);
      string Begin = "begin";
      string aa     = "b";
      double dd     = 3.14;
      Expression AA(Begin);
      Expression BB(aa);
      Expression CC(dd);
      AA.pushleaf(BB);
      AA.pushleaf(CC);
      bool ok = (A == AA);
      REQUIRE(ok);
    }
    {
      string begin = "begin";
      string a     = "a";
      double d     = 3.14;
      Expression A(begin);
      Expression B(a);
      Expression C(d);
      A.pushleaf(B);
      A.pushleaf(C);
      string Begin = "define";
      string aa     = "b";
      double dd     = 3.14;
      Expression AA(Begin);
      Expression BB(aa);
      Expression CC(dd);
      AA.pushleaf(BB);
      AA.pushleaf(CC);
      bool ok = (A == AA);
      REQUIRE(!ok);
    }
    {
        std::string str = "define";
        Expression a(str);
        Expression b(str);
        bool boolean = (a == b);
        REQUIRE(boolean);
    }
    {
        std::string str = "define";
        double d = 3.14;
        Expression a(str);
        Expression b(d);
        bool boolean = (a == b);
        REQUIRE(!boolean);
    }
}

TEST_CASE("Test inexpression ", "[Expression]"){
      {
          Atom a;
          Expression e;
          a.type = NoneT;
          e.inExpression(a);
          REQUIRE(e.getExpression().type == NoneT);

      }
      {
          Atom a;
          Expression e;
          a.type = BoolT;
          a.BoolV = true;
          e.inExpression(a);
          Expression ee(true);
          REQUIRE(e.getExpression().type == BoolT);
          REQUIRE(e.getExpression().BoolV == ee.getExpression().BoolV);


      }
      {
          Atom a;
          Expression e;
          a.type = DoubleT;
          a.DoubleV = 2.2;
          e.inExpression(a);
          REQUIRE(e.getExpression().type == DoubleT);
          REQUIRE(e.getExpression().DoubleV == 2.2);


      }
      {
          Atom a;
          Expression e;
          a.type = StringT;
          a.StringV = "a";
          e.inExpression(a);
          REQUIRE(e.getExpression().type == StringT);
          REQUIRE(e.getExpression().StringV == "a");


      }
}
