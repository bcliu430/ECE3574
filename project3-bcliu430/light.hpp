#ifndef LIGHTS_HPP
#define LIGHTS_HPP
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include "parse.hpp"
#include "geometry.hpp"

struct Clight{
  double intensity;
  struct coor loc;
};

class Light{
public:
  Light(){ }
  ~Light() { }
  Light(const QJsonObject &qj_obj);
  Clight get_light();
private:
  Clight lig;
};
#endif
