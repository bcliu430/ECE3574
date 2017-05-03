#include "objects.hpp"

#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
objects::objects(const QJsonObject &qj_obj, const std::string &obj_type){
  parse par;
  QJsonObject center = qj_obj["center"].toObject();
  if (center.size() != 3){
    throw "Error: not a valid center.\n";
  }
  else{
    obj.cen.x = center["x"].toDouble();
    obj.cen.y = center["y"].toDouble();
    obj.cen.z = center["z"].toDouble();
  }

  QJsonObject color = qj_obj["color"].toObject();
  c_red   = color["r"].toInt();
  c_green = color["g"].toInt();
  c_blue  = color["b"].toInt();

  if (( c_red > 255 || c_red < 0) || (c_green >255 || c_green < 0) || (c_blue > 255 ||c_blue < 0) )
   {
     throw "Error: invalid color.\n";
   } else {
      obj.Ccol.r = c_red;
      obj.Ccol.g = c_green;
      obj.Ccol.b = c_blue;
  }
  if (obj_type == "plane"){
    QJsonObject normal =  qj_obj["normal"].toObject();
    if (normal.size() != 3){
      throw "Error: not a valid normal.\n";
    }
    else{
      obj.nor.x = normal["x"].toDouble();
      obj.nor.y = normal["y"].toDouble();
      obj.nor.z = normal["z"].toDouble();
    }
  }
  if (obj_type == "sphere"){
    obj.lambert = qj_obj["lambert"].toDouble();
    obj.radius = qj_obj["radius"].toDouble();
    obj.nor = {0,0,0};
    obj.type = "sphere";

  }
  if(obj_type == "plane"){
    obj.lambert = qj_obj["lambert"].toDouble();
    obj.radius = 0;
    obj.type = "plane";
  }
}


Cobject objects::get_obj(){
      return obj;
};
