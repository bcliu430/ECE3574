#include "catch.hpp"
#include "expression.hpp"
#include "tokenize.hpp"
#include <string>
#include <iostream>

TEST_CASE("Test Expression constructor", "[Expression]"){
    {
        Expression e;
        REQUIRE(e.getExpression().type == NoneT);
    }
    {
        Expression e(false);
        REQUIRE(e.getExpression().type == BoolT);
        REQUIRE(e.getExpression().BoolV == false);
    }
    {
        Expression e(true);
        REQUIRE(e.getExpression().type == BoolT);
        REQUIRE(e.getExpression().BoolV == true);
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
      REQUIRE(ok == true);
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
      REQUIRE(ok == false);
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
        Expression b(double);
        bool boolean = (a == b);
        REQUIRE(boolean == false);
    }
}
