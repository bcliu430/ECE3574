#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Point
{
  double x;
  double y;
};

std::ostream& operator <<(std::ostream& stream, const Point& p)
{
  stream << "(" << p.x << ", " << p.y << ")";
  return stream;
}

class Shape
{
public:
  Shape(){}

  virtual ~Shape(){};
  
  virtual void print(){
    std::cout << "Shape" << std::endl;
  }
  
private:
  
};

class Line: public Shape
{
public:
  Line(){
    start.x = 0.0; start.y = 0.0;
    end.x = 0.0; end.y = 0.0;
  }
  
  void print(){
    std::cout << "Line from " << start << " to " << end << std::endl;
  }
  
private:
  Point start, end;
};

class Circle: public Shape
{
public:
  Circle(){
    center.x = 0.0; center.y = 0.0;
    radius = 0.0;
  }
  
  void print(){
    std::cout << "Circle centered at " << center << " with radius " << radius << std::endl;
  }
  
private:
  Point center;
  double radius;
};


class ShapeFactory
{
public:
  enum ShapeType {UNKNOWN, LINE, CIRCLE};
  Shape * New(ShapeType type){
    switch(type)
      {
      case LINE:
	return new Line();
      case CIRCLE:
	return new Circle();
      default:
	assert(false && "Unknown Shape Type in Factory");      }
  }

  ShapeFactory(){ // build the mapping from strings to enums
    mapping["line"] = LINE;
    mapping["circle"] = CIRCLE;
  }
  
  ShapeType lookup(std::string str){
    std::map<std::string, ShapeType>::iterator it = mapping.find(str);
    if(it != mapping.end()) return it->second;
    else return UNKNOWN;
  }
  
private:
  std::map<std::string, ShapeType> mapping;
};

// Example:
// build some default shapes using the factory
// based on user input string
// (could come from anywhere, e.g. a menu callback/signal or file)
void read_user_input()
{
  std::vector<Shape *> shapes;
  ShapeFactory shape_maker;

  std::string input;
  do{
    std::getline(std::cin, input);

    ShapeFactory::ShapeType stype = shape_maker.lookup(input);
    if(stype != ShapeFactory::UNKNOWN){
      shapes.push_back(shape_maker.New(stype));
    }
  } while( !input.empty() );

  // print them
  for( auto it: shapes) it->print();
  
  // cleanup
  for( auto it: shapes) delete it;  
}

int main()
{
  read_user_input();
  
  return 0;
}

  
