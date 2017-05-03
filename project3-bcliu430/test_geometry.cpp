#include "catch.hpp"

#include "geometry.hpp"

TEST_CASE("test geometry", "[geometry]"){
    geometry geo;
    coor a = {3,4,5};
    coor b = {4,3,5};
    coor c = {10,0,0};

    double dot_ret = geo.dot(a,b);
    REQUIRE(dot_ret == 49);

    coor norm_ret = geo.norm(c);
    REQUIRE(norm_ret.x == Approx(1));
    REQUIRE(norm_ret.y == 0);
    REQUIRE(norm_ret.z == 0);
}

TEST_CASE("test vector and magitude", "[geometry]"){
  {
    geometry geo;
    coor a = {0,0,0};
    coor b = {1,3,5};

    coor vec = geo.vec(a,b);
    bool ok = (vec.x == 1) && (vec.y == 3) && (vec.z == 5);

    REQUIRE(ok);

  }
  {
    geometry geo;
    coor a = {0,0,0};
    coor b = {2,3,6};

    double mag = geo.magitude(a,b);
    REQUIRE(mag == 7);

  }

}
