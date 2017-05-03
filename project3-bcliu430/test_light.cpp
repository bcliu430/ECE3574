#include "catch.hpp"

#include "light.hpp"
#include <QJsonObject>


TEST_CASE("test light", "[Light]"){
  {
    QJsonObject light_obj;
    QJsonObject location;
    location.insert("x", 5);
    location.insert("y", -5);
    location.insert("z", 0);
    light_obj.insert("intensity",1);
    light_obj.insert("location",location);

    Light L(light_obj);
    Clight light_struct = L.get_light();
    REQUIRE(light_struct.intensity == 1);
    REQUIRE(light_struct.loc.x == 5);
    REQUIRE(light_struct.loc.y == -5);
    REQUIRE(light_struct.loc.z == 0);
  }
  {
    QJsonObject light_obj;
    QJsonObject location;
    location.insert("x", 5);
    location.insert("y", -5);
    location.insert("z", 0);

    light_obj.insert("intensity",1.5);
    light_obj.insert("location",location);

    Light L(light_obj);
    REQUIRE_THROWS_WITH(L.get_light(), "Error: light is not complete");
 }
   {
     QJsonObject light_obj;
     QJsonObject location;
     location.insert("x", 5);
     location.insert("y", -5);
     light_obj.insert("intensity",1);
     light_obj.insert("location",location);

     REQUIRE_THROWS_WITH(Light L(light_obj), "Error: cannot parse light");
  }
}
