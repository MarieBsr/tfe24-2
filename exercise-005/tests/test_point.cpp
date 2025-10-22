#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "point.hpp"
using Catch::Approx;

TEST_CASE("Point: Constructors") {
    SECTION("Initialize with values") {
        Point p{2, 3};
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 3);
    }

    SECTION("Default constructor") {
        Point p;
        REQUIRE(p.x == 0);
        REQUIRE(p.y == 0);
    }
}

TEST_CASE("Point: move shifts relatively") {
    SECTION("Positive and negative shifts") {
        Point p{1, 1};
        p.move(2, -3);
        REQUIRE(p.x == 3);
        REQUIRE(p.y == -2);
    }

    SECTION("Multiple consecutive moves") {
        Point p{0, 0};
        p.move(1, 1);
        p.move(2, -1);
        p.move(-1, 3);
        REQUIRE(p.x == 2); // 0+1+2-1
        REQUIRE(p.y == 3); // 0+1-1+3
    }
}

TEST_CASE("Point: distance_to – Euclidean & robust") {
    SECTION("Standard distance") {
        Point a{0, 0};
        Point b{3, 4};
        REQUIRE(a.distance_to(b) == Approx(5.0).margin(1e-12));
    }

    SECTION("Symmetry") {
        Point a{0, 0};
        Point b{3, 4};
        REQUIRE(a.distance_to(b) == Approx(b.distance_to(a)).margin(1e-12));
    }

    SECTION("Distance to self") {
        Point a{5, -7};
        REQUIRE(a.distance_to(a) == Approx(0.0).margin(1e-12));
    }

    SECTION("Large and negative coordinates") {
        Point a{1'000'000'000, -1'000'000'000};
        Point b{-1'000'000'000, 1'000'000'000};
        double dist = a.distance_to(b);
        REQUIRE(dist == Approx(2'828'427'124.74619).margin(1e-6)); // sqrt(2*10^18)
    }

    SECTION("Stability after many moves") {
        Point p{0,0};
        for(int i=0; i<1'000; ++i) {
            p.move(1, -1);
        }
        Point q{1000, -1000};
        REQUIRE(p.distance_to(q) == Approx(0.0).margin(1e-12));
    }

    SECTION("Triangle inequality (optional)") {
        Point a{0,0};
        Point b{3,4};
        Point c{6,8};
        REQUIRE(a.distance_to(c) <= a.distance_to(b) + b.distance_to(c) + 1e-12);
    }
}