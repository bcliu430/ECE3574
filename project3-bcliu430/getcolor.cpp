#include "getcolor.hpp"

getcolor::getcolor(const coor &surface_normal, const coor &shadow_ray,
                  const double &lambert,const double &intensity, const color &color)
{
    geometry geo;
    coor shadow = geo.norm(shadow_ray);
    coor normal = geo.norm(surface_normal);
    // normal (0,-1,0) --> shadow  = -0.149
    double scale = geo.dot(normal,shadow)*lambert; //dot should be 0.149
    int R,G,B;
    R = scale*intensity*color.r;
    G = scale*intensity*color.g;
    B = scale*intensity*color.b; //scale 0.149

    cor.r = R;
    cor.g = G;
    cor.b = B; //38
    if(cor.r <0){
      cor.r = 0;
    }
    if(cor.g <0){
      cor.g = 0;
    }
    if(cor.b <0){
      cor.b = 0;
    }

}
