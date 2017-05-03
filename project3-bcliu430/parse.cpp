#include "parse.hpp"
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <exception>
#include <QJsonParseError>
#include <QDebug>
parse::parse(const std::string &file){
    QFile inf(QString::fromStdString(file));

    if(!inf.open(QIODevice::ReadOnly)){
      throw "Error: parse error.\n";
    }
    QByteArray rawData = inf.readAll();

    // Parse document
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(rawData, &err);

    if(err.error != QJsonParseError::NoError){
      qDebug() << "json parse error";
      throw err;
    }
    // Get JSON object
    json = doc.object();


    cameraObj = json["camera"].toObject();
    light_array = json["lights"].toArray();
    object_array = json["objects"].toArray();

    for (int jj = 0; jj < light_array.size(); jj++) {
      try{
        light = light_array[jj].toObject();
        Light L(light);
        Clight light_struct = L.get_light();
        light_vec.push_back(light_struct);
      }
      catch (...) {
        exit(EXIT_FAILURE);
      }
    }
    for (int ii = 0; ii < object_array.size(); ii++) {
      try{
        Obj = object_array[ii].toObject();
        std::string obj_type = Obj["type"].toString().toStdString();
        objects O(Obj,obj_type);
        Cobject obj_struct = O.get_obj();
        obj_vec.push_back(obj_struct);
      }
      catch (...) {
        exit(EXIT_FAILURE);
      }

    }


}
