#include "catch.hpp"
#include "parse.hpp"

#include <exception>

TEST_CASE("parse test", "[parse]"){
  {
    std::string file = "dne.json";
    REQUIRE_THROWS(parse parse(file));
  }
  {
    std::string file = "/vagrant/tests/scene0.json";
    REQUIRE_NOTHROW(parse parse(file));
  }
  {
    std::string file = "vagrant/tests/blank.json";
    REQUIRE_THROWS(parse parse(file));
  }
  {
    std::string file = "/vagrant/tests/scene0.json";
    parse p(file);
    REQUIRE_NOTHROW(p.get_camera());
  }
}
