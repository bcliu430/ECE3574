#include "catch.hpp"

#include <string>
#include <iostream>

#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter.hpp"

TEST_CASE("Test tokenize constructor", "[Tokenize]"){
    {
        std::string program = "(begin (define answer (+ 9 11)) (answer))";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        vector<string> vec2 = {"(","begin", "(", "define",  "answer", "(", "+", "9", "11", ")",")","(","answer",")",")"};
        REQUIRE(vec.size() == 15);
        REQUIRE(vec == vec2);
    }
    {
        std::string program = "(begin (define answer 42)\n(answer))";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        vector<string> vec2 = {"(","begin", "(", "define",  "answer", "42", ")","(" , "answer",")",")"};
        REQUIRE(vec.size() == 11);
        REQUIRE(vec == vec2);
    }

    {
        std::string program = ";this is a comment\n(begin (define answer (+ 9 11)) (answer))";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 15);
    }

}

TEST_CASE("Test tokenize eraseComments function", "[Tokenize]"){


    {
        Tokenize t;
        std::string str = ";this is a comment\n(begin (define answer (+ 9 11)) (answer))\n;hahahah\n;hahahah\n;hahahah\n;hahahah\n;hahahah\n";
        std::string temp = t.deleteComments(str);
        REQUIRE(temp == "(begin (define answer (+ 9 11)) (answer))\n");
    }

    {
        Tokenize t;
        std::string str = ";this is a comment\n(begin (define answer (+ 9 11)) (answer)) ;hahahah\n ()()();define this\n";
        std::string temp = t.deleteComments(str);
        REQUIRE(temp == "(begin (define answer (+ 9 11)) (answer))  ()()()");
    }
}

TEST_CASE("Test parenthesis in pair", "[Tokenize]"){
    {
        std::string program = "( )))";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        std::vector<std::string> vec2 = {"1"};
        bool pair = t.parePair();
        REQUIRE(pair == false);
    }

    {
        std::string program = "(begin (define answer (+ 9 11)) (answer))  ()()()";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        std::vector<std::string> vec2 = {"1"};
        bool pair = t.parePair();
        REQUIRE(pair == true);
    }
}

TEST_CASE("Test data type return", "[Tokenize]"){
    {
       Tokenize t;
	     atom_type trueT = t.DataType("True");
       atom_type flaseT = t.DataType("False");
       REQUIRE(trueT == BoolT);
       REQUIRE(flaseT == BoolT);
    }
    {
       Tokenize t;
	     atom_type d = t.DataType("12.3");
       REQUIRE(d == DoubleT);
    }
    {
       Tokenize t;
	     atom_type str = t.DataType("advada");
       REQUIRE(str == StringT);
    }
    {
       Tokenize t;
	     atom_type none = t.DataType("");
       REQUIRE(none == NoneT);
    }
}

TEST_CASE("newnode function test", "[Tokenize]"){
    {
       Tokenize t;
       string expres = "True";
	     Expression node = t.newnode(expres);
       REQUIRE(node.getExpression().type == BoolT);
       REQUIRE(node.getExpression().BoolV == true);
    }
    {
       Tokenize t;
       string expres = "35.74";
	     Expression node = t.newnode(expres);
       REQUIRE(node.getExpression().type == DoubleT);
       REQUIRE(node.getExpression().DoubleV == 35.74);
    }
    {
       Tokenize t;
       string expres = "begin";
	     Expression node = t.newnode(expres);
       REQUIRE(node.getExpression().type == StringT);
       REQUIRE(node.getExpression().StringV == "begin" );
    }

}

TEST_CASE( "Test tokenize BuildAST", "[Tokenize]" ) {
  {
      string program = "(begin (define a 1) (define b pi))";
      istringstream iss(program);
      Interpreter i;
      bool ok = i.parse(iss);
      REQUIRE(ok == true);
  }
  {
        std::string program = "(define (a) (1))";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(ok == true);
  }
  {
        std::string program = ")";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(ok == false);
  }
  {
        std::string program = "(";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(ok == false);
  }
  {
        std::string program = "";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(ok == false);
  }
}
/*
TEST_CASE("Test Postorder traversal", "[Tokenize]"){
      {
          string s0 = "begin";
          string s1 = "define";
          string s2 = "a";
          string s3 = "b";
          string s4 = "+";
          double d0 = 1.0;
          double d1 = 2.0;

          Expression E_Begin(s0);
          Expression E_Define1(s1);
          Expression E_Define2(s1);
          Expression E_a(s2);
          Expression E_b(s3);

          Expression a(d0);
          Expression b(d1);
          Expression plus(s4);

          E_b.pushleaf(b); //b
          E_Define2.pushleaf(E_b);   //2
          E_a.pushleaf(a); //a
          E_Define1.pushleaf(E_a);   //1
          plus.pushleaf(E_Define1);
          plus.pushleaf(E_Define2);
          E_Begin.pushleaf(plus);

          Tokenize t;
          Expression ee = t.postordertraversal(E_Begin);

          REQUIRE(1);
      }

}
*/
