#include "camera.hpp"

#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

camera::camera(const QJsonObject &qj_obj){
    QJsonObject center = qj_obj["center"].toObject();
    if (center.size() != 3){
      throw "Error: cannot parse camera, invalid center.\n";
    }
    else{
      cam.cen.x = center["x"].toDouble();
      cam.cen.y = center["y"].toDouble();
      cam.cen.z = center["z"].toDouble();
    }
    QJsonObject normal = qj_obj["normal"].toObject();
    if (normal.size() != 3){
      throw "Error: cannot parse camera, invalid normal.\n";
    }
    else{
      cam.nor.x = normal["x"].toDouble();
      cam.nor.y = normal["y"].toDouble();
      cam.nor.z = normal["z"].toDouble();
    }
    QJsonArray img_size = qj_obj["size"].toArray();
    QJsonArray img_res = qj_obj["resolution"].toArray();
    cam.focus = qj_obj["focus"].toInt();
    if (img_size.size()!= 2){
      throw "Error: wrong image size.\n";
    }
    if (img_res.size() != 2){
      throw "Error: wrong image resolution.\n";
    }
    cam.size[0] = img_size[0].toInt();
    cam.size[1] = img_size[1].toInt();
    cam.resolution[0] = img_res[0].toDouble();
    cam.resolution[1] = img_res[1].toDouble();

}
