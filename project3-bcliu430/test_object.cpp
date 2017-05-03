#include "catch.hpp"

#include <QJsonObject>
#include <QDebug>
#include "objects.hpp"


TEST_CASE("test sphere","[objects]"){
    {
    QJsonObject center;
    center.insert("x", 0);
    center.insert("y", 0);
    center.insert("z", 5);
    QJsonObject color;
    color.insert("r", 255);
    color.insert("g", 0);
    color.insert("b", 0);
    QJsonObject obj;
    obj.insert("center",center);
    obj.insert("color", color);
    obj.insert("lambert",1);
    obj.insert("radius", 1);
    obj.insert("type", "sphere");

    coor a = {0,0,5};
  //  color Color = {255,0,0};
    objects Obj(obj,"sphere");
    Cobject obj_struct = Obj.get_obj();
    REQUIRE(obj_struct.cen == a);
  //  REQUIRE(obj_struct.Ccol == Color);
    REQUIRE(obj_struct.lambert == 1);
    REQUIRE(obj_struct.radius == 1);
    REQUIRE(obj_struct.type == "sphere");
    }
    {
      QJsonObject center;
      center.insert("x", 0);
      center.insert("y", 0);
      QJsonObject color;
      color.insert("r", 255);
      color.insert("g", 0);
      color.insert("b", 0);
      QJsonObject obj;
      obj.insert("center",center);
      obj.insert("color", color);
      obj.insert("lambert",1);
      obj.insert("radius", 1);
      obj.insert("type", "sphere");

      REQUIRE_THROWS_WITH(objects Obj(obj,"sphere"), "Error: not a valid center.\n");

      }
  }

TEST_CASE("test plane","[objects]"){
    {
    QJsonObject center;
    center.insert("x", 0);
    center.insert("y", 5);
    center.insert("z", 0);
    QJsonObject normal;
    normal.insert("x", 0);
    normal.insert("y", -1);
    normal.insert("z", 0);
    QJsonObject color;
    color.insert("r", 255);
    color.insert("g", 255);
    color.insert("b", 255);
    QJsonObject obj;
    obj.insert("center",center);
    obj.insert("color", color);
    obj.insert("lambert",1);
    obj.insert("radius", 0);
    obj.insert("normal", normal);
    obj.insert("type", "plane");

    coor a = {0,5,0};
    coor b = {0,-1,0};
  //  color Color = {255,255,255};
    objects Obj(obj,"plane");
    Cobject obj_struct = Obj.get_obj();
    REQUIRE(obj_struct.cen == a);
  //  REQUIRE(obj_struct.Ccol == Color);
    REQUIRE(obj_struct.lambert == 1);
    REQUIRE(obj_struct.radius == 0);
    REQUIRE(obj_struct.nor == b);
    REQUIRE(obj_struct.type == "plane");
    }
    {
    QJsonObject center;
    center.insert("x", 0);
    center.insert("y", 5);
    center.insert("z", 0);
    QJsonObject normal;
    normal.insert("x", 0);
    normal.insert("y", -1);
    QJsonObject color;
    color.insert("r", 255);
    color.insert("g", 255);
    color.insert("b", 255);
    QJsonObject obj;
    obj.insert("center",center);
    obj.insert("color", color);
    obj.insert("lambert",1);
    obj.insert("radius", 0);
    obj.insert("normal", normal);
    obj.insert("type", "plane");
    coor a = {0,5,0};
    coor b = {0,-1,0};
    REQUIRE_THROWS_WITH(objects Obj(obj,"plane"), "Error: not a valid normal.\n");

    }

}

TEST_CASE("test wrong color","[objects]"){
  {
    QJsonObject center;
    center.insert("x", 0);
    center.insert("y", 0);
    center.insert("z", 0);
    QJsonObject color;
    color.insert("r", 600);
    color.insert("g", 0);
    color.insert("b", 0);
    QJsonObject obj;
    obj.insert("center",center);
    obj.insert("color", color);
    obj.insert("lambert",1);
    obj.insert("radius", 1);
    obj.insert("type", "sphere");

    REQUIRE_THROWS_WITH(objects Obj(obj,"sphere"), "Error: invalid color.\n");

    }
}
