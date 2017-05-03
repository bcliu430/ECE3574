#include "geometry.hpp"
#include <QDebug>

double geometry::dot(const coor &a, const coor &b){
  return (a.x*b.x+a.y*b.y+a.z*b.z);
}

coor geometry::norm(const coor &a){
  coor out;
  double x_sq = pow(a.x, 2);
  double y_sq = pow(a.y, 2);
  double z_sq = pow(a.z, 2);
  double d = pow(x_sq+y_sq+z_sq,0.5);

  out.x = a.x/d;
  out.y = a.y/d;
  out.z = a.z/d;
  return out;
}
coor geometry::vec(const coor &a, const  coor &b ){
  coor out;
  out.x = b.x - a.x;
  out.y = b.y - a.y;
  out.z = b.z - a.z;
  return out;
}

double geometry::magitude(const coor &a, const coor &b){
  return pow ((pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)) , 0.5);
}
