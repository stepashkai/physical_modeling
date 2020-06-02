#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "planet.hpp"
#include <iostream>
#include <cmath>


Planet CreatePlanet(double posX, double posY, double vX, double vY, double aX, double aY, double mass, double d, double rotation, std::string filepath)
{
    sf::Vector2f pos(posX, posY);
    sf::Vector2f v(vX, vY);
    sf::Vector2f a(aX, aY);
    Planet planet("", pos, v, a, mass, d, rotation);
    return planet;
}


TEST_CASE("Test distance")
{
    Planet a(CreatePlanet(0, 100, 0, 0, 0, 0, 0, 0,0, ""));
    Planet b(CreatePlanet(0, 0, 0, 0, 0, 0, 0, 0,0, ""));
    Planet c(CreatePlanet(100, 100, 0, 0, 0, 0, 0, 0,0, ""));
    Planet d(CreatePlanet(100, 0, 0, 0, 0, 0, 0, 0,0, ""));
    REQUIRE(a.GetDistance(b) == 100);
    REQUIRE(b.GetDistance(c) == sqrt(2) * 100);
    REQUIRE(b.GetDistance(d) == 100);
}

TEST_CASE("Test convert")
{
    REQUIRE(Planet::ToMeter(0.0001) == 100000);
    REQUIRE(Planet::ToMeter(1) ==  1000000000);
    REQUIRE(Planet::ToPixels(100000) == 0.0001);
    REQUIRE(Planet::ToPixels(1000000000) ==  1);
}

TEST_CASE("Test union")
{
    Planet a(CreatePlanet(0, 0, 0, 0, 0, 0, 100, 0,0, ""));
    Planet b(CreatePlanet(0, 0, 0, 0, 0, 0, 333, 0,0, ""));
    a.Union(b);
    REQUIRE(a.mass == 433);
    a.Union(a);
    REQUIRE(a.mass == 866);
}

TEST_CASE("Test colision")
{
    Planet a(CreatePlanet(0, 0, 0, 0, 0, 0, 0, 10,0, ""));
    Planet b(CreatePlanet(0, 20, 0, 0, 0, 0, 0, 20,0, ""));
    Planet c(CreatePlanet(0, 30, 0, 0, 0, 0, 0, 20,0, ""));
    Planet d(CreatePlanet(0, 50, 0, 0, 0, 0, 0, 20,0, ""));
    REQUIRE(a.GetDistance(b) < a.d + b.d);
    REQUIRE(a.GetDistance(c) <= a.d + c.d);
    REQUIRE(a.GetDistance(d) > a.d + d.d);
}
