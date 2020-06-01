#pragma once
#include <SFML/Graphics.hpp>

class Planet
{
private:
	sf::Vector2f* v;
	sf::Vector2f* a;
public:
	sf::CircleShape *texture;
	sf::Vector2f* position;
	double mass;
	double r;

	Planet(sf::Vector2f pos, double mass, double r);
	Planet(sf::Vector2f pos, sf::Vector2f v, sf::Vector2f a, double mass, double r);
	void Move(double dt);
	void ResetA();
	void Correct(Planet& other);
	~Planet();
};

