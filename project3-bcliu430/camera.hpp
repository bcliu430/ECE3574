#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "parse.hpp"
#include "geometry.hpp"

struct Ccamera{
  int focus;
  struct coor cen;
  double resolution[2];
  int size[2];
  struct coor nor;
};
class camera {
public:
  camera() { }
  ~camera() { }
  camera(const QJsonObject &qj_obj);
  Ccamera get_cam(){
    return cam;
  };
private:
  Ccamera cam;
};
#endif
