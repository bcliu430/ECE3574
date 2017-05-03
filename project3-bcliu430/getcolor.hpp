#ifndef GETCOLOR_HPP
#define GETCOLOR_HPP
#include <QColor>
#include <vector>
#include "geometry.hpp"
#include "objects.hpp"

class getcolor {
public:
  getcolor(){ }
  getcolor(const coor &surface_normal, const coor &shadow_ray,
            const double &lambert, const double &intensity, const color &color);
  color retColor(){ return cor;}

private:
  color cor;
};
#endif
