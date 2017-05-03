#ifndef OBJECTS_HPP
#define OBJECTS_HPP
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <string>
#include "parse.hpp"
#include "geometry.hpp"

struct color{
  int r,g,b;
  bool operator==(const color &c) const{
    return (this ->r == c.r && this ->g == c.g && this -> b == c.b);
  }

  color &operator= (const color &c) {
    this-> r = c.r;
    this-> g = c.g;
    this-> b = c.b;
    return *this;
  }
  color &operator+ (const color &c) {
    this-> r = this-> r + c.r;
    this-> g = this-> g + c.g;
    this-> b = this-> b + c.b;
    return *this;
  }
};

struct Cobject{
    struct coor cen;
    struct coor nor; // plane
    double radius; // sphere
    color Ccol;
    double lambert;
    std::string type;

    bool operator==(const Cobject & obj) const {
      return (this-> cen == obj.cen &&
      this-> nor == obj.nor &&
      this-> radius == obj.radius &&
      this-> Ccol == obj.Ccol &&
      this-> lambert == obj.lambert &&
      this-> type == obj.type);
    }
};



class objects{
public:
  objects(){ }
  ~objects(){ }
  objects(const QJsonObject &qj_obj, const std::string &obj_type);
  Cobject get_obj();

private:
  Cobject obj;
  int c_red, c_green, c_blue;

};
#endif
