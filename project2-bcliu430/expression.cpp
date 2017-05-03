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

Expression::Expression(std::tuple<double,double> value){
    expres.type = PointT;
    expres.PointV = value;
}

Expression::Expression(std::tuple<double,double> start,
        std::tuple<double,double> end){
    expres.type = LineT;
    expres.line_start = start ;
    expres.line_end = end;
}

Expression::Expression(std::tuple<double,double> center,
           std::tuple<double,double> start,
           double angle){
    expres.type = ArcT;
    expres.arc_center = center ;
    expres.arc_start = start;
    expres.arc_angle = angle;
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
    else if (expres.type == PointT){
        this -> expres.type = PointT;
        this -> expres.PointV = expres.PointV;
    }
    else if (expres.type == LineT){
        this -> expres.type = LineT;
        this -> expres.line_start = expres.line_start;
        this -> expres.line_end = expres.line_end;
    }
    else if (expres.type == ArcT){
        this -> expres.type = ArcT;
        this -> expres.arc_center = expres.arc_center;
        this -> expres.arc_start = expres.arc_start;
        this -> expres.arc_angle = expres.arc_angle;
    }

}
Atom Expression::getExpression(){
    return expres;
}

bool Expression::operator== (const Expression &exp) const noexcept{
    if(this->expres.type!= exp.expres.type)
        return false;
    if( (this->expres.type == BoolT) &&
       (this->expres.BoolV != exp.expres.BoolV) )
        return false;
    if (this->expres.type == DoubleT &&
        !(almost_equal(this->expres.DoubleV, exp.expres.DoubleV, 1)) )
        return false;

    if( (this->expres.type == StringT) &&
       (this->expres.StringV != exp.expres.StringV) )
        return false;
    if( (this->expres.type == PointT) &&
       (this->expres.PointV != exp.expres.PointV) )
        return false;
    if( (  this->expres.type == LineT) &&
       ( (this->expres.line_start != exp.expres.line_start) ||
       (  this->expres.line_end != exp.expres.line_end)) )
        return false;
   if( (  this->expres.type == ArcT) &&
       ( (this->expres.arc_center != exp.expres.arc_center ) ||
       (  this ->expres.arc_start != exp.expres.arc_start  )  ||
       (  this ->expres.arc_angle != exp.expres.arc_angle  ) ))
        return false;

   if(this->leaf.size() != exp.leaf.size())
        return false;

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
    else if (expres.type == PointT){
        std::tuple <double,double> pnt;
        pnt = expres.PointV;
        double x = std::get<0>(pnt);
        double y = std::get<1>(pnt);
        cout<< x << ',' << y;
    }
    else if (expres.type == LineT){
        std::tuple <double,double> start_pnt;
        std::tuple <double,double> end_pnt;

        start_pnt = expres.line_start;
        end_pnt = expres.line_end;

        double x_start = std::get<0>(start_pnt);
        double y_start = std::get<1>(start_pnt);
        double x_end = std::get<0>(end_pnt);
        double y_end = std::get<1>(end_pnt);
        cout<< '(' << x_start << ',' << y_start << ")(" << x_end << ',' << y_end << ')';
    }
    else if (expres.type == ArcT){
        std::tuple <double,double> center_pnt;
        std::tuple <double,double> start_pnt;

        center_pnt = expres.arc_center;
        start_pnt = expres.arc_start;
        double x_center = std::get<0>(center_pnt);
        double y_center = std::get<1>(center_pnt);
        double x_start = std::get<0>(start_pnt);
        double y_start = std::get<1>(start_pnt);
        double ang = expres.arc_angle;
        cout << '('<< x_center <<',' <<y_center << ")(" << x_start<<','<< y_start <<')' <<ang;

    }
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
