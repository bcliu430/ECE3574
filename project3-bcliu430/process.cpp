#include "process.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QImage>
#include <QColor>
#include <QJsonParseError>
#include <QString>
#include <QFile>

process::process(const std::string &input, std::string &output, const int &threadNum){
    try {
        parse p(input);
        geometry geo;
        QJsonObject camobj = p.get_camera();
        obj_arr = p.obj_arr();
        light_arr = p.light_arr();
        camera cam(camobj);
        camStruct = cam.get_cam();
        x_resolution = camStruct.resolution[0];
        y_resolution = camStruct.resolution[1];
        coor start = {camStruct.cen.x,camStruct.cen.y, -(double)camStruct.focus};
        x =  camStruct.size[0];
        y =  camStruct.size[1];
        QImage img(x, y, QImage::Format_RGB888);
        matrix.reserve(x);
        std::vector<std::future<std::vector<std::vector<color>>>> threads;
        for (int aa = 0; aa <threadNum; aa++){
          auto xx = std::async(std::launch::async, &process::render,this, threadNum,x,y,std::ref(start),aa);
          threads.push_back(std::move(xx));
        }
        for(int aa = 0; aa <threadNum; aa++){
          auto piece = threads[aa].get();
          matrix.insert(matrix.end(),piece.begin(), piece.end());
          }
        scale(x,y,img);
        QFile file(QString::fromStdString(output));
        img.save(&file,"png",100);
      }
      catch(QJsonParseError &err){
        qDebug() << err.errorString();
        exit(EXIT_FAILURE);
      }
      catch(const std::string *str){
        std::cerr << str;
        exit(EXIT_FAILURE);
      }
      catch(...){
        std::cerr << "Error: \n";
        exit(EXIT_FAILURE);
      }
}

std::vector<std::vector<color>> process::render(const int &thread, const int &x_size, const int &y_size, const coor &start, const int &thread_index){
  coor stop;
  std::vector<std::vector<color>> mat;
  mat.reserve(x_size);
  for (int ii = 0; ii < x_size/thread; ii++){
    vector<color> sub_mat;
    sub_mat.reserve(y_size);
    for (int jj =0; jj < y_size;jj++){
        int x_pos = thread_index*x_size/thread+ii;
        stop = calc_pixel(x_pos,jj ,camStruct.cen.z);
        color c = get_pix_color(start,stop);
        sub_mat.push_back(c);
    }
    mat.push_back(sub_mat);
  }

  return mat;
}

void process::scale(const int &x_size, const int &y_size, QImage &img){
  for (int ii = 0; ii < x_size; ii++){
    vector<color> sub_mat = matrix.at(ii);
    for (int jj = 0; jj < y_size;jj++){
        color c = sub_mat.at(jj);
        if(c.r > 255 && c.r > R_max){  R_max = c.r;    }
        if(c.g > 255 && c.g > G_max){  G_max = c.g;    }
        if(c.b > 255 && c.b > B_max){  B_max = c.b;    }
    }
  }
  R_coef = find_coef(R_max);
  G_coef = find_coef(G_max);
  B_coef = find_coef(B_max);
  for (int ii = 0; ii < x_size; ii++){
    vector<color> sub_mat = matrix.at(ii);
    for (int jj = 0; jj < y_size;jj++){
      color value = sub_mat.at(jj);
      int r_color = int(value.r * R_coef );
      int g_color = int(value.g * G_coef );
      int b_color = int(value.b * B_coef );
      QRgb real_color = qRgb(r_color,g_color, b_color );
      img.setPixel(ii,jj,real_color);
    }
  }

}
coor process::convert_to_coor(const double &X, const double &Y , const double &Z){
  coor a = {X,Y,Z};
  return a;
}

coor process::calc_pixel(const int &X, const int &Y, const double &z){
    double xx = x_resolution*(X-(x/2));
    double yy = y_resolution*(Y-(y/2));
    double zz = z;
    coor a = {xx,yy,zz};
    return a;
}

