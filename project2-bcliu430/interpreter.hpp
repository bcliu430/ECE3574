#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "expression.hpp"
#include "tokenize.hpp"

class Interpreter{

public:
    Interpreter();

    ~Interpreter();

    bool parse(std::istream &expression) noexcept;
    Expression eval();
    Expression root;

private:
    vector<string> token;
    Environment env;
    unordered_map<string,bool> boolmap;
    unordered_map<string,double> doublemap;
};
#endif
