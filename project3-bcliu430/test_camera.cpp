#include "catch.hpp"

#include <QJsonObject>
#include "camera.hpp"

TEST_CASE("test camera ", "[camera]"){
    QJsonObject center;
    center.insert("x",0);
    center.insert("y",0);
    center.insert("z",0);
    QJsonObject normal;
    normal.insert("x",0);
    normal.insert("y",0);
    normal.insert("z",1);
    QJsonObject cam_obj;
    cam_obj.insert("center", center);
    cam_obj.insert("focus", 10);
    cam_obj.insert("normal", normal);
    QJsonArray res;
    res.insert(0,0.1);
    res.insert(1,0.1);
    QJsonValue res_val(res);
    cam_obj.insert("resolution",res_val);
    QJsonArray size;
    size.insert(0,256);
    size.insert(1,256);
    QJsonValue size_val(size);
    cam_obj.insert("size", size_val);

    camera cam(cam_obj);
    Ccamera cam_struct = cam.get_cam();
    coor a = {0,0,0};
    coor b = {0,0,1};

    REQUIRE(cam_struct.cen == a);
    REQUIRE(cam_struct.nor == b);
    REQUIRE(cam_struct.resolution[0] == 0.1);
    REQUIRE(cam_struct.resolution[1] == 0.1);

    REQUIRE(cam_struct.size[0] == 256);
    REQUIRE(cam_struct.size[1] == 256);
    REQUIRE(cam_struct.focus == 10);
}


TEST_CASE("test camera bad center", "[camera]"){
    QJsonObject center;
    center.insert("x",0);
    center.insert("y",0);
    QJsonObject normal;
    normal.insert("x",0);
    normal.insert("y",0);
    normal.insert("z",1);
    QJsonObject cam_obj;
    cam_obj.insert("center", center);
    cam_obj.insert("focus", 10);
    cam_obj.insert("normal", normal);
    QJsonArray res;
    res.insert(0,0.1);
    res.insert(1,0.1);
    QJsonValue res_val(res);
    cam_obj.insert("resolution",res_val);
    QJsonArray size;
    size.insert(0,256);
    size.insert(1,256);
    QJsonValue size_val(size);
    cam_obj.insert("size", size_val);

    REQUIRE_THROWS_WITH( camera cam(cam_obj), "Error: cannot parse camera, invalid center.\n");
}

TEST_CASE("test camera bad Normal", "[camera]"){
    QJsonObject center;
    center.insert("x",0);
    center.insert("y",0);
    center.insert("z",0);
    QJsonObject normal;
    normal.insert("x",0);
    normal.insert("y",0);
    QJsonObject cam_obj;
    cam_obj.insert("center", center);
    cam_obj.insert("focus", 10);
    cam_obj.insert("normal", normal);
    QJsonArray res;
    res.insert(0,0.1);
    res.insert(1,0.1);
    QJsonValue res_val(res);
    cam_obj.insert("resolution",res_val);
    QJsonArray size;
    size.insert(0,256);
    size.insert(1,256);
    QJsonValue size_val(size);
    cam_obj.insert("size", size_val);

    REQUIRE_THROWS_WITH( camera cam(cam_obj), "Error: cannot parse camera, invalid normal.\n");
}
TEST_CASE("test camera bad array", "[camera]"){
  {
    QJsonObject center;
    center.insert("x",0);
    center.insert("y",0);
    center.insert("z",0);
    QJsonObject normal;
    normal.insert("x",0);
    normal.insert("y",0);
    normal.insert("z",1);
    QJsonObject cam_obj;
    cam_obj.insert("center", center);
    cam_obj.insert("focus", 10);
    cam_obj.insert("normal", normal);
    QJsonArray res;
    res.insert(0,0.1);
    QJsonValue res_val(res);
    cam_obj.insert("resolution",res_val);
    QJsonArray size;
    size.insert(0,256);
    size.insert(1,256);
    QJsonValue size_val(size);
    cam_obj.insert("size", size_val);

    REQUIRE_THROWS_WITH( camera cam(cam_obj), "Error: wrong image resolution.\n");
  }
  {
    QJsonObject center;
    center.insert("x",0);
    center.insert("y",0);
    center.insert("z",0);
    QJsonObject normal;
    normal.insert("x",0);
    normal.insert("y",0);
    normal.insert("z",1);
    QJsonObject cam_obj;
    cam_obj.insert("center", center);
    cam_obj.insert("focus", 10);
    cam_obj.insert("normal", normal);
    QJsonArray res;
    res.insert(0,0.1);
    res.insert(1,0.1);
    QJsonValue res_val(res);
    cam_obj.insert("resolution",res_val);
    QJsonArray size;
    size.insert(0,256);
    QJsonValue size_val(size);
    cam_obj.insert("size", size_val);

    REQUIRE_THROWS_WITH( camera cam(cam_obj), "Error: wrong image size.\n");
  }
}