color process::get_pix_color(const coor &start, const coor &stop){
  geometry geo;
  color CC = {0,0,0};
  color zero = {0,0,0};
  coor Intersect_pnt;
  coor close;
  coor diff = geo.vec(start, stop);
  for (int ii = 0; ii <light_arr.size(); ii++){
    int inter = -1;
    light_struct = light_arr.at(ii);
    for (int jj = 0; jj < obj_arr.size(); jj++){
      obj = obj_arr.at(jj);
      if(obj.type =="sphere"){
          find_sphere_info(start,stop,obj);
          if(delta >= 0){
            Intersect_pnt.x = start.x + diff.x*t;
            Intersect_pnt.y = start.y + diff.y*t;
            Intersect_pnt.z = start.z + diff.z*t;
            if(inter == -1 || (find_close(start,Intersect_pnt,close))){
              close = Intersect_pnt;
              inter = jj;
            }
          }
      }   else if(obj.type == "plane"){
        coor dir = geo.vec(start,stop);
        dir = geo.norm(dir);
        coor diff = geo.vec(start,obj.cen);
        float denom = geo.dot(obj.nor, dir );
        if (std::abs(denom)>0.001f){
          float numer = geo.dot(obj.nor, diff);
          float distance = numer/denom;
          if(distance >= 0){
            Intersect_pnt.x = start.x + dir.x*distance;
            Intersect_pnt.y = start.y + dir.y*distance;
            Intersect_pnt.z = start.z + dir.z*distance;
            if(inter == -1 ||(find_close(start,Intersect_pnt,close))){
              close = Intersect_pnt;
              inter = jj;
            }
           }
        }
      }
    } // obj_arr end
    if (inter == -1 || ray_inter( close,  light_struct.loc, obj) ){
      CC = CC + zero;
    }  else {
      if (obj_arr.at(inter).type  == "plane"){
        sur_normal = obj_arr.at(inter).nor;
      }
      else if (obj_arr.at(inter).type == "sphere"){
        sur_normal = geo.vec(obj_arr.at(inter).cen, close);
      }
      shadow = geo.vec(close,light_struct.loc);
      getcolor getC(sur_normal,shadow, obj_arr.at(inter).lambert ,light_struct.intensity,obj_arr.at(inter).Ccol);
      CC = CC + getC.retColor();
    }
  } //light_arr end
  return CC;
}

double process::find_coef(const int &max){
  double c = 1;
  if(max!= 0){
    c = double(255)/double(max);
  }
  return c;
}

void process::find_sphere_info(const coor &start, const coor &stop, const Cobject &sph){
  double dx = stop.x - start.x;
  double dy = stop.y - start.y;
  double dz = stop.z - start.z;
  a = pow (dx, 2) + pow (dy, 2) + pow(dz,2);
  b = 2*( dx*(start.x-sph.cen.x) +
          dy*(start.y-sph.cen.y) +
          dz*(start.z-sph.cen.z) );
  c = pow((start.x-sph.cen.x), 2) + pow((start.y-sph.cen.y), 2) + pow( (start.z-sph.cen.z), 2) - pow(sph.radius,2);
  delta = pow(b,2)-4*a*c;
  t0 = (-b + pow(delta, 0.5) ) /(2 *a);
  t1 = (-b - pow(delta, 0.5) ) /(2 *a);

  if(t0>t1){
    t = t1;
  }
  if (t0<t1){
    t = t0;
  }
}

inline bool process::find_close(const coor & start,const coor & intersect,const coor & close){
  geometry geo;
  double dist1 =geo.magitude(start,intersect);
  double dist2 =geo.magitude(start,close);
  return (dist1 <dist2);
}

bool process::ray_inter(const coor &close, const coor &light, const Cobject &obj){
  geometry geo;
  Cobject oo;
  coor d = geo.vec(close,light);
  double dist = geo.magitude(close, light);
  for (int ii = 0 ; ii <obj_arr.size(); ii++){
    if(!(obj_arr.at(ii) == obj)){
      if(obj_arr.at(ii).type == "sphere"){
        double a = d.x*d.x + d.y*d.y + d.z*d.z;
        double b = 2*(d.x*(close.x - obj_arr.at(ii).cen.x) +
                      d.y*(close.y - obj_arr.at(ii).cen.y) +
                      d.z*(close.z - obj_arr.at(ii).cen.z) );
        double c = pow((close.x - obj_arr.at(ii).cen.x),2) +
                   pow((close.y - obj_arr.at(ii).cen.y),2) +
                   pow((close.z - obj_arr.at(ii).cen.z),2) -
                   pow(obj_arr.at(ii).radius,2) ;
        double r = obj_arr.at(ii).radius;
        double delta = b*b - 4*a*c;
        if(delta >= 0){
          double t0 = (-b-pow(delta,0.5))/(2*a);
          double t1 = (-b+pow(delta,0.5))/(2*a);
          double t;
          if(t0>t1){ t = t1; }
          if(t0<t1){ t = t0; }
          double dx = close.x + t*d.x;
          double dy = close.y + t*d.y;
          double dz = close.z + t*d.z;
          coor new_loc = {dx,dy,dz};
          double DISt = geo.magitude(light, new_loc);
          if(dz>=0 && DISt < dist){
            return true;
          }
        }
      }
      else if (obj_arr.at(ii).type == "plane"){
          coor unit = geo.norm(d);
          coor cen = geo.vec(close, obj_arr.at(ii).cen);
          cen = geo.norm(cen);
          double denom = geo.dot(cen,unit);
          if(std::abs(denom) > 0.001f){
            double numer = geo.dot(obj_arr.at(ii).nor, cen);
            double dist = numer/denom;
            if(dist >= 0){
              double dx = close.x + t*unit.x;
              double dy = close.y + t*unit.y;
              double dz = close.z + t*unit.z;
              coor new_loc = {dx,dy,dz};
              double DISt = geo.magitude(light,new_loc);
              if(dz>= 0 && DISt < dist){
                return true;
              }
            }
          }
      }
    }
  }
  return false;
}
