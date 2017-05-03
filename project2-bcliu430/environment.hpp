#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <math.h>
#include <unordered_map>
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

using namespace std;

class Environment {

public:
    Expression PI();
    Expression And(Expression expres);
    Expression Or(Expression expres);
    Expression Not(Expression expres);
    Expression Comparison(Expression expres);
    Expression m_ary(Expression expres);
    Expression minus(Expression expres);
    Expression division(Expression expres);
    Expression Define(Expression expres);
    Expression Begin(Expression expres);
    Expression IF(Expression expres);
    Expression findInMap(Expression expres);
    Expression Trig(Expression expres);
    Expression ATan(Expression expres);
    Expression draw(Expression expres);
    Expression Point(Expression expres);
    Expression Line(Expression expres);
    Expression Arc(Expression expres);
    Expression Draw(Expression expres);
    unordered_map<string,bool> bool_map;
    unordered_map<string,double> double_map;

private:

};

#endif
