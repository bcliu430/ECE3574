#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <string>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QImage>
#include <vector>
#include <iostream>
#include <future>

#include "parse.hpp"
#include "camera.hpp"
#include "geometry.hpp"
#include "light.hpp"
#include "objects.hpp"
#include "getcolor.hpp"

using std::vector;

class process{
public:
  process(){  }
  process(const std::string &input, std::string &output, const int &threadNum);
  coor convert_to_coor(const double &X, const double &Y, const double &Z);
  coor calc_pixel(const int &X, const int &Y, const double &z);
  color get_pix_color( const coor &start, const coor &stop);
  double find_coef( const int &max);
  void find_sphere_info(const coor &start, const coor &stop, const Cobject &sph);
  inline bool find_close(const coor & start,const coor & intersect,const coor & close);
  bool ray_inter(const coor &close, const coor &light, const Cobject &obj);
  std::vector<std::vector<color>> render(const int &thread,
    const int &x_size, const int &y_size, const coor &start, const int &thread_index);
  void scale(const int &x_size, const int &y_size, QImage &img);
  std::vector<Cobject> get_obj_arr(){ return obj_arr;}
private:
    int x=0, y=0;
    double x_resolution =0 , y_resolution = 0;
    Ccamera camStruct;
    std::vector<Cobject> obj_arr;
    std::vector<Clight> light_arr;
    int R_max = 0, G_max = 0, B_max = 0;
    double R_coef = 1, G_coef =1,B_coef = 1;
    Cobject obj_struct;
    Clight light_struct;
    Cobject obj;
    coor sur_normal,shadow;

    /* sphere para*/
    double a,b,c,delta ,t; // sphere
    double t0,t1;
    vector<vector<color> > matrix;

    /* plane*/
    coor dir, diff, dir_unit; //plane

};
#endif
