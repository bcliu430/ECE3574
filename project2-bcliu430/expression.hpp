#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include <vector>
#include <iostream>
#include <tuple>
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>

using namespace std;

typedef std::tuple<double, double> point;

enum atom_type {  //type
    NoneT,
    BoolT,
    DoubleT,
    StringT,
    PointT,
    LineT,
    ArcT};

struct Atom { //value
    atom_type type;
    bool BoolV;
    double DoubleV;
    string StringV;
    point PointV;
    point line_start;
    point line_end;
    point arc_center;
    point arc_start;
    double arc_angle;
};
class Expression {

public:
  // Default construct an Expression of type None
  Expression();

  // Construct an Expression with a single Boolean atom with value
  Expression(bool value);

  // Construct an Expression with a single Number atom with value
  Expression(double value);

  // Construct an Expression with a single Symbol atom with value
  Expression(const std::string & value);

  // Construct an Expression with a single Point atom with value
  Expression(std::tuple<double,double> value);

  // Construct an Expression with a single Line atom with starting
  // point start and ending point end
  Expression(std::tuple<double,double> start,
             std::tuple<double,double> end);

  // Construct an Expression with a single Arc atom with center
  // point center, starting point start, and spanning angle angle in radians
  Expression(std::tuple<double,double> center,
             std::tuple<double,double> start,
             double angle);

  void inExpression(Atom expres);

  Atom getExpression();

  // Equality operator for two Expressions, two expressions are equal if the have the same
  // type, atom value, and number of arguments
  bool operator== (const Expression & exp) const noexcept;

  void DisplayResult();

  void setleaf(Expression expres, uint32_t index);
  void pushleaf(Expression expres);
  vector<Expression> Leaf();
  Expression getleaf(uint32_t index);

private:
    Atom expres;
    vector<Expression> expression;
    vector<Expression> leaf;

};

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
   almost_equal(T x, T y, int ulp)
{
   // the machine epsilon has to be scaled to the magnitude of the values used
   // and multiplied by the desired precision in ULPs (units in the last place)
   return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
   // unless the result is subnormal
          || std::abs(x-y) < std::numeric_limits<T>::min();
}
#endif
