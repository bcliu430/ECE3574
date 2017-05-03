#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter.hpp"
using namespace std;

class Tokenize{

public:
  //default constructor
  Tokenize();

  //default destructor
  ~Tokenize();

  //constructor with input
  Tokenize(std::istream & expression);

  vector<string> setToken(string &expression);


  //get private token vector
  vector<std::string> getToken();

  //find the location of certain character in a string
  int findChar(std::string str, char charin);

  //erase comments
  std::string deleteComments(string &str);

  bool AST();

  // check parenthesis in pair
  bool parePair();

  Expression createAST(Expression expression);
  Expression newnode(string expres);


  atom_type DataType(string expression);

  Expression postordertraversal(Expression expression);
  Expression getResult(); 
private:
    vector <string> token;
    Expression root;
    Environment env;

};

#endif
