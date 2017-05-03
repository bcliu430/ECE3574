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
        REQUIRE(!pair);
    }

    {
        std::string program = "(begin (define answer (+ 9 11)) (answer))  ()()()";
        std::istringstream iss(program);

        Tokenize t(iss);

        std::vector<std::string> vec = t.getToken();
        std::vector<std::string> vec2 = {"1"};
        bool pair = t.parePair();
        REQUIRE(pair);
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
       REQUIRE(node.getExpression().BoolV);
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
      REQUIRE(ok);
  }
  {
        std::string program = "(define (a) (1))";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(ok);
  }
  {
        std::string program = ")";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(!ok);
  }
  {
        std::string program = "(";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(!ok);
  }
  {
        std::string program = "";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(!ok);
  }
  {
        std::string program = "123))";
        std::istringstream iss(program);
        Interpreter i;
        bool ok = i.parse(iss);
        REQUIRE(!ok);
  }
}
