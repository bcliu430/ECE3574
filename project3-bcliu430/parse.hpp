#ifndef PARSE_HPP
#define PARSE_HPP
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "light.hpp"
#include "objects.hpp"
#include "camera.hpp"

class parse {
public:
    parse() { }
    ~parse() { }
    parse(const std::string & file);

    QJsonObject get_camera(){
      return cameraObj;
    }

    std::vector<struct Clight> light_arr(){
      return light_vec;
    }
    std::vector<struct Cobject> obj_arr(){
      return obj_vec;
    }

private:
  QJsonObject json;
  QJsonObject cameraObj;
  QJsonArray light_array;
  QJsonArray object_array;
  std::vector<struct Clight> light_vec;
  std::vector<struct Cobject> obj_vec;
  QJsonObject light, Obj;
};

#endif
