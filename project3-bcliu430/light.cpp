#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include "light.hpp"

Light::Light(const QJsonObject &qj_obj){
  parse par;
  QJsonObject location = qj_obj["location"].toObject();
  if (location.size() != 3){
    throw "Error: cannot parse light";
  }
  lig.loc.x = location["x"].toDouble();
  lig.loc.y = location["y"].toDouble();
  lig.loc.z = location["z"].toDouble();
  lig.intensity = qj_obj["intensity"].toDouble();
}

Clight Light::get_light(){
  if ( lig.intensity>=0 && lig.intensity<=1 ){
          return lig;
  }
  throw "Error: light is not complete";
};
