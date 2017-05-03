#include "catch.hpp"
#include "process.hpp"
#include <QDebug>
#include <QJsonObject>

TEST_CASE("test process", "[process]"){
  std::string file = "/vagrant/tests/scene0.json";
  std::string out = "out.png";

  process p(file, out,1);
  {
    double x = 1, y = 2, z =3;
    coor a = p.convert_to_coor(x,y,z);
    coor b = {1,2,3};
    REQUIRE(a == b);
  }

  {
    int x = 140;
    double y = 0;
    coor a = p.calc_pixel(x,x,y);
    coor b = {0.12,0.12,0};
    REQUIRE(a==b);
  }

  {
    coor a = {0,0,-10};
    coor b = {0.12,0.12,0};
    color c =  p.get_pix_color(a,b);
    color out = { 120, 0, 0};
    REQUIRE(c == out);
  }
  {
    int C = 285;
    double out = p.find_coef(C);
    REQUIRE(out == Approx(double(255)/double(285)));
  }
}

TEST_CASE("test ray inter", "[process]"){
  std::string file = "/vagrant/tests/scene1.json";
  std::string out = "out.png";
  coor light = {5,-5, 0};
  process p(file,out,1);
  std::vector<Cobject> obj_arr = p.get_obj_arr();
  Cobject O = obj_arr.at(1);
  coor inter = {1.47945, 5, 3.69863};
  bool ok = p.ray_inter(inter,light, O);
  REQUIRE(!ok);
}
