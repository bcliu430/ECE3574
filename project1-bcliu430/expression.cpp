#include "expression.hpp"
#include <vector>
#include <cstddef>
#include <stdexcept>

Expression::Expression(){
    expres.type = NoneT;
}

Expression::Expression(bool value){
    expres.type = BoolT;
    expres.BoolV = value;
}

Expression::Expression(double value){
    expres.type = DoubleT;
    expres.DoubleV = value;
}

Expression::Expression(const std::string &value){
    expres.type = StringT;
    expres.StringV = value;
}
void Expression::inExpression(Atom expres){

    if(expres.type == BoolT){
        this -> expres.type = BoolT;
        this -> expres.BoolV = expres.BoolV;
    }
    else if(expres.type == DoubleT){
        this -> expres.type = DoubleT;
        this -> expres.DoubleV = expres.DoubleV;
    }
    else if(expres.type == StringT){
        this -> expres.type = StringT;
        this -> expres.StringV = expres.StringV;
    }

}
Atom Expression::getExpression(){
    return expres;
}

bool Expression::operator== (const Expression &exp) const noexcept{
    if(this->expres.type!= exp.expres.type)
        return false;
    else if( (this->expres.type == BoolT) &&
             (this->expres.BoolV != exp.expres.BoolV) )
        return false;
    else if( (this->expres.type == DoubleT) &&
             (this->expres.DoubleV != exp.expres.DoubleV) )
        return false;
    else if( (this->expres.type == StringT) &&
             (this->expres.StringV != exp.expres.StringV) )
        return false;
    else if(this->leaf.size() != exp.leaf.size())
        return false;
    else
         return true;

}

void Expression::DisplayResult(){
    if(expres.type == BoolT){
        if(expres.BoolV == true)
            cout << "True";
        else
            cout << "FaLse";
    }
    else if (expres.type == DoubleT)
        cout <<  expres.DoubleV;
    else if (expres.type == StringT)
        cout <<  expres.StringV;
    else {}
}

void Expression::setleaf(Expression expres, uint32_t index){
    expression[index] = expres;
}

void Expression::pushleaf(Expression expres){
    expression.push_back(expres);
}

vector<Expression> Expression::Leaf(){
    return expression;
}

Expression Expression::getleaf(uint32_t index){
    return expression[index];
}
