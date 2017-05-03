#include "catch.hpp"
#include "getcolor.hpp"

#include <QColor>


TEST_CASE("test getcolor", "[geometry]"){
  {
    color a = {0,0,0};
    color b = {0,0,0};
    bool ok = (a==b);
    REQUIRE(ok);
  }
  {
    struct coor a = {2,0,0};
    struct coor b = {0,4,0};

    double l = 0.3;
    double intensity = 0.5;
    color rgb = {255,0,0};
    color result = {0,0,0};
    getcolor G(a,b,l,intensity,rgb);

    REQUIRE(G.retColor() == result);

  }
  {
    struct coor a = {2,0.125,0};
    struct coor b = {0.25,4,0};

    double l = 1;
    double intensity = 1;
    color rgb = {255,0,0};
    getcolor getco(a,b,l,intensity,rgb);
    color ret = getco.retColor();
    color result = {31,0,0};
    REQUIRE(ret == result);
  }
  {
    struct coor a = {2,0.125,0};
    struct coor b = {0.25,4,0};

    double l = 1;
    double intensity = 1;
    color rgb = {-10,-20,-30};
    getcolor getco(a,b,l,intensity,rgb);
    color ret = getco.retColor();
    color result = {0,0,0};
    REQUIRE(ret == result);
  }
}
