#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <unordered_map>
#include <string>
#include "catch.hpp"

TEST_CASE("Test Constructor","[unordered_map]"){

    typedef std::unordered_map<int,std::string> MapT;

    MapT map;
    REQUIRE(map.size() == 0);
    REQUIRE(map.empty());
}

TEST_CASE("Test Insrty","[unordered_map]"){

    typedef std::unordered_map<int,std::string> MapT;

    MapT map;
    map[42] = "fourty-two";
    REQUIRE(map.size() == 1);
    REQUIRE(!map.empty());
}
