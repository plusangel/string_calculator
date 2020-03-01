//
// Created by angelos on 29/02/2020.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "simple_calc.h"

using namespace std::literals::string_literals;

TEST_CASE("check calculator's functionality") {

  SECTION("add") { REQUIRE(std::any_cast<int>(calculator("100+11")) == 111); }

  SECTION("sub") { REQUIRE(std::any_cast<int>(calculator("100-11")) == 89); }

  SECTION("mult") {
    REQUIRE(std::any_cast<int>(calculator("100*10")) == 1'000);
  }

  SECTION("div") { REQUIRE(std::any_cast<int>(calculator("100/10")) == 10); }

  SECTION("div with zero") {
    REQUIRE_THROWS_AS(std::any_cast<int>(calculator("100/0")),
                      std::invalid_argument);
  }

  SECTION("unknown operand") {
    REQUIRE_THROWS_AS(std::any_cast<int>(calculator("100$0")),
                      std::invalid_argument);
  }

  SECTION("out of range") {
    REQUIRE_THROWS_AS(std::any_cast<int>(calculator("100000000000000+0")),
                      std::out_of_range);
  }

  SECTION("mad user") {
    REQUIRE_THROWS_AS(std::any_cast<int>(calculator("bull-shit")),
                      std::exception);
  }
}