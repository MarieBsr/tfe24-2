#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <fmt/core.h>

#include "../point_fmt.hpp"  

TEST_CASE("Point<T>: Konstruktion & move (int)") {
  Point<int> p{2, 3};
  REQUIRE(p.x == 2);
  REQUIRE(p.y == 3);

  p.move(1, -4);
  REQUIRE(p.x == 3);
  REQUIRE(p.y == -1);
}

TEST_CASE("Point<T>: Konstruktion & move (double)") {
  Point<double> p{2.5, -3.75};
  p.move(0.5, 0.25);
  REQUIRE(p.x == Catch::Approx(3.0));
  REQUIRE(p.y == Catch::Approx(-3.5));
}

TEST_CASE("Point<T>: distance_to – Typ & Wert") {
  Point<int> a{0,0}, b{3,4};
  typedef decltype(a.distance_to(b)) dist_t;
  STATIC_REQUIRE(!std::is_same<dist_t, int>::value);
  REQUIRE(a.distance_to(b) == Catch::Approx(5.0).margin(1e-12));
  REQUIRE(b.distance_to(a) == Catch::Approx(5.0).margin(1e-12));
  REQUIRE(a.distance_to(a) == Catch::Approx(0.0).margin(1e-12));
}

TEST_CASE("Point<T>: fmt-Formatter") {
  Point<int> pi{1,2};
  REQUIRE(fmt::format("{}", pi) == "(1, 2)");
}