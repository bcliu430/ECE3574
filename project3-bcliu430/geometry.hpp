#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <math.h>
#include <cmath>
#include <vector>
#include <QDebug>

struct coor{
  double x,y,z;
  bool operator==(const coor &c) const{
    return (this ->x == c.x && this ->y == c.y && this -> z == c.z);
  }

    coor operator=(const coor &c) {
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
    return *this;
  }

};

class geometry{
public:
  geometry(){ }
  ~geometry(){ }
  double dot(const coor &a, const coor &b);
  double magitude( const coor &a, const coor &b);
  coor norm(const coor &a);
  coor vec( const coor &a, const coor &b);

private:
  coor out;
  coor dir, diff, dir_unit; //plane
  double dist;
  double a,b,c,delta; // sphere
  double t0, t1;
};

#endif
